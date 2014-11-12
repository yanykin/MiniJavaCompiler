/*
* ��������� �������������� ������� ����������, ������� ������������� ��������� (����������� �����)
*/
#pragma once
// #include "Visitor.h"
class IVisitor;

// ��������� - ��������� ������
class IProgram
{
public:
	virtual ~IProgram() { };
	virtual int Accept( IVisitor *visitor ) const = 0;
};

// ������� ����� ���������
class IMainClassDeclaration {
public:
	virtual ~IMainClassDeclaration() { };
	virtual int Accept( IVisitor *visitor ) const = 0;
};

// ���������� ������
class IClassDeclaration
{
public:
	virtual ~IClassDeclaration() { };
	virtual int Accept( IVisitor *visitor ) const = 0;
};

// ���������� ���������� ��� ����
class IVariableDeclaration
{
public:
	virtual ~IVariableDeclaration() { };
};

// ���������� ������ ������
class IMethodDeclaration
{
public:
	virtual ~IMethodDeclaration() { };
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

/*
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
*/