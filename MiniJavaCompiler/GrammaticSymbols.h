/*
* ��������� �������������� ������� ����������, ������� ������������� ��������� (����������� �����)
*/

// ������� ����� ���������
class IMainClassDeclaration {
public:
	virtual ~IMainClassDeclaration() { };
};

// ���������� ������
class IClassDeclaration
{
public:
	virtual ~IClassDeclaration() { };
};

// ���������� ���������� ��� ����
class IVariableDeclaration
{
public:
	virtual ~IVariableDeclaration() { };
	
};

// ���������� ������ ������
class IMethonDeclaration
{
public:
	virtual ~IMethonDeclaration() { };
};

// ������ ���������� ������
class IFormalList
{
public:
	virtual ~IFormalList() { };
};

// ��������� ������� ������ ���������� ������
class IFormalRest
{
public:
	virtual ~IFormalRest() { };
};

// ��� ������
class IType
{
public:
	virtual ~IType() { };
};

// ��������
class IStatement
{
public:
	virtual ~IStatement() { };
};

// ���������
class IExpression
{
public:
	virtual ~IExpression() { };
};

// ������ ���������
class IExpressionList
{
public:
	virtual ~IExpressionList() { };
};

// ������� ������ ���������
class IExpressionRest
{
public:
	virtual ~IExpressionRest() { };
};