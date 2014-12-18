/*
* Описывает нетерминальные символы грамматики, каждому соответствует интерфейс (абстрактный класс)
*/
#pragma once
#include "Visitor.h"
// class IVisitor;

// Программа - начальный символ
class IProgram
{
public:
	virtual ~IProgram() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
};

// Главный класс программы
class IMainClassDeclaration {
public:
	virtual ~IMainClassDeclaration() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
};

// Объявление класса
class IClassDeclaration
{
public:
	virtual ~IClassDeclaration() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
};

// Объявление переменной или поля
class IVariableDeclaration
{
public:
	virtual ~IVariableDeclaration() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
};

// Объявление метода класса
class IMethodDeclaration
{
public:
	virtual ~IMethodDeclaration() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
};

// Список параметров метода
class IFormalList
{
public:
	virtual ~IFormalList() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
};

// Последний элемент списка параметров метода
class IFormalRest
{
public:
	virtual ~IFormalRest() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
};

// Тип данных
class IType
{
public:
	virtual ~IType() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
};

// Операция
class IStatement
{
public:
	virtual ~IStatement() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
};

// Выражение
class IExpression
{
public:
	virtual ~IExpression() { };
	virtual void Accept( IVisitor *visitor ) const = 0;
};

/*
// Список выражений
class IExpressionList
{
public:
	virtual ~IExpressionList() { };
};

// Остаток списка выражений
class IExpressionRest
{
public:
	virtual ~IExpressionRest() { };
};
*/