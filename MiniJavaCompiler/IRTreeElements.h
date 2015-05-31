/*
������ ������������ ���� ������������� ������� ����� ������ �������������� �������������
*/
#pragma once

namespace IRTree {

	// ��������������� ������
	class CExpList;
	class CStmList;

	// ��������� IRTree::IExp
	class CONST;
	class NAME;
	class TEMP;
	class BINOP;
	class MEM;
	class CALL;
	class ESEQ;

	// ��������� IRTree::IStm
	class MOVE;
	class EXP;
	class JUMP;
	class CJUMP;
	class SEQ;
	class LABEL;
}
