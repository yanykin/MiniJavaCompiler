/*
* ����� �������, ����������� ��� ��������� ������� ���������
*/

#pragma once
#include "Symbol.h"
#include "IRTree.h"
#include <map>

namespace Frame {

	// ��������� ��� ���������� ������
	class IAccess {
	public:
		virtual ~IAccess() {}
		virtual const IRTree::IExp* GetExp( const Temp::CTemp* framePointer ) const = 0;
	};

	// ���������� ���������� � ������ ������������ ���������� �� ������
	class CVariableInFrame : public IAccess {
	public:
		CVariableInFrame( int _offsetInWords ) :
			offsetInWords(_offsetInWords) {};
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
		CVariableInRegister(const Temp::CTemp* _registerLabel): registerLabel(_registerLabel) {};
		virtual const IRTree::IExp* GetExp( const Temp::CTemp* framePointer ) const {
			return new IRTree::TEMP( registerLabel );
		}
	private:
		const Temp::CTemp* registerLabel; // ��������� ����������, ��������������� �������
	};

	// CFrame ---------------------------------------------------------------------
	// �����-��������� � ���������-��������� ����������� � �������
	class CFrame {
	public:
		// ������� ����� ����� ������� � ������� ���������� ������������ ��� ����������
		CFrame( const Symbol::CSymbol* _name ) :
			name( _name ),
			formalCount( 0 ),
			framePointer( Temp::CTemp() ),
			thisPointer( Temp::CTemp() ),
			returnPointer( Temp::CTemp() )
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
		static const int GetWordSize() { return wordSize; }

		const Temp::CTemp* FramePointer() const { return &framePointer; }
		const Temp::CTemp* ThisPointer() const { return &thisPointer; }
		const Temp::CTemp* ReturnPointer() const { return &returnPointer;  }

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

	};

} // namespace Frame