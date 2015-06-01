// �����: ������� ������

#include "RegisterMap.h"

namespace RegisterAllocation {

    CRegisterMapBuilder::CRegisterMapBuilder( int k, const CInterferenceGraphBuilder::CInterferenceGraph& interferenceGraph ) : 
    k( k ),
    sourceInterferenceGraph( interferenceGraph )
    {}

    void CRegisterMapBuilder::Build() {

        // �������� ����, �������� ������� �� ����
        while( temporaryInterferenceGraph.GetSize() != 0 ) {
            if( !Simplify() ) {
                isColored = false;
                return;
            }
        }

        // ������ �������, ������ �� �� �����
        while( !vertStack.empty() ) {
            // ��������� ������� � ��� ���������� ����
            temporaryInterferenceGraph.AddVertice( vertStack.top() );

            // ��������������� ����� � ��� ������������ ���������
            for( const auto& vert : sourceInterferenceGraph.GetNeigbours( vertStack.top() ) ) {
                if( temporaryInterferenceGraph.HasVetrice( vert ) ){
                    temporaryInterferenceGraph.AddEdge( vertStack.top(), vert );
                }
            }

            // �������� ����, �������� ��� � �������
            ChooseColor( vertStack.top() );
            vertStack.pop();
        }
        isColored = true;
    }

    bool CRegisterMapBuilder::Simplify() {
        bool isSimpleable = false;
        Temp::CTemp removeVert;
        
        for( const auto& vert : temporaryInterferenceGraph.GetVertices() ) {
            if( temporaryInterferenceGraph.GetDegree( vert ) < k ) {
                removeVert = vert;
                isSimpleable = true;
                break;
            }
        }
        if( isSimpleable ) {
            temporaryInterferenceGraph.RemoveVertice( removeVert );
            vertStack.push( removeVert );
            return true;
        }

        return false;
    }

    void CRegisterMapBuilder::ChooseColor( Temp::CTemp& vert ) {

        std::vector<bool> avaliableColors (k, true);

        // �������, ����� ����� ������
        for( auto &vert : temporaryInterferenceGraph.GetNeigbours( vert ) ) {
            avaliableColors[colorMap[vert]] = false;
        }

        // �������� ��������� ����
        int color = 0;
        while( !avaliableColors[color] ) {
            ++color;
        }
        colorMap.insert( std::make_pair(vert, color) );
    }

    std::unordered_map<Temp::CTemp, int>& CRegisterMapBuilder::GetMap() {
        assert( isColored );
        return colorMap;
    }
}