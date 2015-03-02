/*
Просто перечисление всех реализованных классов узлов дерева промежуточного представления
*/
#pragma once

namespace IRTree {

	// Вспомогательные классы
	class CExpList;
	class CStmList;

	// Подклассы IRTree::IExp
	class CONST;
	class NAME;
	class TEMP;
	class BINOP;
	class MEM;
	class CALL;
	class ESEQ;

	// Подклассы IRTree::IStm
	class MOVE;
	class EXP;
	class JUMP;
	class CJUMP;
	class SEQ;
	class LABEL;
}