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
            void AddVertice( const Temp::CTemp vert );

            // �������� �����
            void AddEdge( const Temp::CTemp& from, const Temp::CTemp& to );

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