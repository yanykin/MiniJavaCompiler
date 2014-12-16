/*
* Для каждого правила нетерминала создаём класс
*/
#pragma once
#include "GrammaticSymbols.h"
#include "TerminalSymbols.h"
#include "Visitor.h"
#include "CoordinatesHolder.h"
#include <vector>

// Вся программа
class CProgram : public IProgram, public CCoordinatesHolder
{
public:
	CProgram(const YYLTYPE& yylloc, IMainClassDeclaration *_mainClassDeclaration, IClassDeclaration *_classDeclarationList ) :
		CCoordinatesHolder( yylloc ), mainClassDeclaration( _mainClassDeclaration ), classDeclarationsList( _classDeclarationList ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };
	IMainClassDeclaration* GetMainClassDeclaration() const { return mainClassDeclaration; };
	IClassDeclaration* GetClassDeclarationsList() const { return classDeclarationsList; };
private:
	IMainClassDeclaration *mainClassDeclaration; // объявление главного класса
	IClassDeclaration *classDeclarationsList; // список объявлений классов
};

// Определение главного класса
class CMainClassDeclaration : public IMainClassDeclaration, public CCoordinatesHolder
{
public:
	CMainClassDeclaration( const YYLTYPE& yylloc, CIdentifier *_className, CIdentifier *_argumentName, IStatement *_statement ) :
		CCoordinatesHolder( yylloc ), className( _className ), argumentName( _argumentName ), statement( _statement ) { };
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetClassName() const { return className->getString(); };
	std::string GetArgumentName() const { return argumentName->getString(); };
	IStatement* GetClassStatements() const { return statement; };

private:
	CIdentifier *className; // Название класса
	CIdentifier *argumentName; // Имя аргумента
	IStatement *statement; // Тело класса 
};

// Определение класса
class CClassDeclaration : public IClassDeclaration, public CCoordinatesHolder
{
public:
	CClassDeclaration( const YYLTYPE& yylloc, CIdentifier *_className, IVariableDeclaration *_fieldsList, IMethodDeclaration *_methodsList ) :
		CCoordinatesHolder( yylloc ), className( _className ), fieldsList( _fieldsList ), methodsList( _methodsList ) { };
	std::string getClassName() const;
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetClassName() const { return className->getString(); };
	IVariableDeclaration* GetFieldsList() const { return fieldsList; };
	IMethodDeclaration* GetMethodsList() const { return methodsList; };

private:
	CIdentifier *className; // Название класса
	IVariableDeclaration *fieldsList; // Список полей класса
	IMethodDeclaration *methodsList; // Перечисление методов 
};

// Список определений классов
class CClassDeclarationList : public IClassDeclaration, public CCoordinatesHolder
{
public:
	CClassDeclarationList( const YYLTYPE& yylloc, IClassDeclaration *_classDeclaration, IClassDeclaration *_nextClassDeclaration ) :
		CCoordinatesHolder( yylloc ), classDeclaration( _classDeclaration ), nextClassDeclaration( _nextClassDeclaration ) { };
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IClassDeclaration* GetClassDeclaration() const { return classDeclaration; };
	IClassDeclaration *GetNextClassDeclaration() const { return nextClassDeclaration; };

private:
	IClassDeclaration *classDeclaration; // связанные данные элемента списка
	IClassDeclaration *nextClassDeclaration; // ссылка на следующий элемент
};

// Определение класса, который наследуется от существующего
class CClassExtendsDeclaration : public IClassDeclaration, public CCoordinatesHolder
{
public:
	CClassExtendsDeclaration( const YYLTYPE& yylloc, CIdentifier *_className, CIdentifier *_superClassName, IVariableDeclaration *_fieldsList, IMethodDeclaration *_methodsList ) :
		CCoordinatesHolder( yylloc ), className( _className ), superClassName( _superClassName ), fieldsList( _fieldsList ), methodsList( _methodsList ) { };
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetClassName() const { return className->getString(); };
	std::string GetSuperClassName() const { return superClassName->getString(); };
	IVariableDeclaration* GetFieldsList() const { return fieldsList; };
	IMethodDeclaration* GetMethodsList() const { return methodsList; };
private:
	CIdentifier *className; // Название класса
	CIdentifier *superClassName; // Название класса, от которого происходит наследование
	IVariableDeclaration *fieldsList; // Список полей класса
	IMethodDeclaration *methodsList; // Перечисление методов 
};

// Определение переменной
class CVariableDeclaration : public IVariableDeclaration, public CCoordinatesHolder
{
public:
	CVariableDeclaration( const YYLTYPE& yylloc, IType *_type, CIdentifier *_variableName ) :
		CCoordinatesHolder( yylloc ), type( _type ), variableName( _variableName ) { };
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetName() const { return variableName->getString(); };
	IType* GetType() const { return type;  };
private:
	IType *type; // тип данных
	CIdentifier *variableName; // имя переменной	
};

// Список определений переменных
class CVariableDeclarationList : public IVariableDeclaration, public CCoordinatesHolder
{
public:
	CVariableDeclarationList( const YYLTYPE& yylloc, IVariableDeclaration *_variableDeclaration, CVariableDeclarationList *_nextVariableDeclaration ) :
		CCoordinatesHolder( yylloc ), variableDeclaration( _variableDeclaration ), nextVariableDeclaration( _nextVariableDeclaration ) { };
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	CVariableDeclarationList* GetNextVariableDeclaration() const { return nextVariableDeclaration; };
	IVariableDeclaration* GetVariableDeclaration() const { return variableDeclaration; };

private:
	IVariableDeclaration *variableDeclaration; // связанные данные
	CVariableDeclarationList *nextVariableDeclaration; // ссылка на следующий элемент
};

// Определение метода
class CMethodDeclaration : public IMethodDeclaration, public CCoordinatesHolder
{
public:
	CMethodDeclaration( const YYLTYPE& yylloc, IType *_type, CIdentifier *_methodName, IFormalList *_formalList, IVariableDeclaration *_localVariablesList, IStatement *_statementList, IExpression *_returnExpression ) :
		CCoordinatesHolder( yylloc ), type( _type ), methodName( _methodName ), formalList( _formalList ), localVariablesList( _localVariablesList ), statementList( _statementList ), returnExpression( _returnExpression ) { }
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetMethodName() const {return methodName->getString(); };
	IType* GetType() const { return type; };
	IFormalList* GetFormalList() const { return formalList; };
	IStatement* GetStatements() const { return statementList; };

	IVariableDeclaration* GetLocalVariablesList() const { return localVariablesList; };

	IExpression* GetReturnExpression() const { return returnExpression; };

private:
	IType *type; // тип данных, который возвращает этот тип
	CIdentifier *methodName; // имя метода
	IFormalList *formalList; // перечисление аргументов
	IVariableDeclaration *localVariablesList; // локальные переменные метода
	IStatement *statementList; // непосредственно код метода
	IExpression *returnExpression; // значение, которое будет возвращаться методом
};

// Список определений методов
class CMethodDeclarationList : public IMethodDeclaration, public CCoordinatesHolder
{
public:
	CMethodDeclarationList( const YYLTYPE& yylloc, IMethodDeclaration *_methodDeclaration, IMethodDeclaration *_nextMethodDeclaration ) :
		CCoordinatesHolder( yylloc ), methodDeclaration( _methodDeclaration ), nextMethodDeclaration( _nextMethodDeclaration ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IMethodDeclaration* GetMethodDeclaration() const { return methodDeclaration; };
	IMethodDeclaration* GetNextMethodDeclaration() const { return nextMethodDeclaration; };

private:
	IMethodDeclaration *methodDeclaration; // определение метода (связанные данные)
	IMethodDeclaration *nextMethodDeclaration; // ссылка на следующее определение метода
};

// Список параметров метода
class CFormalList : public IFormalList, public CCoordinatesHolder
{
public:
	CFormalList( const YYLTYPE& yylloc, IType *_type, CIdentifier *_parameterName ) :
		CCoordinatesHolder( yylloc ), type( _type ), parameterName( _parameterName ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetParameterName() const { return parameterName->getString(); };
	IType* GetType() const { return type; };

private:
	IType *type; // тип переменной
	CIdentifier *parameterName; // имя переменной
	// std::vector<IFormalRest> *formalRest; // указатель на остаток списка
	// IFormalList *nextInList; // следующий параметр в списке
};

class CFormalRestList : public IFormalList, public CCoordinatesHolder
{
public:
	CFormalRestList( const YYLTYPE& yylloc, IFormalList *_formalRest, IFormalList *_nextFormalRest ) :
		CCoordinatesHolder( yylloc ), formalRest( _formalRest ), nextFormalRest( _nextFormalRest ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IFormalList* GetFormalRest() const { return formalRest; };
	IFormalList* GetNextFormalRest() const { return nextFormalRest; };

private:
	IFormalList *formalRest; // параметр
	IFormalList *nextFormalRest; // следующий параметр
};

/*
// Пустой список параметров метода
class CEmptyFormalList : public IFormalList, public CCoordinatesHolder
{
public:
	CEmptyFormalList() { };
};
*/

/*
// "Хвостовой" элемент перечисления параметров метода
class CFormalRest : public IFormalRest, public CCoordinatesHolder
{
public:
	CFormalRest( IType *_type, CIdentifier *_parameterName ) :
		type( _type ), parameterName( _parameterName ) { };
private:
	IType *type; // тип переменной
	CIdentifier *parameterName; // имя переменной
};
*/

// Перечисление встроенных типов данных
enum TBuiltInType {
	BT_INTEGER,
	BT_INTEGER_ARRAY,
	BT_BOOLEAN
};

// Класс, задающий встроенный тип данных
class CBuiltInType : public IType, public CCoordinatesHolder {
public:
	CBuiltInType( const YYLTYPE& yylloc, TBuiltInType _type ) : CCoordinatesHolder( yylloc ), type( _type ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	TBuiltInType GetType() const { return type; };
private:
	TBuiltInType type;
};

// Класс, задающий пользовательский тип данных
class CUserType : public IType, public CCoordinatesHolder {
public:
	CUserType( const YYLTYPE& yylloc, CIdentifier *_typeName ) : CCoordinatesHolder( yylloc ), typeName( _typeName ) { };
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetTypeName() const { return typeName->getString(); }
private:
	CIdentifier *typeName; // название класса
};

/* ОПЕРАТОРЫ */
// Построение списка операторов
class CStatementList : public IStatement, public CCoordinatesHolder
{
public:
	CStatementList( const YYLTYPE& yylloc, IStatement *_statement, IStatement *_nextStatement ) :
		CCoordinatesHolder( yylloc ), statement( _statement ), nextStatement( _nextStatement ) { };
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IStatement* GetStatement() const { return statement; };
	IStatement* GetNextStatement() const { return nextStatement; };

private:
	IStatement *statement; // целевые данные элемента
	IStatement *nextStatement; // следующий элемент списка
};

// Перечисление операторов в блоке кода
class CStatementBlock : public IStatement, public CCoordinatesHolder
{
public:
	CStatementBlock( const YYLTYPE& yylloc, IStatement *_statementsList ) : CCoordinatesHolder( yylloc ), statementsList( _statementsList ) { };
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IStatement* GetStatementList() const { return statementsList; };

private:
	IStatement *statementsList; // операторы в данном блоке
};

// Условный оператор
class CIfStatement : public IStatement, public CCoordinatesHolder
{
public:
	CIfStatement( const YYLTYPE& yylloc, IExpression *_condition, IStatement *_trueStatement, IStatement *_falseStatement ) :
		CCoordinatesHolder( yylloc ), condition( _condition ), trueStatement( _trueStatement ), falseStatement( _falseStatement ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IStatement* GetTrueStatement() const { return trueStatement; };
	IStatement* GetFalseStatement() const { return falseStatement; };

	IExpression* GetCondition() const { return condition; };

private:
	IExpression *condition; // условие, которое должно выполняться
	IStatement *trueStatement; // оператор, выполняемый при истинном условии
	IStatement *falseStatement; // оператор, выполняемый при ложном условии
};

// Оператор while
class CWhileStatement : public IStatement, public CCoordinatesHolder
{
public:
	CWhileStatement( const YYLTYPE& yylloc, IExpression *_condition, IStatement *_trueStatement ) :
		CCoordinatesHolder( yylloc ), condition( _condition ), trueStatement( _trueStatement ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IStatement* GetStatement() const { return trueStatement; };
	IExpression* GetCondition() const { return condition; };

private:
	IExpression *condition; // условие, которое должно выполняться
	IStatement *trueStatement; // оператор, выполняемый при истинном условии
};

// Оператор печати
class CPrintStatement : public IStatement, public CCoordinatesHolder
{
public:
	CPrintStatement( const YYLTYPE& yylloc, IExpression *_expressionToPrint ) :
		CCoordinatesHolder( yylloc ), expressionToPrint( _expressionToPrint ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IExpression* GetExpression() const { return expressionToPrint; };
private:
	IExpression *expressionToPrint; // выражение, значение которого будет печататься
};

// Операция присваивания
class CAssignmentStatement : public IStatement, public CCoordinatesHolder
{
public:
	CAssignmentStatement( const YYLTYPE& yylloc, CIdentifier *_variableName, IExpression *_rightValue ) :
		CCoordinatesHolder( yylloc ), variableName( _variableName ), rightValue( _rightValue ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetVariableName() const { return variableName->getString(); };
	IExpression* GetRightValue() const { return rightValue; };
private:
	CIdentifier *variableName; // имя переменной, которой будет присваиваться значение
	IExpression *rightValue; // присваиваемое значение
};

// Операция присваивания элементу массива
class CArrayElementAssignmentStatement : public IStatement, public CCoordinatesHolder
{
public:
	CArrayElementAssignmentStatement( const YYLTYPE& yylloc, CIdentifier *_arrayName, IExpression *_indexExpression, IExpression *_rightValue ) :
		CCoordinatesHolder( yylloc ), arrayName( _arrayName ), indexExpression( _indexExpression ), rightValue( _rightValue ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetArrayName() const { return arrayName->getString(); };
	IExpression* GetIndexExpression() const { return indexExpression; };
	IExpression* GetRightValue() const { return rightValue; };

private:
	CIdentifier *arrayName; // имя массива
	IExpression *indexExpression; // индекс массива
	IExpression *rightValue; // присваиваемое значение
};

/* ВЫРАЖЕНИЯ */
// Бинарная операция
enum TBinaryOperator {
	BO_PLUS,		// сумма
	BO_MINUS,		// разность
	BO_MULTIPLY,	// произведение
	BO_LESS,		// меньше
	BO_LOGICAL_AND,	// логическое "И"
};

class CBinaryOperatorExpression : public IExpression, public CCoordinatesHolder
{
public:
	CBinaryOperatorExpression( const YYLTYPE& yylloc, IExpression *_leftValue, IExpression *_rightValue, TBinaryOperator _binaryOperator ) :
		CCoordinatesHolder( yylloc ), leftValue( _leftValue ), rightValue( _rightValue ), binaryOperator( _binaryOperator ) { }
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IExpression* GetLeftValue() const { return leftValue; };
	IExpression* GetRightValue() const { return rightValue; };
	TBinaryOperator GetOperator() const { return binaryOperator;  };

private:
	IExpression *leftValue; // значение слева
	IExpression *rightValue; // значение справа
	TBinaryOperator binaryOperator;
};

// Операция доступа к элементу массива
class CIndexAccessExpression : public IExpression, public CCoordinatesHolder
{
public:
	CIndexAccessExpression( const YYLTYPE& yylloc, IExpression *_arrayExpression, IExpression *_index ) :
		CCoordinatesHolder( yylloc ), arrayExpression( _arrayExpression ), index( _index ) { };
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IExpression* GetArrayExpression() const { return arrayExpression; };
	IExpression* GetIndex() const { return index; };
private:
	IExpression *arrayExpression; // массив, к которому хотим обратиться
	IExpression *index; // индекс элемента
};

// Получение длины массива
class CLengthExpression : public IExpression, public CCoordinatesHolder
{
public:
	CLengthExpression( const YYLTYPE& yylloc, IExpression *_arrayExpression ) : CCoordinatesHolder( yylloc ), arrayExpression( _arrayExpression ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IExpression* GetArray() const { return arrayExpression; };
private:
	IExpression *arrayExpression; // массив, к которому хотим обратиться
};

// Вызов метода объекта
class CMethodCallExpression : public IExpression, public CCoordinatesHolder
{
public:
	CMethodCallExpression( const YYLTYPE& yylloc, IExpression *_variableExpression, CIdentifier *_methodName, IExpression *_expressionList ) :
		CCoordinatesHolder( yylloc ), variableExpression( _variableExpression ), methodName( _methodName ), expressionList( _expressionList ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IExpression* GetObject() const { return variableExpression; };
	IExpression* GetParams() const { return expressionList; };
	std::string GetMethodName() const { return methodName->getString(); }

private:
	IExpression *variableExpression; // переменная или объект, у которой вызываем метод
	CIdentifier *methodName; // имя метода, который мы вызываем
	IExpression *expressionList; // список аргументов, которые мы передаём методу
};

enum TValueType {
	VT_INTEGER,
	VT_BOOLEAN
};
// Целочисленное и булево значение
class CIntegerOrBooleanExpression : public IExpression, public CCoordinatesHolder
{
public:
	CIntegerOrBooleanExpression( const YYLTYPE& yylloc, int _value, TValueType _valueType ) :
		CCoordinatesHolder( yylloc ), value( _value ), valueType( _valueType ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	int GetValue() const { return value; };
	TValueType GetValueType() const { return valueType; };

private:
	int value; // значение переменной
	TValueType valueType; // тип переменной 
};

// Получение значения переменной
class CIdentifierExpression : public IExpression, public CCoordinatesHolder
{
public:
	CIdentifierExpression( const YYLTYPE& yylloc, CIdentifier *_variableName ) : CCoordinatesHolder( yylloc ), variableName( _variableName ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetVariableName() const { return variableName->getString(); };
private:
	CIdentifier *variableName; // имя переменной, значение которой мы хотим получить
};

// Получение ссылки на объект по ключевому слову this
class CThisExpression : public IExpression, public CCoordinatesHolder
{
public:
	CThisExpression( const YYLTYPE& yylloc ) : CCoordinatesHolder( yylloc ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };
};

// Создание нового массива из int
class CNewIntegerArrayExpression : public IExpression, public CCoordinatesHolder
{
public:
	CNewIntegerArrayExpression( const YYLTYPE& yylloc, IExpression *_arraySize ) : CCoordinatesHolder( yylloc ), arraySize( _arraySize ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IExpression* GetArraySize() const { return arraySize; };
private:
	IExpression *arraySize; // размер массива
};

// Создание нового объекта определённого класса
class CNewObjectExpression : public IExpression, public CCoordinatesHolder
{
public:
	CNewObjectExpression( const YYLTYPE& yylloc, CIdentifier *_className ) : CCoordinatesHolder( yylloc ), className( _className ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetClass() const { return className->getString(); };
private:
	CIdentifier *className; // класс, объект которого мы хотим создать
};

// Операция отрицания
class CNegationExpression : public IExpression, public CCoordinatesHolder
{
public:
	CNegationExpression( const YYLTYPE& yylloc, IExpression *_argument ) : CCoordinatesHolder( yylloc ), argument( _argument ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IExpression* GetArgument() const { return argument; };
private:
	IExpression *argument; // значение, отрицание которого мы хотим получить
};

// Скобки
class CParenthesesExpression : public IExpression, public CCoordinatesHolder
{
public:
	CParenthesesExpression( const YYLTYPE& yylloc, IExpression *_expression ) : CCoordinatesHolder( yylloc ), expression( _expression ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IExpression* GetExpression() const { return expression; };
private:
	IExpression *expression; // выражение в скобках
};

// Список выражений
class CExpressionList : public IExpression, public CCoordinatesHolder
{
public:
	CExpressionList( const YYLTYPE& yylloc, IExpression *_expression, IExpression *_nextExpression ) :
		CCoordinatesHolder( yylloc ), expression( _expression ), nextExpression( _nextExpression ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IExpression* GetExpression() const { return expression; };
	IExpression* GetNextExpression() const { return nextExpression; };

private:
	IExpression *expression; // целевое значение элемента списка - выражение
	IExpression *nextExpression; // следующий элемент списка
};
