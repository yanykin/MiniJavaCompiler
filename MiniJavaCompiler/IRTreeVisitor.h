/*
Интерфейс для реализации паттерна "Посетитель" для дерева промежуточного представления
*/

#pragma once
#include "IRTreeElements.h"

using namespace IRTree;

class IIRTreeVisitor {
public:
	// Вспомогательные классы
	virtual void Visit( const CExpList* node ) = 0;
	virtual void Visit( const CStmList* node ) = 0;

	// Подклассы IRTree::IExp
	virtual void Visit( const CONST* node ) = 0;
	virtual void Visit( const NAME* node ) = 0;
	virtual void Visit( const TEMP* node ) = 0;
	virtual void Visit( const BINOP* node ) = 0;
	virtual void Visit( const MEM* node ) = 0;
	virtual void Visit( const CALL* node ) = 0;
	virtual void Visit( const ESEQ* node ) = 0;

	// Подклассы IRTree::IStm
	virtual void Visit( const MOVE* node ) = 0;
	virtual void Visit( const EXP* node ) = 0;
	virtual void Visit( const JUMP* node ) = 0;
	virtual void Visit( const CJUMP* node ) = 0;
	virtual void Visit( const SEQ* node ) = 0;
	virtual void Visit( const LABEL* node ) = 0;
};