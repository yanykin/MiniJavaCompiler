/*
* ��� ������� ������� ����������� ������ �����
*/
#include "GrammaticSymbols.h"
#include "TerminalSymbols.h"
#include <vector>

// ����������� �������� ������
class CMainClassDeclaration : public IMainClassDeclaration
{
public:
	CMainClassDeclaration(CIdentifier *_className, CIdentifier *_argumentName, IStatement *_statement):
		className(_className), argumentName(_argumentName), statement(_statement) { };

private:
	CIdentifier *className; // �������� ������
	CIdentifier *argumentName; // ��� ���������
	IStatement *statement; // ���� ������ 
};

// ����������� ������
class CClassDeclaration : public IClassDeclaration
{
public:
	CClassDeclaration( CIdentifier *_className, std::vector<IVariableDeclaration> *_fields, std::vector<IMethonDeclaration> *_methods ) :
		className( _className ), fields( _fields ), methods( _methods ) { };
private:
	CIdentifier *className; // �������� ������
	std::vector<IVariableDeclaration> *fields; // ������������ �����
	std::vector<IMethonDeclaration> *methods; // ������������ ������� 
};

// ����������� ������, ������� ����������� �� �������������
class CClassExtendsDeclaration : public IClassDeclaration
{
public:
	CClassExtendsDeclaration( CIdentifier *_className, CIdentifier *_superClassName, std::vector<IVariableDeclaration> *_fields, std::vector<IMethonDeclaration> *_methods ) :
		className( _className ), superClassName( _superClassName ), fields( _fields ), methods( _methods ) { };
private:
	CIdentifier *className; // �������� ������
	CIdentifier *superClassName; // �������� ������, �� �������� ���������� ������������
	std::vector<IVariableDeclaration> *fields; // ������������ �����
	std::vector<IMethonDeclaration> *methods; // ������������ ������� 
};

// ����������� ����������
class CVariableDeclaraion : public IVariableDeclaration
{
public:
	CVariableDeclaraion( IType *_type, CIdentifier *_variableName ) :
		type( _type ), variableName( _variableName ) { };
private:
	IType *type; // ��� ������
	CIdentifier *variableName; // ��� ����������
};

// ����������� ������
class CMethodDeclaration : public IMethonDeclaration
{
public:
	CMethodDeclaration( IType *_type, CIdentifier *_methodName, IFormalList *_formalList, std::vector<IVariableDeclaration> *_localVariables, std::vector<IStatement> *_statements, IExpression *_returnExpression ) :
		type( _type ), methodName( _methodName ), formalList( _formalList ), localVariables( _localVariables ), statements( _statements ), returnExpression( _returnExpression ) { }
private:
	IType *type; // ��� ������, ������� ���������� ���� ���
	CIdentifier *methodName; // ��� ������
	IFormalList *formalList; // ������������ ����������
	std::vector<IVariableDeclaration> *localVariables; // ��������� ���������� ������
	std::vector<IStatement> *statements; // ��������������� ��� ������
	IExpression *returnExpression; // ��������, ������� ����� ������������ �������
};

// ������ ���������� ������
class CFormalList : public IFormalList
{
public:
	CFormalList( IType *_type, CIdentifier *_parameterName, std::vector<IFormalRest> *_formalRest ) :
		type(_type), parameterName(_parameterName), formalRest(_formalRest) {}
private:
	IType *type; // ��� ����������
	CIdentifier *parameterName; // ��� ����������
	std::vector<IFormalRest> *formalRest; // ��������� �� ������� ������
};

// ������ ������ ���������� ������
class CEmptyFormalList : public IFormalList
{
public:
	CEmptyFormalList() { };
};

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

// ������������ ���������� ����� ������
enum TBuiltInType {
	BT_INTEGER,
	BT_INTEGER_ARRAY,
	BT_BOOLEAN
};

// �����, �������� ���������� ��� ������
class CBulitInType : public IType {
public:
	CBulitInType( TBuiltInType _type ) : type( _type ) {};
private:
	TBuiltInType type;
};

// �����, �������� ���������������� ��� ������
class CUserType : public IType {
public:
	CUserType( CIdentifier *_typeName ) : typeName( _typeName ) { };
private:
	CIdentifier *typeName; // �������� ������
};

// ������������ ���������� � ����� ����
class CStatementBlock : public IStatement
{
public:
	CStatementBlock( std::vector<IStatement> *_statements ) : statements( _statements ) { };
private:
	std::vector<IStatement> *statements; // ��������� � ������ �����
};

// �������� ��������
class CIfStatement : public IStatement
{
public:
	CIfStatement( IExpression *_condition, IStatement *_trueStatement, IStatement *_falseStatement ) :
		condition( _condition ), trueStatement( _trueStatement ), falseStatement( _falseStatement ) { };
private:
	IExpression *condition; // �������, ������� ������ �����������
	IStatement *trueStatement; // ��������, ����������� ��� �������� �������
	IStatement *falseStatement; // ��������, ����������� ��� ������ �������
};

// �������� while
class CWhileStatement : public IStatement
{
	CWhileStatement( IExpression *_condition, IStatement *_trueStatement ) :
		condition( _condition ), trueStatement( _trueStatement ){ };
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
private:
	IExpression *expressionToPrint; // ���������, �������� �������� ����� ����������
};