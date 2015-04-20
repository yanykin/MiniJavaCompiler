#pragma once
#include "IRTree.h"
#include "Temp.h"
#include <string>

using namespace IRTree;
using namespace Temp;

//вспомогательный класс
class CTempList
{
public:
	CTemp * head;
	CTempList * tail;
	CTempList(CTemp * h, CTempList * t) : head(h), tail(t) {}
};

//вспомогательный класс
class Targets {
public:
	CLabelList labels;
	Targets(CLabelList l) : labels(l) {}
};

namespace Assem
{
	class IInstr
	{
	public:
		std::string assem;
		CTempList * use();
		CTempList * def();
		Targets * jumps();
		std::string format();
	};

	class InstrList
	{
	public:
		IInstr * head;
		InstrList * tail;
		InstrList(IInstr * h, InstrList * t) : head(h), tail(t) {}
	};

	class LABEL : public IInstr {
	public:
		CLabel * label;

		LABEL(std::string & a, CLabel * l) : label(l) { assem = a; }

		CTempList * use() { return NULL; }
		CTempList * def() { return NULL; }
		Targets * jumps()     { return NULL; }

	};

	class MOVE : IInstr {
	public:
		CTemp * dst;
		CTemp * src;

		MOVE(std::string & a, CTemp * d, CTemp * s) : dst(d), src(s) { assem = a; }

		CTempList * use() { return new CTempList(src, NULL); }
		CTempList * def() { return new CTempList(dst, NULL); }
		Targets * jumps() { return NULL; }

	};

	class OPER : IInstr {
	public:
		CTempList * dst;
		CTempList * src;
		Targets * jump;

		OPER(std::string & a, CTempList * d, CTempList * s, CLabelList * j = NULL) : dst(d), src(s)
		{
			assem = a; jump = new Targets(*j);
		}


		CTempList * use() { return src; }
		CTempList * def() { return dst; }
		Targets * jumps() { return jump; }

	};

}