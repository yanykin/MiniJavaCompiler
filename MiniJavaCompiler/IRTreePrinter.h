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
	class CIRTreePrinter : IIRTreeVisitor
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

	private:
		std::ofstream graphvizOutputFile;

		// Порядковый номер текущего узла
		size_t currentNodeID;

		// Общее количество пройденных узлов
		size_t totalVisitedNodes;

		// Стек посещений
		std::stack<size_t> nodeStack;

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


