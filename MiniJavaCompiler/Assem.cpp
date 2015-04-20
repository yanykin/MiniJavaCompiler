#include "Assem.h"

using namespace Assem;

void Codegen::emit(IInstr * inst) {
	if (last)
	{
		last = last->tail = new InstrList(inst, NULL);
	}
	else last = ilist = new InstrList(inst, NULL);
}

InstrList * Codegen::codegen(IRTree::IStm * s) {
	InstrList * l;
	munchStm(s);
	l = ilist;
	ilist = last = NULL;
	return l;
}

void Codegen::munchStm(IRTree::SEQ * stm)
{
	munchStm(stm->GetLeft);
	munchStm(stm->GetRight);
}

void Codegen::munchStm(IRTree::MOVE * stm)
{
	MEM * memStmDst = reinterpret_cast<MEM *> (stm->GetDst);
	MEM * memStmSrc = reinterpret_cast<MEM *> (stm->GetSrc);
	
	if (memStmDst)
	{
		if (memStmSrc)
		{
			emit(new OPER(std::string("MOVE M[Сs0] <- M[Сs1]\n"),
				NULL, new CTempList(munchExp(memStmDst->GetExp), new CTempList(munchExp(memStmSrc->GetExp), NULL))));
			return;
		}
		emit(new OPER(std::string("STORE M[Сs0] <- Сs1\n"),
			NULL, new CTempList(munchExp(memStmDst->GetExp), new CTempList(munchExp(stm->GetSrc), NULL))));
		return;
	}
}

//не доделана!!
CTemp * Codegen::munchExp(IRTree::CONST * exp)
{
	CTemp * r = new CTemp();
	std::string intstrString = "ADDI Сd0 <- r0+";
	intstrString += exp->GetValue;
	intstrString += "\n";
	
	return r;
}

CTemp * Codegen::munchExp(IRTree::MEM * exp)
{
	IExp * curExp = exp->GetExp;
	CTemp * r = new CTemp();

	BINOP * binopExp = reinterpret_cast<BINOP *> (curExp);
	if (binopExp)
	{
		emit(new OPER(std::string("LOAD Сd0 <- M[Сs0+0]\n"),
			new CTempList(r, NULL), new CTempList(munchExp(binopExp), NULL)));
		return r;
	}

	CONST * constExp = reinterpret_cast<CONST *> (curExp);
	if (constExp)
	{
		std::string intstrString = "ADDI Сd0 <- r0+";
		intstrString += constExp->GetValue;
		intstrString += "\n";
		emit(new OPER(intstrString, new CTempList(r, NULL), NULL));
		return r;
	}

	return r;
}

CTemp * Codegen::munchExp(IRTree::BINOP * exp)
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