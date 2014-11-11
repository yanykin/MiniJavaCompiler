/*
* Описывает нетерминальные символы грамматики, каждому соответствует интерфейс (абстрактный класс)
*/

// Главный класс программы
class IMainClassDeclaration {
public:
	virtual ~IMainClassDeclaration() { };
};

// Объявление класса
class IClassDeclaration
{
public:
	virtual ~IClassDeclaration() { };
};

// Объявление переменной или поля
class IVariableDeclaration
{
public:
	virtual ~IVariableDeclaration() { };
	
};

// Объявление метода класса
class IMethonDeclaration
{
public:
	virtual ~IMethonDeclaration() { };
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