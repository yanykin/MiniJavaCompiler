#include "Instruction.h"
#include <string>

using namespace CodeGeneration;

void CCodeGenerator::emit(IInstruction* instruction)  {
	_instructions.push_back( instruction );
}

std::list<IInstruction*> CCodeGenerator::generateCode( IRTree::IStm* rootStatement ) {
	std::list<IInstruction*> instructions;
	munchStm( rootStatement );
	instructions.insert( instructions.begin(), _instructions.begin(), _instructions.end() );
	_instructions.clear();

	return instructions;
}

// === IStm ===
void CCodeGenerator::munchStm( const IRTree::IStm* statement ) {
	if ( !statement ) {
		return;
	}
	const IRTree::MOVE* move = _helper.IsMOVE( statement );
	if ( move ) {
		munchStm( move );
	}
	
}

void CCodeGenerator::munchStm( const IRTree::SEQ* seq ) {
	munchStm( seq->GetLeft() );
	munchStm( seq->GetRight() );
}

void CCodeGenerator::munchStm( const IRTree::MOVE* move ) {
	// Получаем левую и правую части
	const IRTree::MEM* destinationMemory = _helper.IsMEM(move->GetDst());
	const IRTree::MEM* sourceMemory = _helper.IsMEM( move->GetSrc() );

	Temp::CTemp* s0 = munchExp( destinationMemory->GetExp() );
	Temp::CTemp* s1 = munchExp( sourceMemory->GetExp() );

	// Случай 0: обе части - обращения по памяти
	if ( destinationMemory && sourceMemory ) {	
		// Промежуточная переменная
		Temp::CTemp* t = new Temp::CTemp();

		// Добавляем две операции
		emit(new OPER("MOV `s0, [`s1]", nullptr, L(t, s0)));
		emit( new OPER( "MOV [`s0], `s1]", nullptr, L( s1, t ) ) );
	}
	// Случай 1: левая часть - обращение по памяти, правая - нет
	if ( destinationMemory && !sourceMemory ) {
		emit( new OPER( "MOV [`s0], `s1]", nullptr, L( s0, s1 ) ) );
	}
	// Случай 2: правая часть - обращение по памяти, левая - нет
	if ( sourceMemory && !destinationMemory ) {
		emit( new OPER( "MOV `s0, [`s1]", nullptr, L( s0, s1 ) ) );
	}
	// Случай 3: обе части - просто какие-то выражения
	if ( !sourceMemory && !destinationMemory ) {
		emit( new OPER( "MOV `s0, `s1", nullptr, L( s0, s1 ) ) );
	}
}

void CCodeGenerator::munchStm( const IRTree::EXP* exp ) {
	// Проверяем тип дочернего узла
	const IRTree::CALL* call = _helper.IsCALL( exp->GetExp() );
	if ( call ) {
		Temp::CTemp* f = munchExp( call->GetFunc() );
		Temp::CTempList* l = munchArgs( call->GetArgs() );
		emit( new OPER("CALL `s0", nullptr, new Temp::CTempList(f, l)));
	}
	else {
		Temp::CTemp* d0 = new Temp::CTemp();
		Temp::CTemp* s0 = munchExp( exp->GetExp() );
		emit( new MOVE( "MOVE `d0, `s0", d0, s0 ) );
	}
	
}

void CCodeGenerator::munchStm( const IRTree::LABEL* label ) {
	emit(new LABEL(label->GetLabel()->Name() + ": ", label->GetLabel()));
}

void CCodeGenerator::munchStm( const IRTree::JUMP* jump ) {
	const Temp::CLabel* label = jump->GetTargets()->GetHead();
	emit( new OPER( "JUMP `j0", nullptr, nullptr, L(label)));
}

void CCodeGenerator::munchStm( const IRTree::CJUMP* cjump ) {
	const Temp::CLabel* trueLabel = cjump->GetIfTrue();
	const Temp::CLabel* falseLabel = cjump->GetIfFalse();

	Temp::CTemp* leftArg = munchExp( cjump->GetLeft() );
	Temp::CTemp* rightArg = munchExp( cjump->GetRight() );

	// Создаёт команду сравнения
	emit(new OPER("CMP `s0, `s1", nullptr, L(leftArg, rightArg)));

	// В зависимости от операции генерируем две команды перехода
	switch ( cjump->GetRelop() )
	{
	case CJ_EQ:
		emit( new OPER( "JE `j0", nullptr, nullptr, L( trueLabel ) ) );
		emit( new OPER( "JNE `j0", nullptr, nullptr, L( trueLabel ) ) );
		break;
	case CJ_NE:
		emit( new OPER( "JNE `j0", nullptr, nullptr, L( trueLabel ) ) );
		emit( new OPER( "JE `j0", nullptr, nullptr, L( trueLabel ) ) );
		break;
	case CJ_GT:
		emit( new OPER( "JG `j0", nullptr, nullptr, L( trueLabel ) ) );
		emit( new OPER( "JLE `j0", nullptr, nullptr, L( trueLabel ) ) );
		break;
	case CJ_LT:
		emit( new OPER( "JL `j0", nullptr, nullptr, L( trueLabel ) ) );
		emit( new OPER( "JGE `j0", nullptr, nullptr, L( trueLabel ) ) );
		break;
	case CJ_GE:
		emit( new OPER( "JGE `j0", nullptr, nullptr, L( trueLabel ) ) );
		emit( new OPER( "JL `j0", nullptr, nullptr, L( trueLabel ) ) );
		break;
	case CJ_LE:
		emit( new OPER( "JLE `j0", nullptr, nullptr, L( trueLabel ) ) );
		emit( new OPER( "JG `j0", nullptr, nullptr, L( trueLabel ) ) );
		break;
	default:
		break;
	}
}

// === IExp ===
Temp::CTemp* CCodeGenerator::munchExp( const IRTree::IExp* expression ) {
	return nullptr;
}

Temp::CTemp* CCodeGenerator::munchExp( const IRTree::CONST* constExp ) {
	Temp::CTemp* r = new Temp::CTemp();
	std::string command = "MOV `d0, " + std::to_string( constExp->GetValue() );
	emit( new MOVE( command, r, nullptr ) );
	return r;
}

Temp::CTemp* CCodeGenerator::munchExp( const IRTree::NAME* name ) {
	return nullptr;
}

const Temp::CTemp* CCodeGenerator::munchExp( const IRTree::TEMP* temp ) {
	return temp->GetTemp();
}

Temp::CTemp* CCodeGenerator::munchExp( const IRTree::BINOP* binop ) {
	Temp::CTemp* r = new Temp::CTemp();
	Temp::CTemp* leftOperand = munchExp( binop->GetLeft() );
	Temp::CTemp* rightOperand = munchExp( binop->GetRight() );
	// Заносим первый аргумент в промежуточную переменную
	emit( new MOVE("MOV `d0, `s0", r, leftOperand) );
	// Применяем операцию
	switch ( binop->GetBinop() )
	{
	case BO_PLUS:
		emit( new OPER( "ADD `d0, `s0", L(r), L(rightOperand) ) );
		break;
	case BO_MINUS:
		emit( new OPER( "SUB `d0, `s0", L( r ), L( rightOperand ) ) );
		break;
	case BO_MUL:
		emit( new OPER( "IMUL `d0, `s0", L( r ), L( rightOperand ) ) );
		break;
	case BO_DIV:
		// TIP: деление в x86 привязано к регистрам
		break;
	case BO_AND:
		emit( new OPER( "AND `d0, `s0", L( r ), L( rightOperand ) ) );
		break;
	case BO_OR:
		emit( new OPER( "OR `d0, `s0", L( r ), L( rightOperand ) ) );
		break;
	case BO_XOR:
		emit( new OPER( "XOR `d0, `s0", L( r ), L( rightOperand ) ) );
		break;
	default:
		break;
	}
	// Возвращаем результат
	return r;
}

Temp::CTemp* CCodeGenerator::munchExp( const IRTree::MEM* mem ) {
	Temp::CTemp* r = new Temp::CTemp();
	Temp::CTemp* m = munchExp( mem->GetExp() );
	// Заносим значение по ячейке памяти
	emit( new MOVE("MOV `d0, [`s0]", r, m));

	// Возвращаем значение
	return r;
}

Temp::CTemp* CCodeGenerator::munchExp( const IRTree::CALL* call ){
	return nullptr;
}

Temp::CTempList* CCodeGenerator::munchArgs( const IRTree::CExpList* expList ) {
	const IRTree::CExpList* list = expList;

	std::list<Temp::CTemp*> temps;

	const IRTree::IExp* currentExrpession = list->GetHead();
	while ( currentExrpession ) {
		temps.push_back( munchExp( currentExrpession ) );
		// Переходим к следующему аргументу
		list = list->GetTail();
	}

	// Оборачиваем полученные переменные в CTempList
	Temp::CTempList* tempsList = nullptr;
	for ( auto temp = temps.rbegin(); temp != temps.rend(); temp++ ) {
		tempsList = new Temp::CTempList( *temp, tempsList );
	}

	// Возвращаем результат
	return tempsList;
}