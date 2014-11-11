/*
* ƒл€ каждого правила нетерминала создаЄм класс
*/
#include "GrammaticSymbols.h"
#include "TerminalSymbols.h"
#include <vector>

// ќпределение главного класса
class CMainClassDeclaration : public IMainClassDeclaration
{
public:
	CMainClassDeclaration(CIdentifier *_className, CIdentifier *_argumentName, IStatement *_statement):
		className(_className), argumentName(_argumentName), statement(_statement) { };

private:
	CIdentifier *className; // Ќазвание класса
	CIdentifier *argumentName; // »м€ аргумента
	IStatement *statement; // “ело класса 
};

// ќпределение класса
class CClassDeclaration : public IClassDeclaration
{
public:
	CClassDeclaration( CIdentifier *_className, std::vector<IVariableDeclaration> *_fields, std::vector<IMethonDeclaration> *_methods ) :
		className( _className ), fields( _fields ), methods( _methods ) { };
private:
	CIdentifier *className; // Ќазвание класса
	std::vector<IVariableDeclaration> *fields; // ѕеречисление полей
	std::vector<IMethonDeclaration> *methods; // ѕеречисление методов 
};

// ќпределение класса, который наследуетс€ от существующего
class CClassExtendsDeclaration : public IClassDeclaration
{
public:
	CClassExtendsDeclaration( CIdentifier *_className, CIdentifier *_superClassName, std::vector<IVariableDeclaration> *_fields, std::vector<IMethonDeclaration> *_methods ) :
		className( _className ), superClassName( _superClassName ), fields( _fields ), methods( _methods ) { };
private:
	CIdentifier *className; // Ќазвание класса
	CIdentifier *superClassName; // Ќазвание класса, от которого происходит наследование
	std::vector<IVariableDeclaration> *fields; // ѕеречисление полей
	std::vector<IMethonDeclaration> *methods; // ѕеречисление методов 
};

// ќпределение переменной
class CVariableDeclaraion : public IVariableDeclaration
{
public:
	CVariableDeclaraion( IType *_type, CIdentifier *_variableName ) :
		type( _type ), variableName( _variableName ) { };
private:
	IType *type; // тип данных
	CIdentifier *variableName; // им€ переменной
};

// ќпределение метода
class CMethodDeclaration : public IMethonDeclaration
{
public:
	CMethodDeclaration( IType *_type, CIdentifier *_methodName, IFormalList *_formalList, std::vector<IVariableDeclaration> *_localVariables, std::vector<IStatement> *_statements, IExpression *_returnExpression ) :
		type( _type ), methodName( _methodName ), formalList( _formalList ), localVariables( _localVariables ), statements( _statements ), returnExpression( _returnExpression ) { }
private:
	IType *type; // тип данных, который возвращает этот тип
	CIdentifier *methodName; // им€ метода
	IFormalList *formalList; // перечисление аргументов
	std::vector<IVariableDeclaration> *localVariables; // локальные переменные метода
	std::vector<IStatement> *statements; // непосредственно код метода
	IExpression *returnExpression; // значение, которое будет возвращатьс€ методом
};

// —писок параметров метода
class CFormalList : public IFormalList
{
public:
	CFormalList( IType *_type, CIdentifier *_parameterName, std::vector<IFormalRest> *_formalRest ) :
		type(_type), parameterName(_parameterName), formalRest(_formalRest) {}
private:
	IType *type; // тип переменной
	CIdentifier *parameterName; // им€ переменной
	std::vector<IFormalRest> *formalRest; // указатель на остаток списка
};

// ѕустой список параметров метода
class CEmptyFormalList : public IFormalList
{
public:
	CEmptyFormalList() { };
};

// "’востовой" элемент перечислени€ параметров метода
class CFormalRest : public IFormalRest
{
public:
	CFormalRest( IType *_type, CIdentifier *_parameterName ) :
		type( _type ), parameterName( _parameterName ) { };
private:
	IType *type; // тип переменной
	CIdentifier *parameterName; // им€ переменной
};

// ѕеречисление встроенных типов данных
enum TBuiltInType {
	BT_INTEGER,
	BT_INTEGER_ARRAY,
	BT_BOOLEAN
};

//  ласс, задающий встроенный тип данных
class CBulitInType : public IType {
public:
	CBulitInType( TBuiltInType _type ) : type( _type ) {};
private:
	TBuiltInType type;
};

//  ласс, задающий пользовательский тип данных
class CUserType : public IType {
public:
	CUserType( CIdentifier *_typeName ) : typeName( _typeName ) { };
private:
	CIdentifier *typeName; // название класса
};

// ѕеречисление операторов в блоке кода
class CStatementBlock : public IStatement
{
public:
	CStatementBlock( std::vector<IStatement> *_statements ) : statements( _statements ) { };
private:
	std::vector<IStatement> *statements; // операторы в данном блоке
};

// ”словный оператор
class CIfStatement : public IStatement
{
public:
	CIfStatement( IExpression *_condition, IStatement *_trueStatement, IStatement *_falseStatement ) :
		condition( _condition ), trueStatement( _trueStatement ), falseStatement( _falseStatement ) { };
private:
	IExpression *condition; // условие, которое должно выполн€тьс€
	IStatement *trueStatement; // оператор, выполн€емый при истинном условии
	IStatement *falseStatement; // оператор, выполн€емый при ложном условии
};

// ќператор while
class CWhileStatement : public IStatement
{
	CWhileStatement( IExpression *_condition, IStatement *_trueStatement ) :
		condition( _condition ), trueStatement( _trueStatement ){ };
private:
	IExpression *condition; // условие, которое должно выполн€тьс€
	IStatement *trueStatement; // оператор, выполн€емый при истинном условии
};

// ќператор печати
class CPrintStatement : public IStatement
{
public:
	CPrintStatement( IExpression *_expressionToPrint ) :
		expressionToPrint( _expressionToPrint ) {};
private:
	IExpression *expressionToPrint; // выражение, значение которого будет печататьс€
};