/*
Интерфейс для реализации паттерна "Посетитель" для дерева промежуточного представления
*/

#pragma once
#include "IRTreeElements.h"

class IIRTreeVisitor {
public:
	// Вспомогательные классы
	virtual void Visit( const IRTree::CExpList* node ) = 0;
	virtual void Visit( const IRTree::CStmList* node ) = 0;

	// Подклассы IRTree::IExp
	virtual void Visit( const IRTree::CONST* node ) = 0;
	virtual void Visit( const IRTree::NAME* node ) = 0;
	virtual void Visit( const IRTree::TEMP* node ) = 0;
	virtual void Visit( const IRTree::BINOP* node ) = 0;
	virtual void Visit( const IRTree::MEM* node ) = 0;
	virtual void Visit( const IRTree::CALL* node ) = 0;
	virtual void Visit( const IRTree::ESEQ* node ) = 0;

	// Подклассы IRTree::IStm
	virtual void Visit( const IRTree::MOVE* node ) = 0;
	virtual void Visit( const IRTree::EXP* node ) = 0;
	virtual void Visit( const IRTree::JUMP* node ) = 0;
	virtual void Visit( const IRTree::CJUMP* node ) = 0;
	virtual void Visit( const IRTree::SEQ* node ) = 0;
	virtual void Visit( const IRTree::LABEL* node ) = 0;
};