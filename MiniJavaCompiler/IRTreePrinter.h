#pragma once

#include "IRTree.h"
#include "IRTreeVisitor.h"
#include <string>
#include <fstream>
#include <map>
#include <stack>

/*
���������� ������� "����������" ��� ������ �������������� �������������
*/

namespace IRTree {
	class CIRTreePrinter : IIRTreeVisitor
	{
	public:
		// � �������� ��������� ������������ ������� ��� �����, ���� ����� ���������� ��������� ������ � ������� GraphViz
		CIRTreePrinter( const std::string& outputFileName );
		~CIRTreePrinter();

		// ������, "����������" �� ��� ���� ���� ������
		// ��������� IRTree::IExp
		void Visit( const CONST* node );
		void Visit( const NAME* node );
		void Visit( const TEMP* node );
		void Visit( const BINOP* node );
		void Visit( const MEM* node );
		void Visit( const CALL* node );
		void Visit( const ESEQ* node );

		// ��������� IRTree::IStm
		void Visit( const MOVE* node );
		void Visit( const EXP* node );
		void Visit( const JUMP* node );
		void Visit( const CJUMP* node );
		void Visit( const SEQ* node );
		void Visit( const LABEL* node );

	private:
		std::ofstream graphvizOutputFile;

		// ���������� ����� �������� ����
		size_t currentNodeID;

		// ����� ���������� ���������� �����
		size_t totalVisitedNodes;

		// ���� ���������
		std::stack<size_t> nodeStack;

		// ��������������� ���������, ������� ������� ���� ����������� ���������� ����� � ��� ���� ����� ��������� �������
		std::map<size_t, std::string> nodeLabels;
		// ����� ���� �������, ������������ ���� � ������
		
		typedef std::pair<size_t, size_t> CGraphVizEdge;
		std::vector<CGraphVizEdge> treeEdges;

		void addEdge( size_t from, size_t to ) {
			treeEdges.push_back( CGraphVizEdge (from, to) );
		}
	};
}


