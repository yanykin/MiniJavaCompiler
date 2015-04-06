#include "Instr.h"
//алгоритм покрытия IRTree патернами поддеревьев

using namespace IRTree;

namespace Assem
{
	

	class Codegen {
	public:
		Codegen(Frame * f) : frame(f) {}
		InstrList * codegen(IStm * s);
	private: 
		InstrList * ilist = NULL, * last = NULL;
		void emit(IInstr * inst);

		void munchStm(SEQ * stm);
		void munchStm(MOVE * stm);
		void munchStm(LABEL * stm);

		CTemp * munchExp(BINOP * exp);
		CTemp * munchExp(MEM * exp);
		CTemp * munchExp(CONST * exp);
		CTemp * munchExp(TEMP * exp) { return exp->GetTemp; }

		Frame * frame;
	};

	class Frame {
	public:
		InstrList * codegen(IStm * stm)
		{
			return (new Codegen(this)) -> codegen(stm);
		}
	};

}

