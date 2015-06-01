// �����: ������� ������
// ��������: ���� �������������� ������

#pragma once

#include "ControlFlowGraphBuilder.h"


#include <unordered_map>
#include <unordered_set>

namespace RegisterAllocation {

    class CInterferenceGraphBuilder {

    public:

        // �����, � ������ ����� ������� ����
        class CInterferenceGraph {
        public:

            // �������� �������
            void AddVertice( const Temp::CTemp& vert );

            // �������� �����
            void AddEdge( const Temp::CTemp& from, const Temp::CTemp& to );

            // ������� �������
            void RemoveVertice( const Temp::CTemp& vert );

            // �������� ������
            size_t GetSize() { return vertices.size(); }

            // �������� ������� �������
            const std::unordered_set<Temp::CTemp>& GetNeigbours( const Temp::CTemp& vert ) const;

            // �������� ������ ������
            const std::unordered_set<Temp::CTemp>& GetVertices() { return vertices; }

            // G������ ������� �������
            size_t GetDegree( const Temp::CTemp& vert );

            // ���� �� ������ ������� � �����?
            bool HasVetrice( const Temp::CTemp& vert ) { return vertices.find( vert ) != vertices.end(); }

        private:
            std::unordered_map<Temp::CTemp, std::unordered_set<Temp::CTemp>> edges;
            std::unordered_set<Temp::CTemp> vertices;
        };

        // ��������� ���� �������������� �� ����� ������ ����������
        void Build( const CDirectGraph<CControlFlowVertex>& controlFlowGraph );

        // �������� ����������� ����
        const CInterferenceGraph& Get();

    private:

        CInterferenceGraph interferenceGraph;

    };
}