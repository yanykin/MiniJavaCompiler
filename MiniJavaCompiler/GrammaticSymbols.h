/*
* ��������� �������������� ������� ����������, ������� ������������� ��������� (����������� �����)
*/
#pragma once
#include "Visitor.h"
// class IVisitor;

// ��������� - ��������� ������
class IProgram
{
public:
	virtual ~IProgram() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
};

// ������� ����� ���������
class IMainClassDeclaration {
public:
	virtual ~IMainClassDeclaration() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
};

// ���������� ������
class IClassDeclaration
{
public:
	virtual ~IClassDeclaration() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
};

// ���������� ���������� ��� ����
class IVariableDeclaration
{
public:
	virtual ~IVariableDeclaration() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
};

// ���������� ������ ������
class IMethodDeclaration
{
public:
	virtual ~IMethodDeclaration() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
};

// ������ ���������� ������
class IFormalList
{
public:
	virtual ~IFormalList() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
};

// ��������� ������� ������ ���������� ������
class IFormalRest
{
public:
	virtual ~IFormalRest() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
};

// ��� ������
class IType
{
public:
	virtual ~IType() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
};

// ��������
class IStatement
{
public:
	virtual ~IStatement() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
};

// ���������
class IExpression
{
public:
	virtual ~IExpression() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
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