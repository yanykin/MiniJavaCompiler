/*
* ����� �������, ����������� ��� ��������� ������� ���������
*/

#pragma once
#include "Symbol.h"
#include "IRTree.h"
#include <map>

namespace Frame {
	class CFrame;
}


namespace Frame {

	// ��������� ��� ���������� ������
	class IAccess {
	public:
		virtual ~IAccess() {}
		virtual const IRTree::IExp* GetExp( const Temp::CTemp* framePointer ) const = 0;
	};


	// CFrame ---------------------------------------------------------------------
	// �����-��������� � ���������-��������� ����������� � �������
	class CFrame {
	public:
		// ������� ����� ����� ������� � ������� ���������� ������������ ��� ����������
		CFrame( const Symbol::CSymbol* _name ) :
			name( _name ),
			formalCount( 0 ),
			framePointer( Temp::CTemp( Symbol::CSymbol::GetSymbol("FP") ) ),
			thisPointer( Temp::CTemp () ),
			returnPointer( Temp::CTemp( Symbol::CSymbol::GetSymbol( "RP" ) ) ),

			prologueLabel( Temp::CLabel() ),
			startLabel( Temp::CLabel() ),
			epilogueLabel( Temp::CLabel() )
		{};

		// �������� �������� �������
		void AddFormal( const Symbol::CSymbol* name );

		// �������� ��������� ����������
		void AddLocal( const Symbol::CSymbol* name );

		// �������� ���������� ��������� ����������
		int GetFormalCount() const { return formalCount; }

		// �������� � ���������� ������ �� ����� (��� ����� ���� ��� �������� �������, ��� � ��������� ����������)
		const IAccess* FindLocalOrFormal( const Symbol::CSymbol* name ) const;

		// ���������� ������ ��������� ����� � ������
		static int GetWordSize() { return wordSize; }

		const Temp::CTemp* FramePointer() const { return &framePointer; }
		const Temp::CTemp* ThisPointer() const { return &thisPointer; }
		const Temp::CTemp* ReturnPointer() const { return &returnPointer;  }

		// �������� ��� ������
		const Symbol::CSymbol* GetMethodName() const { return name; }

		const Temp::CLabel* GetPrologueLanel() const { return &prologueLabel; }
		const Temp::CLabel* GetStartLabel() const { return &startLabel; }
		const Temp::CLabel* GetEpilogueLabel() const { return &epilogueLabel; }

	private:
		static const int wordSize = 4; // ������ ��������� ����� ��� ����� ���������
		const Symbol::CSymbol* name; // ��� ������

		int formalCount; // ���������� ���������� ������ ����������
	
		std::map<const Symbol::CSymbol*, const IAccess*> localVariables; // ��������� ����������
		std::map<const Symbol::CSymbol*, const IAccess*> objectFields; // ���� �������, ����� �������� �� ��������
		std::map<const Symbol::CSymbol*, const IAccess*> methodFormals; // ��������� ������, ���������� ��� ������

		// ����������� ��������
		const Temp::CTemp framePointer;
		const Temp::CTemp thisPointer;
		const Temp::CTemp returnPointer; // ���� ����� ����� ���������� ������������ �������� �������

		// ����� ������, ���� � ������ �������
		Temp::CLabel prologueLabel;
		Temp::CLabel startLabel;
		Temp::CLabel epilogueLabel;
	};

	// ���������� ���������� � ������ ������������ ���������� �� ������
	class CVariableInFrame : public IAccess {
	public:
		CVariableInFrame( int _offsetInWords ) :
			offsetInWords( _offsetInWords ) {};
		virtual const IRTree::IExp* GetExp( const Temp::CTemp* framePointer ) const {
			// TODO: �����������
			return
				new IRTree::MEM(
				new IRTree::BINOP(
				IRTree::BO_PLUS,
				new IRTree::TEMP( framePointer ),
				new IRTree::CONST( offsetInWords * CFrame::GetWordSize() )
				)
				);
		}
	private:
		int offsetInWords; // �������� �� ������ �����
	};

	//...� � ������ ������������ � �����
	class CVariableInRegister : public IAccess {
	public:
		CVariableInRegister( const Temp::CTemp* _registerLabel ) : registerLabel( _registerLabel ) {};
		virtual const IRTree::IExp* GetExp( const Temp::CTemp* framePointer ) const {
			return new IRTree::TEMP( registerLabel );
		}
	private:
		const Temp::CTemp* registerLabel; // ��������� ����������, ��������������� �������
	};

} // namespace Frame