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
	class CIRTreePrinter : public IIRTreeVisitor
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

		// ��������� ��������������� �����
		void Visit( const CExpList* node );
		void Visit( const CStmList* node );

		void OpenFile() {
			// ������ �����
			graphvizOutputFile << "digraph {" << std::endl << "node [shape=\"plaintext\"]" << std::endl;
		}

		void CloseFile() {
			// ����� �����
			graphvizOutputFile << "}" << std::endl;
			graphvizOutputFile.close();
		}

		void WriteGraphStructureToTheFile() {
			
			// ������������ ���� ��� ����
			for ( auto& edge : treeEdges ) {
				graphvizOutputFile << prefix << edge.first << " -> " << prefix << edge.second << std::endl;
			}

			// ������������ ���� ������
			for ( auto& node : nodeLabels ) {
				graphvizOutputFile << prefix << node.first << "[ label = \"" << node.second << "\" ]" << std::endl;
			}

		}

		void ResetPrinter( const std::string& nodesPrefix ) {
			totalVisitedNodes = 0;
			currentNodeID = lastVisitedNodeID = 0;
			
			nodeLabels.clear();
			treeEdges.clear();

			prefix = nodesPrefix;
		}

	private:
		std::ofstream graphvizOutputFile;

		// �������, ������� �������� ����� �������� �����, ����� ��������� ���������
		std::string prefix;

		// ���������� ����� �������� ����
		size_t currentNodeID;
		// ���������� ����� ���������� ����������� ���� (���������� ��� �������� ����)
		size_t lastVisitedNodeID;

		// ����� ���������� ���������� �����
		size_t totalVisitedNodes;

		// ���� ��������� (�� ������� ����� ����� ��������� ����� �������, ��� ������ ��������� ����������)
		std::stack<size_t> nodeStack;

		// ��������������� �������, ������� ���������� ��� ��������� ������� ����
		void visitNewNode() {
			lastVisitedNodeID = currentNodeID;

			totalVisitedNodes += 1;
			currentNodeID = totalVisitedNodes;
			nodeStack.push( currentNodeID );

			if ( lastVisitedNodeID != 0 ) {
				this->addEdge( lastVisitedNodeID, currentNodeID );
			}
			
		};

		// ����������, ����� �� ��������� ������ �� ���������
		void leaveNode() {
			lastVisitedNodeID = currentNodeID;

			nodeStack.pop();
			if ( !nodeStack.empty() ) {
				currentNodeID = nodeStack.top();
			}
			else {
				// TODO: ��������� ��������� �����
			}
		}

		size_t createNewNode() {
			totalVisitedNodes += 1;
			return totalVisitedNodes;
		}

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


