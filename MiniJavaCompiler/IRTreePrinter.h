#pragma once

#include "IRTree.h"
#include "IRTreeVisitor.h"
#include <string>
#include <fstream>
#include <map>
#include <stack>

/*
Реализация патерна "Посетитель" для дерева промежуточного представления
*/

namespace IRTree {
	class CIRTreePrinter : public IIRTreeVisitor
	{
	public:
		// В качестве параметра конструктора передаём имя файла, куда будем записывать структуру дерева в формате GraphViz
		CIRTreePrinter( const std::string& outputFileName );
		~CIRTreePrinter();

		// Методы, "посещающие" те или иные узлы дерева
		// Подклассы IRTree::IExp
		void Visit( const CONST* node );
		void Visit( const NAME* node );
		void Visit( const TEMP* node );
		void Visit( const BINOP* node );
		void Visit( const MEM* node );
		void Visit( const CALL* node );
		void Visit( const ESEQ* node );

		// Подклассы IRTree::IStm
		void Visit( const MOVE* node );
		void Visit( const EXP* node );
		void Visit( const JUMP* node );
		void Visit( const CJUMP* node );
		void Visit( const SEQ* node );
		void Visit( const LABEL* node );

		// Посещение вспомогательных узлов
		void Visit( const CExpList* node );
		void Visit( const CStmList* node );

		void WriteGraphStructureToTheFile() {
			// Начало файла
			graphvizOutputFile << "digraph {" << std::endl << "node [shape=\"plaintext\"]" << std::endl;

			// Перечисление всех пар рёбер
			for ( auto& edge : treeEdges ) {
				graphvizOutputFile << edge.first << " -> " << edge.second << std::endl;
			}

			// Перечисление всех вершин
			for ( auto& node : nodeLabels ) {
				graphvizOutputFile << node.first << "[ label = \"" << node.second << "\" ]" << std::endl;
			}

			// Конец файла
			graphvizOutputFile << "}" << std::endl;
		}

	private:
		std::ofstream graphvizOutputFile;

		// Порядковый номер текущего узла
		size_t currentNodeID;
		// Порядковый номер последнего посещённого узла (необходимо для создания рёбер)
		size_t lastVisitedNodeID;

		// Общее количество пройденных узлов
		size_t totalVisitedNodes;

		// Стек посещений (на вершине стека будет храниться номер вершины, где сейчас находится посетитель)
		std::stack<size_t> nodeStack;

		// Вспомогательная функция, которая вызывается при посещении каждого узла
		void visitNewNode() {
			lastVisitedNodeID = currentNodeID;

			totalVisitedNodes += 1;
			currentNodeID = totalVisitedNodes;
			nodeStack.push( currentNodeID );

			this->addEdge( lastVisitedNodeID, currentNodeID );
		};

		// Вызывается, когда мы полностью обошли всё поддерево
		void leaveNode() {
			lastVisitedNodeID = currentNodeID;

			nodeStack.pop();
			if ( !nodeStack.empty() ) {
				currentNodeID = nodeStack.top();
			}
			else {
				// TODO: полностью завершили обход
			}
		}

		size_t createNewNode() {
			totalVisitedNodes += 1;
			return totalVisitedNodes;
		}

		// Вспомогательная структура, которая каждому узлу присваивает порядковый номер и для него задаёт текстовый атрибут
		std::map<size_t, std::string> nodeLabels;

		// Задаёт пары номеров, обозначающие рёбра в дереве
		typedef std::pair<size_t, size_t> CGraphVizEdge;
		std::vector<CGraphVizEdge> treeEdges;

		void addEdge( size_t from, size_t to ) {
			treeEdges.push_back( CGraphVizEdge (from, to) );
		}

		
	};
}


