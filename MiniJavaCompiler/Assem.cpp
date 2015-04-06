#include "Assem.h"

using namespace Assem;

void Codegen::emit(IInstr * inst) {
	if (last)
	{
		last = last->tail = new InstrList(inst, NULL);
	}
	else last = ilist = new InstrList(inst, NULL);
}

InstrList * Codegen::codegen(IStm * s) {
	InstrList * l;
	munchStm(s);
	l = ilist;
	ilist = last = NULL;
	return l;
}

CTemp * Codegen::munchExp(CONST * exp)
{
	CTemp * r = new CTemp();
	std::string intstrString = "ADDI ‘d0 <- r0+";
	intstrString += exp->GetValue;
	intstrString += "\n";

	return r;
}

CTemp * Codegen::munchExp(MEM * exp)
{
	IExp * curExp = exp->GetExp;
	CTemp * r = new CTemp();

	BINOP * binopExp = reinterpret_cast<BINOP *> (curExp);
	if (binopExp)
	{
		emit(new OPER(std::string("LOAD ‘d0 <- M[‘s0+0]\n"),
			new CTempList(r, NULL), new CTempList(munchExp(binopExp), NULL)));
		return r;
	}

	CONST * constExp = reinterpret_cast<CONST *> (curExp);
	if (constExp)
	{
		std::string intstrString = "ADDI ‘d0 <- r0+";
		intstrString += constExp->GetValue;
		intstrString += "\n";
		emit(new OPER(intstrString, new CTempList(r, NULL), NULL));
		return r;
	}

	return r;
}

CTemp * Codegen::munchExp(BINOP * exp)
{
	TBinop type = exp->GetBinop;
	switch (type)
	{
	case IRTree::BO_PLUS:
		CTemp * r = new CTemp();
		emit(new OPER(std::string("add `d0 <- `s0 + `s1"), new CTempList(r, NULL), new CTempList(munchExp(exp), NULL)));
		break;
	case IRTree::BO_MINUS:
		CTemp * r = new CTemp();
		emit(new OPER(std::string("sub `d0 <- `s0 + `s1"), new CTempList(r, NULL), new CTempList(munchExp(exp), NULL)));
		break;
	case IRTree::BO_MUL:
		CTemp * r = new CTemp();
		emit(new OPER(std::string("mul `d0 <- `s0 + `s1"), new CTempList(r, NULL), new CTempList(munchExp(exp), NULL)));
		break;
	case IRTree::BO_DIV:
		CTemp * r = new CTemp();
		emit(new OPER(std::string("div `d0 <- `s0 + `s1"), new CTempList(r, NULL), new CTempList(munchExp(exp), NULL)));
		break;
	case IRTree::BO_AND:
		CTemp * r = new CTemp();
		emit(new OPER(std::string("and `d0 <- `s0 + `s1"), new CTempList(r, NULL), new CTempList(munchExp(exp), NULL)));
		break;
	case IRTree::BO_OR:
		CTemp * r = new CTemp();
		emit(new OPER(std::string("or `d0 <- `s0 + `s1"), new CTempList(r, NULL), new CTempList(munchExp(exp), NULL)));
		break;
	case IRTree::BO_LSHIFT:
		break;
	case IRTree::BO_RSHIFT:
		break;
	case IRTree::BO_ARSHIFT:
		break;
	case IRTree::BO_XOR:
		CTemp * r = new CTemp();
		emit(new OPER(std::string("or `d0 <- `s0 + `s1"), new CTempList(r, NULL), new CTempList(munchExp(exp), NULL)));
		break;
	default:
		break;
	}
}