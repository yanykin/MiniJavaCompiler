/*
* Интерфейс шаблона проектирования "Посетитель"
*/
#pragma once
#include "GrammaticRules.h"
#include <iostream>

class IVisitor {
public:
	virtual int Visit( const CProgram* node ) = 0;
	virtual int Visit( const CMainClassDeclaration* node ) = 0;
	virtual int Visit( const CClassDeclaration* node ) = 0;
	virtual int Visit( const CClassExtendsDeclaration* node ) = 0;
	virtual int Visit( const CClassDeclarationList* node ) = 0;
};