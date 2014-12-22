/*
* ����� �������, ����������� ��� ��������� ������� ���������
*/

#pragma once
#include "Symbol.h"
#include "IRTree.h"
#include <map>

namespace Frame {

	// ���������� ������
	class IAccess {
	public:
		virtual ~IAccess() {}
		virtual const IRTree::IExp* GetExp( const IRTree::IExp* framePointer ) const = 0;
	};

	// CFrame ---------------------------------------------------------------------
	// �����-��������� � ���������-��������� ����������� � �������
	class CFrame {
	public:
		// ������� ����� ����� ������� � ������� ���������� ������������ ��� ����������
		CFrame( const Symbol::CSymbol* name );

		// ������ � ���������� ���������� � ��������� ����������
		void AddFormal( const Symbol::CSymbol* name );
		void AddLocal( const Symbol::CSymbol* name );

		const IAccess* FindLocalOrFormal( const Symbol::CSymbol* name ) const;
		int WordSize() const { return wordSize; }
		const Temp::CTemp* FramePointer() const { return &fp; }
		const Temp::CTemp* ThisPointer() const { return &thisPtr; }

	private:
		// ������ ��������� ����� ��� ����� ���������
		static const int wordSize = 4;
		const Symbol::CSymbol* name; // ��� ������
		std::map<const Symbol::CSymbol*, const IAccess*> locals;

		// ����������� ��������
		const Temp::CTemp fp;
		const Temp::CTemp thisPtr;

	};

} // namespace Frame