/*
* Описывает нетерминальные символы грамматики, каждому соответствует интерфейс (абстрактный класс)
*/
#pragma once
// #include "Visitor.h"
class IVisitor;

// Программа - начальный символ
class IProgram
{
public:
	virtual ~IProgram() { };
	virtual int Accept( IVisitor *visitor ) const = 0;
};

// Главный класс программы
class IMainClassDeclaration {
public:
	virtual ~IMainClassDeclaration() { };
	virtual int Accept( IVisitor *visitor ) const = 0;
};

// Объявление класса
class IClassDeclaration
{
public:
	virtual ~IClassDeclaration() { };
	virtual int Accept( IVisitor *visitor ) const = 0;
};

// Объявление переменной или поля
class IVariableDeclaration
{
public:
	virtual ~IVariableDeclaration() { };
};

// Объявление метода класса
class IMethodDeclaration
{
public:
	virtual ~IMethodDeclaration() { };
};

// Список параметров метода
class IFormalList
{
public:
	virtual ~IFormalList() { };
};

// Последний элемент списка параметров метода
class IFormalRest
{
public:
	virtual ~IFormalRest() { };
};

// Тип данных
class IType
{
public:
	virtual ~IType() { };
};

// Операция
class IStatement
{
public:
	virtual ~IStatement() { };
};

// Выражение
class IExpression
{
public:
	virtual ~IExpression() { };
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