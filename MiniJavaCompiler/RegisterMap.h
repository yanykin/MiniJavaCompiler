// �����: ������� ������
// ��������: ���������� ����� ��������� ( ������������� �� ��������� )


#pragma once

#include "InterferenceGraph.h"

#include <unordered_map>
#include <stack>

namespace RegisterAllocation {

    class CRegisterMapBuilder {
    public:
        CRegisterMapBuilder( int k, const CInterferenceGraphBuilder::CInterferenceGraph& interferenceGraph );

        // ����������� ����������, ���� �������, � isColored ����� �������� TRUE
        void Build();

        // �������� ���������
        std::unordered_map<Temp::CTemp, int>& GetMap();
        
    private:
        // ���� ��� ���������, ���������� FALSE, ���� ��������� �� �������
        bool Simplify();

        // ��������� ������� ���������� ����
        void ChooseColor( Temp::CTemp& vert );

        // ����, � ������� ������������ ������� ��� ���������
        std::stack<Temp::CTemp> vertStack;

        // �������� ���� �������������� ����������
        const CInterferenceGraphBuilder::CInterferenceGraph sourceInterferenceGraph;

        // �������, ���������� ����
        CInterferenceGraphBuilder::CInterferenceGraph temporaryInterferenceGraph;

        // ���������� ��������� ���������
        const int k = 6;

        // ��������� �� ����
        bool isColored = false;

        // ����� ���������
        std::unordered_map<Temp::CTemp, int> colorMap;
    };
    
}