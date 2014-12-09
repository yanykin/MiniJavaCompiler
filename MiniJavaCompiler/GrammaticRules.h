/*
* ��� ������� ������� ����������� ������ �����
*/
#pragma once
#include "GrammaticSymbols.h"
#include "TerminalSymbols.h"
#include "Visitor.h"
#include <vector>

// ��� ���������
class CProgram : public IProgram
{
public:
	CProgram( IMainClassDeclaration *_mainClassDeclaration, IClassDeclaration *_classDeclarationList ) :
	mainClassDeclaration(_mainClassDeclaration), classDeclarationsList(_classDeclarationList) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };
	IMainClassDeclaration* GetMainClassDeclaration() const { return mainClassDeclaration; };
	IClassDeclaration* GetClassDeclarationsList() const { return classDeclarationsList; };
private:
	IMainClassDeclaration *mainClassDeclaration; // ���������� �������� ������
	IClassDeclaration *classDeclarationsList; // ������ ���������� �������
};

// ����������� �������� ������
class CMainClassDeclaration : public IMainClassDeclaration
{
public:
	CMainClassDeclaration(CIdentifier *_className, CIdentifier *_argumentName, IStatement *_statement):
		className(_className), argumentName(_argumentName), statement(_statement) { };
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetClassName() const { return className->getString(); };
	std::string GetArgumentName() const { return argumentName->getString(); };
	IStatement* GetClassStatements() const { return statement; };

private:
	CIdentifier *className; // �������� ������
	CIdentifier *argumentName; // ��� ���������
	IStatement *statement; // ���� ������ 
};

// ����������� ������
class CClassDeclaration : public IClassDeclaration
{
public:
	CClassDeclaration( CIdentifier *_className, IVariableDeclaration *_fieldsList, IMethodDeclaration *_methodsList ) :
		className( _className ), fieldsList( _fieldsList ), methodsList( _methodsList ) { };
	std::string getClassName() const;
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetClassName() const { return className->getString(); };
	IVariableDeclaration* GetFieldsList() const { return fieldsList; };
	IMethodDeclaration* GetMethodsList() const { return methodsList; };

private:
	CIdentifier *className; // �������� ������
	IVariableDeclaration *fieldsList; // ������ ����� ������
	IMethodDeclaration *methodsList; // ������������ ������� 
};

// ������ ����������� �������
class CClassDeclarationList : public IClassDeclaration
{
public:
	CClassDeclarationList( IClassDeclaration *_classDeclaration, IClassDeclaration *_nextClassDeclaration ) :
		classDeclaration( _classDeclaration ), nextClassDeclaration( _nextClassDeclaration ) { };
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IClassDeclaration* GetClassDeclaration() const { return classDeclaration; };
	IClassDeclaration *GetNextClassDeclaration() const { return nextClassDeclaration; };

private:
	IClassDeclaration *classDeclaration; // ��������� ������ �������� ������
	IClassDeclaration *nextClassDeclaration; // ������ �� ��������� �������
};

// ����������� ������, ������� ����������� �� �������������
class CClassExtendsDeclaration : public IClassDeclaration
{
public:
	CClassExtendsDeclaration( CIdentifier *_className, CIdentifier *_superClassName, IVariableDeclaration *_fieldsList, IMethodDeclaration *_methodsList ) :
		className( _className ), superClassName( _superClassName ), fieldsList( _fieldsList ), methodsList( _methodsList ) { };
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetClassName() const { return className->getString(); };
	std::string GetSuperClassName() const { return superClassName->getString(); };
	IVariableDeclaration* GetFieldsList() const { return fieldsList; };
	IMethodDeclaration* GetMethodsList() const { return methodsList; };
private:
	CIdentifier *className; // �������� ������
	CIdentifier *superClassName; // �������� ������, �� �������� ���������� ������������
	IVariableDeclaration *fieldsList; // ������ ����� ������
	IMethodDeclaration *methodsList; // ������������ ������� 
};

// ����������� ����������
class CVariableDeclaration : public IVariableDeclaration
{
public:
	CVariableDeclaration( IType *_type, CIdentifier *_variableName) :
		type( _type ), variableName( _variableName ) { };
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetName() const { return variableName->getString(); };
	IType* GetType() const { return type;  };
private:
	IType *type; // ��� ������
	CIdentifier *variableName; // ��� ����������	
};

// ������ ����������� ����������
class CVariableDeclarationList : public IVariableDeclaration
{
public:
	CVariableDeclarationList(IVariableDeclaration *_variableDeclaration, CVariableDeclarationList *_nextVariableDeclaration):
	variableDeclaration(_variableDeclaration), nextVariableDeclaration(_nextVariableDeclaration) { };
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	CVariableDeclarationList* GetNextVariableDeclaration() const { return nextVariableDeclaration; };
	IVariableDeclaration* GetVariableDeclaration() const { return variableDeclaration; };

private:
	IVariableDeclaration *variableDeclaration; // ��������� ������
	CVariableDeclarationList *nextVariableDeclaration; // ������ �� ��������� �������
};

// ����������� ������
class CMethodDeclaration : public IMethodDeclaration
{
public:
	CMethodDeclaration( IType *_type, CIdentifier *_methodName, IFormalList *_formalList, IVariableDeclaration *_localVariablesList, IStatement *_statementList, IExpression *_returnExpression) :
		type( _type ), methodName( _methodName ), formalList( _formalList ), localVariablesList( _localVariablesList ), statementList( _statementList ), returnExpression( _returnExpression ) { }
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetMethodName() const {return methodName->getString(); };
	IType* GetType() const { return type; };
	IFormalList* GetFormalList() const { return formalList; };
	IStatement* GetStatements() const { return statementList; };

	IVariableDeclaration* GetLocalVariablesList() const { return localVariablesList; };

	IExpression* GetReturnExpression() const { return returnExpression; };

private:
	IType *type; // ��� ������, ������� ���������� ���� ���
	CIdentifier *methodName; // ��� ������
	IFormalList *formalList; // ������������ ����������
	IVariableDeclaration *localVariablesList; // ��������� ���������� ������
	IStatement *statementList; // ��������������� ��� ������
	IExpression *returnExpression; // ��������, ������� ����� ������������ �������
};

// ������ ����������� �������
class CMethodDeclarationList : public IMethodDeclaration
{
public:
	CMethodDeclarationList(IMethodDeclaration *_methodDeclaration, IMethodDeclaration *_nextMethodDeclaration):
	methodDeclaration(_methodDeclaration), nextMethodDeclaration(_nextMethodDeclaration) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IMethodDeclaration* GetMethodDeclaration() const { return methodDeclaration; };
	IMethodDeclaration* GetNextMethodDeclaration() const { return nextMethodDeclaration; };

private:
	IMethodDeclaration *methodDeclaration; // ����������� ������ (��������� ������)
	IMethodDeclaration *nextMethodDeclaration; // ������ �� ��������� ����������� ������
};

// ������ ���������� ������
class CFormalList : public IFormalList
{
public:
	CFormalList( IType *_type, CIdentifier *_parameterName ) :
		type( _type ), parameterName( _parameterName ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetParameterName() const { return parameterName->getString(); };
	IType* GetType() const { return type; };

private:
	IType *type; // ��� ����������
	CIdentifier *parameterName; // ��� ����������
	// std::vector<IFormalRest> *formalRest; // ��������� �� ������� ������
	// IFormalList *nextInList; // ��������� �������� � ������
};

class CFormalRestList : public IFormalList
{
public:
	CFormalRestList(IFormalList *_formalRest, IFormalList *_nextFormalRest):
	formalRest(_formalRest), nextFormalRest(_nextFormalRest) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IFormalList* GetFormalRest() const { return formalRest; };
	IFormalList* GetNextFormalRest() const { return nextFormalRest; };

private:
	IFormalList *formalRest; // ��������
	IFormalList *nextFormalRest; // ��������� ��������
};

/*
// ������ ������ ���������� ������
class CEmptyFormalList : public IFormalList
{
public:
	CEmptyFormalList() { };
};
*/

/*
// "���������" ������� ������������ ���������� ������
class CFormalRest : public IFormalRest
{
public:
	CFormalRest( IType *_type, CIdentifier *_parameterName ) :
		type( _type ), parameterName( _parameterName ) { };
private:
	IType *type; // ��� ����������
	CIdentifier *parameterName; // ��� ����������
};
*/

// ������������ ���������� ����� ������
enum TBuiltInType {
	BT_INTEGER,
	BT_INTEGER_ARRAY,
	BT_BOOLEAN
};

// �����, �������� ���������� ��� ������
class CBuiltInType : public IType {
public:
	CBuiltInType( TBuiltInType _type ) : type( _type ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	TBuiltInType GetType() const { return type; };
private:
	TBuiltInType type;
};

// �����, �������� ���������������� ��� ������
class CUserType : public IType {
public:
	CUserType( CIdentifier *_typeName ) : typeName( _typeName ) { };
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetTypeName() const { return typeName->getString(); }
private:
	CIdentifier *typeName; // �������� ������
};

/* ��������� */
// ���������� ������ ����������
class CStatementList : public IStatement
{
public:
	CStatementList( IStatement *_statement, IStatement *_nextStatement ) :
		statement( _statement ), nextStatement( _nextStatement ) { };
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IStatement* GetStatement() const { return statement; };
	IStatement* GetNextStatement() const { return nextStatement; };

private:
	IStatement *statement; // ������� ������ ��������
	IStatement *nextStatement; // ��������� ������� ������
};

// ������������ ���������� � ����� ����
class CStatementBlock : public IStatement
{
public:
	CStatementBlock( IStatement *_statementsList ) : statementsList( _statementsList ) { };
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IStatement* GetStatementList() const { return statementsList; };

private:
	IStatement *statementsList; // ��������� � ������ �����
};

// �������� ��������
class CIfStatement : public IStatement
{
public:
	CIfStatement( IExpression *_condition, IStatement *_trueStatement, IStatement *_falseStatement ) :
		condition( _condition ), trueStatement( _trueStatement ), falseStatement( _falseStatement ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IStatement* GetTrueStatement() const { return trueStatement; };
	IStatement* GetFalseStatement() const { return falseStatement; };

	IExpression* GetCondition() const { return condition; };

private:
	IExpression *condition; // �������, ������� ������ �����������
	IStatement *trueStatement; // ��������, ����������� ��� �������� �������
	IStatement *falseStatement; // ��������, ����������� ��� ������ �������
};

// �������� while
class CWhileStatement : public IStatement
{
public:
	CWhileStatement( IExpression *_condition, IStatement *_trueStatement ) :
		condition( _condition ), trueStatement( _trueStatement ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IStatement* GetStatement() const { return trueStatement; };
	IExpression* GetCondition() const { return condition; };

private:
	IExpression *condition; // �������, ������� ������ �����������
	IStatement *trueStatement; // ��������, ����������� ��� �������� �������
};

// �������� ������
class CPrintStatement : public IStatement
{
public:
	CPrintStatement( IExpression *_expressionToPrint ) :
		expressionToPrint( _expressionToPrint ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IExpression* GetExpression() const { return expressionToPrint; };
private:
	IExpression *expressionToPrint; // ���������, �������� �������� ����� ����������
};

// �������� ������������
class CAssignmentStatement : public IStatement
{
public:
	CAssignmentStatement( CIdentifier *_variableName, IExpression *_rightValue ) :
		variableName( _variableName ), rightValue( _rightValue ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetVariableName() const { return variableName->getString(); };
	IExpression* GetRightValue() const { return rightValue; };
private:
	CIdentifier *variableName; // ��� ����������, ������� ����� ������������� ��������
	IExpression *rightValue; // ������������� ��������
};

// �������� ������������ �������� �������
class CArrayElementAssignmentStatement : public IStatement
{
public:
	CArrayElementAssignmentStatement( CIdentifier *_arrayName, IExpression *_indexExpression, IExpression *_rightValue ):
		arrayName(_arrayName), indexExpression(_indexExpression), rightValue(_rightValue) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetArrayName() const { return arrayName->getString(); };
	IExpression* GetIndexExpression() const { return indexExpression; };
	IExpression* GetRightValue() const { return rightValue; };

private:
	CIdentifier *arrayName; // ��� �������
	IExpression *indexExpression; // ������ �������
	IExpression *rightValue; // ������������� ��������
};

/* ��������� */
// �������� ��������
enum TBinaryOperator {
	BO_PLUS,		// �����
	BO_MINUS,		// ��������
	BO_MULTIPLY,	// ������������
	BO_LESS,		// ������
	BO_LOGICAL_AND,	// ���������� "�"
};

class CBinaryOperatorExpression : public IExpression
{
public:
	CBinaryOperatorExpression( IExpression *_leftValue, IExpression *_rightValue, TBinaryOperator _binaryOperator ) : 
		leftValue(_leftValue), rightValue(_rightValue), binaryOperator(_binaryOperator) { }
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IExpression* GetLeftValue() const { return leftValue; };
	IExpression* GetRightValue() const { return rightValue; };
	TBinaryOperator GetOperator() const { return binaryOperator;  };

private:
	IExpression *leftValue; // �������� �����
	IExpression *rightValue; // �������� ������
	TBinaryOperator binaryOperator;
};

// �������� ������� � �������� �������
class CIndexAccessExpression : public IExpression
{
public:
	CIndexAccessExpression(IExpression *_arrayExpression, IExpression *_index) :
	arrayExpression(_arrayExpression), index(_index) { };
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IExpression* GetArrayExpression() const { return arrayExpression; };
	IExpression* GetIndex() const { return index; };
private:
	IExpression *arrayExpression; // ������, � �������� ����� ����������
	IExpression *index; // ������ ��������
};

// ��������� ����� �������
class CLengthExpression : public IExpression
{
public:
	CLengthExpression( IExpression *_arrayExpression ) : arrayExpression( _arrayExpression ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IExpression* GetArray() const { return arrayExpression; };
private:
	IExpression *arrayExpression; // ������, � �������� ����� ����������
};

// ����� ������ �������
class CMethodCallExpression : public IExpression
{
public:
	CMethodCallExpression(IExpression *_variableExpression, CIdentifier *_methodName, IExpression *_expressionList) :
	variableExpression(_variableExpression), methodName(_methodName), expressionList(_expressionList) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IExpression* GetObject() const { return variableExpression; };
	IExpression* GetParams() const { return expressionList; };
	std::string GetMethodName() const { return methodName->getString(); }

private:
	IExpression *variableExpression; // ���������� ��� ������, � ������� �������� �����
	CIdentifier *methodName; // ��� ������, ������� �� ��������
	IExpression *expressionList; // ������ ����������, ������� �� ������� ������
};

enum TValueType {
	VT_INTEGER,
	VT_BOOLEAN
};
// ������������� � ������ ��������
class CIntegerOrBooleanExpression : public IExpression
{
public:
	CIntegerOrBooleanExpression( int _value, TValueType _valueType ) :
		value( _value ), valueType( _valueType ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	int GetValue() const { return value; };
	TValueType GetValueType() const { return valueType; };

private:
	int value; // �������� ����������
	TValueType valueType; // ��� ���������� 
};

// ��������� �������� ����������
class CIdentifierExpression : public IExpression
{
public:
	CIdentifierExpression( CIdentifier *_variableName ) : variableName( _variableName ) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetVariableName() const { return variableName->getString(); };
private:
	CIdentifier *variableName; // ��� ����������, �������� ������� �� ����� ��������
};

// ��������� ������ �� ������ �� ��������� ����� this
class CThisExpression : public IExpression
{
public:
	CThisExpression() {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };
};

// �������� ������ ������� �� int
class CNewIntegerArrayExpression : public IExpression
{
public:
	CNewIntegerArrayExpression( IExpression *_arraySize ) : arraySize(_arraySize) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IExpression* GetArraySize() const { return arraySize; };
private:
	IExpression *arraySize; // ������ �������
};

// �������� ������ ������� ������������ ������
class CNewObjectExpression : public IExpression
{
public:
	CNewObjectExpression( CIdentifier *_className ) : className(_className) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	std::string GetClass() const { return className->getString(); };
private:
	CIdentifier *className; // �����, ������ �������� �� ����� �������
};

// �������� ���������
class CNegationExpression : public IExpression
{
public:
	CNegationExpression( IExpression *_argument ) : argument(_argument) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IExpression* GetArgument() const { return argument; };
private:
	IExpression *argument; // ��������, ��������� �������� �� ����� ��������
};

// ������
class CParenthesesExpression : public IExpression
{
public:
	CParenthesesExpression( IExpression *_expression ) : expression(_expression) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IExpression* GetExpression() const { return expression; };
private:
	IExpression *expression; // ��������� � �������
};

// ������ ���������
class CExpressionList : public IExpression
{
public:
	CExpressionList(IExpression *_expression, IExpression *_nextExpression):
	expression(_expression), nextExpression(_nextExpression) {};
	void Accept( IVisitor *visitor ) const { visitor->Visit( this ); };

	IExpression* GetExpression() const { return expression; };
	IExpression* GetNextExpression() const { return nextExpression; };

private:
	IExpression *expression; // ������� �������� �������� ������ - ���������
	IExpression *nextExpression; // ��������� ������� ������
};
