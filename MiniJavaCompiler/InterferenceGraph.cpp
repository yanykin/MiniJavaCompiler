// �����: ������� ������

#include "InterferenceGraph.h"

namespace RegisterAllocation {

    void CInterferenceGraphBuilder::CInterferenceGraph::AddVertice( const Temp::CTemp vert ) {
        assert( vertices.find( vert ) == vertices.end() );
        vertices.insert( vert );

        // ��������� ������� � ��������� �����
        edges[vert];
    }

    void CInterferenceGraphBuilder::CInterferenceGraph::AddEdge( const Temp::CTemp& from, const Temp::CTemp& to ) {
        
        assert( vertices.find( from ) != vertices.end() );
        assert( vertices.find( to ) != vertices.end() );
        // assert( edges[from].find( to ) == edges[from].end() );

        // ��������� �����
        edges[from].insert( to );
    }

    void CInterferenceGraphBuilder::Build( const CDirectGraph<CControlFlowVertex>& controlFlowGraph ) {
        const std::vector<CControlFlowVertex*>& vertices = controlFlowGraph.GetVertices();
        
        // ��������� ���� ���������
        std::unordered_set<Temp::CTemp> tempSet;
        for( const auto& vert : vertices ) {
            tempSet.insert( vert->defs.begin(), vert->defs.end() );
            tempSet.insert( vert->uses.begin(), vert->uses.end() );
        }

        for( const auto& vert : tempSet ) {
            interferenceGraph.AddVertice( vert );
        }

        // ����������� �����
        for( const auto& vert : vertices ) {
            if( vert->isMove ) {

                // � MOVE - ���������� a<-c ��� ���� b_1,..b_n �� live-out, �� ������ �, ��������� ����(a, b_1),...,(a,b_n)
                assert( vert->defs.size() == 1 );
                assert( vert->uses.size() == 1 );

                const Temp::CTemp& def = *vert->defs.begin();
                const Temp::CTemp& use = *vert->uses.begin();

                for( const Temp::CTemp& b : vert->liveOut ) {
                    if( b == def ) {
                        // �� ��������� ������� ���� � �����
                    }
                    if( b != use ) {
                        interferenceGraph.AddEdge( def, b );
                    }
                }
            }
            else {
                // � ����� ��-MOVE ����������, ������� ���������� ��������� ���������� �, ��� ���� 
                // ���������� b_1,...,b_n �� live-out ��������� ���� �������������� (a,b_1),...,(a,b_n)

                for( const Temp::CTemp& def : vert->defs ) {
                    for( const Temp::CTemp& b : vert->liveOut ) {
                        interferenceGraph.AddEdge( def, b );
                    }
                }
            }
        }
    }
}