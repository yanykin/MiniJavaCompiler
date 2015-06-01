// Автор: Николай Левшин

#include "InterferenceGraph.h"

namespace RegisterAllocation {

    void CInterferenceGraphBuilder::CInterferenceGraph::AddVertice( const Temp::CTemp& vert ) {
        assert( vertices.find( vert ) == vertices.end() );
        vertices.insert( vert );

        // Довавляем вершину в хранилище ребер
        edges[vert];
    }

    void CInterferenceGraphBuilder::CInterferenceGraph::AddEdge( const Temp::CTemp& from, const Temp::CTemp& to ) {
        
        assert( vertices.find( from ) != vertices.end() );
        assert( vertices.find( to ) != vertices.end() );
        // assert( edges[from].find( to ) == edges[from].end() );

        // Добавляем ребро
        edges[from].insert( to );
    }

    void CInterferenceGraphBuilder::CInterferenceGraph::RemoveVertice( const Temp::CTemp& vert ) {
        assert( vertices.find( vert ) != vertices.end() );

        // Удаляем все входящие ребра
        for( auto& vertList : edges ) {
            auto vertPtr =vertList.second.find( vert );
            if( vertPtr != vertList.second.end() ) {
                vertList.second.erase( vertPtr );
            }
        }

        // Удаляем исходящие ребра
        edges.erase( vert );

        // Удаляем вершины
        vertices.erase( vert );
    }

    const std::unordered_set<Temp::CTemp>& CInterferenceGraphBuilder::CInterferenceGraph::GetNeigbours( const Temp::CTemp& vert ) const {
        assert( vertices.find( vert ) != vertices.end() );
        return edges.find(vert)->second;
    }

    size_t CInterferenceGraphBuilder::CInterferenceGraph::GetDegree( const Temp::CTemp& vert ) {
        assert( vertices.find( vert ) != vertices.end() );
        return edges[vert].size();
    }

    void CInterferenceGraphBuilder::Build( const CDirectGraph<CControlFlowVertex>& controlFlowGraph ) {
        const std::vector<CControlFlowVertex*>& vertices = controlFlowGraph.GetVertices();
        
        // Заполняем граф вершинами
        std::unordered_set<Temp::CTemp> tempSet;
        for( const auto& vert : vertices ) {
            tempSet.insert( vert->defs.begin(), vert->defs.end() );
            tempSet.insert( vert->uses.begin(), vert->uses.end() );
        }

        for( const auto& vert : tempSet ) {
            interferenceGraph.AddVertice( vert );
        }

        // Расставляем ребра
        for( const auto& vert : vertices ) {
            if( vert->isMove ) {

                // В MOVE - инструкции a<-c для всех b_1,..b_n из live-out, не равных с, добавляем пары(a, b_1),...,(a,b_n)
                assert( vert->defs.size() == 1 );
                assert( vert->uses.size() == 1 );

                const Temp::CTemp& def = *vert->defs.begin();
                const Temp::CTemp& use = *vert->uses.begin();

                for( const Temp::CTemp& b : vert->liveOut ) {
                    if( b == def ) {
                        // Не соединяем вершину саму с собой
                    }
                    if( b != use ) {
                        interferenceGraph.AddEdge( def, b );
                    }
                }
            }
            else {
                // В любой не-MOVE инструкции, которая определяет некоторую переменную а, для всех 
                // переменных b_1,...,b_n из live-out добавляем пары взаимодействия (a,b_1),...,(a,b_n)

                for( const Temp::CTemp& def : vert->defs ) {
                    for( const Temp::CTemp& b : vert->liveOut ) {
                        interferenceGraph.AddEdge( def, b );
                    }
                }
            }
        }
    }
}