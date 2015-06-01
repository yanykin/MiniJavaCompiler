#include "Instruction.h"
#include <string>

using namespace CodeGeneration;

void CCodeGenerator::emit(IInstruction* instruction)  {
	_instructions.push_back( instruction );
}

TInstructionsList CCodeGenerator::generateCode( const IRTree::IStm* rootStatement ) {
	munchStm( rootStatement );
	return _instructions;
}

void CCodeGenerator::Generate() {
	// Обходим всю цепочку инструкций
	const IRTree::CStmList* list = _statements;
	while ( list != nullptr ) {
		const IRTree::IStm* statement = list->GetHead();
		this->generateCode( statement );
		// Переходим к следующему элементу
		list = list->GetTail();
	}
}

TInstructionsList CCodeGenerator::GetInstrucions() const {
	return _instructions;
}

// === IStm ===
void CCodeGenerator::munchStm( const IRTree::IStm* statement ) {
	if ( !statement ) {
		return;
	}
	
	const IRTree::MOVE* moveStm = _helper.IsMOVE( statement );
	const IRTree::EXP* expStm = _helper.IsEXP( statement );
	const IRTree::SEQ* seqStm = _helper.IsSEQ( statement );
	const IRTree::JUMP* jumpStm = _helper.IsJUMP( statement );
	const IRTree::CJUMP* cjumpStm = _helper.IsCJUMP( statement );
	const IRTree::LABEL* labelStm = _helper.IsLABEL( statement );
	if ( moveStm ) {
		munchStm( moveStm );
	} else if ( expStm ) {
		munchStm( expStm );
	}
	else if ( seqStm ) {
		munchStm( seqStm );
	}
	else if ( jumpStm ) {
		munchStm( jumpStm );
	}
	else if ( cjumpStm ) {
		munchStm( cjumpStm );
	}
	else if ( labelStm ) {
		munchStm( labelStm );
	}
}

void CCodeGenerator::munchStm( const IRTree::SEQ* seq ) {
	munchStm( seq->GetLeft() );
	munchStm( seq->GetRight() );
}

void CCodeGenerator::munchStm( const IRTree::MOVE* move ) {
	// Проверяем частный случай, когда мы вызываем функцию и куда-то передаём полученное значение
	if ( munchFunctionCall( move ) ) {
		return;
	}

	// Получаем левую и правую части
	const IRTree::MEM* destinationMemory = _helper.IsMEM(move->GetDst());
	const IRTree::MEM* sourceMemory = _helper.IsMEM( move->GetSrc() );

	// const Temp::CTemp* s0 = munchExp( destinationMemory ? destinationMemory->GetExp() : nullptr );
	// const Temp::CTemp* s1 = munchExp( sourceMemory ? sourceMemory->GetExp() : nullptr );
	const Temp::CTemp* s0 = munchExp( destinationMemory ? destinationMemory->GetExp() : move->GetDst() );
	const Temp::CTemp* s1 = munchExp( sourceMemory ? sourceMemory->GetExp() : move->GetSrc() );

	// Случай 0: обе части - обращения по памяти
	if ( destinationMemory && sourceMemory ) {	
		// Промежуточная переменная
		Temp::CTemp* t = new Temp::CTemp();

		// Добавляем две операции
		emit(new MOVE("\tMOV `d0, [`s0]", t,  s0));
		emit( new MOVE("\tMOV [`d0], `s0", s1, t ) );
	}
	// Случай 1: левая часть - обращение по памяти, правая - нет
	if ( destinationMemory && !sourceMemory ) {
		emit( new MOVE( "\tMOV [`d0], `s0", s0, s1 ) );
	}
	// Случай 2: правая часть - обращение по памяти, левая - нет
	if ( sourceMemory && !destinationMemory ) {
		emit( new MOVE( "\tMOV `d0, [`s0]", s0, s1 ) );
	}
	// Случай 3: обе части - просто какие-то выражения
	if ( !sourceMemory && !destinationMemory ) {
		emit( new MOVE( "\tMOV `d0, `s0", s0, s1 ) );
	}
}

void CCodeGenerator::munchStm( const IRTree::EXP* exp ) {
	// Пытаемся обработать вызов процедуры
	if ( munchProcedureCall( exp ) ) {
		return;
	}

	Temp::CTemp* d0 = new Temp::CTemp();
	const Temp::CTemp* s0 = munchExp( exp->GetExp() );
	emit( new MOVE( "\tMOV `d0 <- `s0", d0, s0 ) );
}

void CCodeGenerator::munchStm( const IRTree::LABEL* label ) {
	emit(new LABEL(label->GetLabel()->Name() + ": ", label->GetLabel()));
}

void CCodeGenerator::munchStm( const IRTree::JUMP* jump ) {
	const Temp::CLabel* label = jump->GetTargets()->GetHead();
	emit( new OPER( "\tJUMP `j0", nullptr, nullptr, L(label)));
}

void CCodeGenerator::munchStm( const IRTree::CJUMP* cjump ) {
	const Temp::CLabel* trueLabel = cjump->GetIfTrue();
	const Temp::CLabel* falseLabel = cjump->GetIfFalse();

	const Temp::CTemp* leftArg = munchExp( cjump->GetLeft() );
	const Temp::CTemp* rightArg = munchExp( cjump->GetRight() );

	// Создаёт команду сравнения
	emit(new OPER("\tCMP `s0, `s1", nullptr, L(leftArg, rightArg)));

	// В зависимости от операции генерируем две команды перехода
	switch( cjump->GetRelop() ) {
		case IRTree::CJ_EQ:
			emit( new OPER( "\tJE `j0", nullptr, nullptr, L( trueLabel ) ) );
			emit( new OPER( "\tJNE `j0", nullptr, nullptr, L( falseLabel ) ) );
			break;
		case IRTree::CJ_NE:
			emit( new OPER( "\tJNE `j0", nullptr, nullptr, L( trueLabel ) ) );
			emit( new OPER( "\tJE `j0", nullptr, nullptr, L( falseLabel ) ) );
			break;
		case IRTree::CJ_GT:
			emit( new OPER( "\tJG `j0", nullptr, nullptr, L( trueLabel ) ) );
			emit( new OPER( "\tJLE `j0", nullptr, nullptr, L( falseLabel ) ) );
			break;
		case IRTree::CJ_LT:
			emit( new OPER( "\tJL `j0", nullptr, nullptr, L( trueLabel ) ) );
			emit( new OPER( "\tJGE `j0", nullptr, nullptr, L( falseLabel ) ) );
			break;
		case IRTree::CJ_GE:
			emit( new OPER( "\tJGE `j0", nullptr, nullptr, L( trueLabel ) ) );
			emit( new OPER( "\tJL `j0", nullptr, nullptr, L( falseLabel ) ) );
			break;
		case IRTree::CJ_LE:
			emit( new OPER( "\tJLE `j0", nullptr, nullptr, L( trueLabel ) ) );
			emit( new OPER( "\tJG `j0", nullptr, nullptr, L( falseLabel ) ) );
			break;
		default:
			break;
	}
}

// === IExp ===
const Temp::CTemp* CCodeGenerator::munchExp( const IRTree::IExp* expression )
{
	const IRTree::MEM* memExp = _helper.IsMEM( expression );
	const IRTree::BINOP* binopExp = _helper.IsBINOP( expression );
	const IRTree::CONST* constExp = _helper.IsCONST( expression );
	const IRTree::CALL* callExp = _helper.IsCALL( expression );
	const IRTree::NAME* nameExp = _helper.IsNAME( expression );
	const IRTree::TEMP* tempExp = _helper.IsTEMP( expression );

	if ( memExp ) {
		return munchExp( memExp );
	}
	else if ( binopExp ) {
		return munchExp( binopExp );
	}
	else if ( constExp ) {
		return munchExp( constExp );
	}
	else if ( callExp ) {
		return munchExp( callExp );
	}
	else if ( nameExp ) {
		return munchExp( nameExp );
	}
	else if ( tempExp ) {
		return munchExp( tempExp );
	}
	else {
		return nullptr;
	}
}

const Temp::CTemp* CCodeGenerator::munchExp( const IRTree::CONST* constExp )
{
	Temp::CTemp* r = new Temp::CTemp();
	std::string command = "\tMOV `d0, " + std::to_string( constExp->GetValue() );
	emit( new MOVE( command, r, nullptr ) );
	return r;
}

const Temp::CTemp* CCodeGenerator::munchExp( const IRTree::NAME* name )
{
	return nullptr;
}

const Temp::CTemp* CCodeGenerator::munchExp( const IRTree::TEMP* temp ) {
	return temp->GetTemp();
}

const Temp::CTemp* CCodeGenerator::munchExp( const IRTree::BINOP* binop )
{
	Temp::CTemp* r = new Temp::CTemp();
	const Temp::CTemp* leftOperand = munchExp( binop->GetLeft() );
	const Temp::CTemp* rightOperand = munchExp( binop->GetRight() );
	// Заносим первый аргумент в промежуточную переменную
	emit( new MOVE("\tMOV `d0, `s0", r, leftOperand) );
	// Применяем операцию
	switch( binop->GetBinop() ) {
		case IRTree::BO_PLUS:
			emit( new OPER( "\tADD `d0, `s0", L( r ), L( rightOperand ) ) );
			break;
		case IRTree::BO_MINUS:
			emit( new OPER( "\tSUB `d0, `s0", L( r ), L( rightOperand ) ) );
			break;
		case IRTree::BO_MUL:
			emit( new OPER( "\tIMUL `d0, `s0", L( r ), L( rightOperand ) ) );
			break;
		case IRTree::BO_DIV:
			// TIP: деление в x86 привязано к регистрам
			break;
		case IRTree::BO_AND:
			emit( new OPER( "\tAND `d0, `s0", L( r ), L( rightOperand ) ) );
			break;
		case IRTree::BO_OR:
			emit( new OPER( "\tOR `d0, `s0", L( r ), L( rightOperand ) ) );
			break;
		case IRTree::BO_XOR:
			emit( new OPER( "\tXOR `d0, `s0", L( r ), L( rightOperand ) ) );
			break;
		default:
			break;
	}
	// Возвращаем результат
	return r;
}

const Temp::CTemp* CCodeGenerator::munchExp( const IRTree::MEM* mem )
{
	const Temp::CTemp* r = new Temp::CTemp();
	const Temp::CTemp* m = munchExp( mem->GetExp() );
	// Заносим значение по ячейке памяти
	emit( new MOVE("\tMOV `d0, [`s0]", r, m));

	// Возвращаем значение
	return r;
}

const Temp::CTemp* CCodeGenerator::munchExp( const IRTree::CALL* call )
{
	return nullptr;
}

const Temp::CTempList* CCodeGenerator::munchArgs( const IRTree::CExpList* expList )
{
	const IRTree::CExpList* list = expList;

	std::list<const Temp::CTemp*> temps;

	while ( list ) {
		const IRTree::IExp* currentExrpession = list->GetHead();
		temps.push_back( munchExp( currentExrpession ) );
		// Переходим к следующему аргументу
		list = list->GetTail();
	}

	// Оборачиваем полученные переменные в CTempList
	Temp::CTempList* tempsList = nullptr;
	for ( auto temp = temps.begin(); temp != temps.end(); temp++ ) {
		tempsList = new Temp::CTempList( *temp, tempsList );
	}

	// Возвращаем результат
	return tempsList;
}

bool CCodeGenerator::munchFunctionCall( const IRTree::MOVE* move ) {
	const IRTree::TEMP* tempExp = _helper.IsTEMP( move->GetDst() );
	const IRTree::CALL* callExp = _helper.IsCALL( move->GetSrc() );
	if ( !tempExp || !callExp ) {
		return false;
	}
	
	// Обрабатываем вызов функции	
	munchProcedureCall( new IRTree::EXP(callExp) );
	
	const Temp::CTemp* resultTemp = munchExp(tempExp);
	emit( new MOVE("\tMOV `d0, EAX", resultTemp, nullptr) );

	return true;
}

bool CCodeGenerator::munchProcedureCall( const IRTree::EXP* exp ) {
	const IRTree::CALL* callExp = _helper.IsCALL( exp->GetExp() );
	if ( !callExp ) {
		return false;
	}
	// Обрабатываем вызов функции

	const Temp::CTemp* r = munchExp( callExp->GetFunc() );
	const IRTree::NAME* functionName = dynamic_cast< const IRTree::NAME* >( callExp->GetFunc() );
	assert( functionName != 0 );
	const Temp::CTempList* l = munchArgs( callExp->GetArgs() );

	const Temp::CTempList* list = l;
	while ( list != 0 ) {
		const Temp::CTemp* temp = list->GetHead();
		
		emit( new OPER("\tPUSH `s0", _methodFrame->GetCallDefArgs(), L(temp), nullptr) );

		list = list->GetTail();
	}
	
	emit(new OPER("\tCALL " + functionName->GetLabel()->Name(), nullptr, new Temp::CTempList(r, l)));
	// TODO: calldefs - модифицируемые call'ом регистры/переменные
	return true;
}