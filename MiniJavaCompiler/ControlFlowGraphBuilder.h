// �����: ������� ������
// ��������: ���� ������ ����������

#pragma once

#include <unordered_set>
#include<vector>

#include "Temp.h"
#include "Instruction.h"
#include "DirectGraph.h"



namespace RegisterAllocation {


    // ������� �����
    struct CControlFlowVertex {

        // ��������� ����������, ������������ � ������ �������
        std::unordered_set<Temp::CTemp> defs;

        // ��������� ����������, ������������ � ������ �������
        std::unordered_set<Temp::CTemp> uses;

        // �������� �� ���������� � ������ ������� MOVE
        bool isMove;

        // ����� ���������� ����������� � ������ �������
        const CodeGeneration::IInstruction* const instruction;

        CControlFlowVertex( const CodeGeneration::IInstruction* instruction );

        // ��������� ����������, ������� ���� �� �����-���� �� �������� ����� ����
        std::unordered_set<Temp::CTemp> liveIn;

        // ��������� ����������, ������� ���� �� �����-���� ��������� �����
        std::unordered_set<Temp::CTemp> liveOut;

        bool operator == ( const CControlFlowVertex& other ) const;

    };



    // ��������, �������� ���� ������ ����������
    class CControlFlowGraphBuilder {

        // ��������� ����
        void Build( const std::vector<CodeGeneration::IInstruction*>& instructions );

        // �������� ����������� ����
        const CDirectGraph<CControlFlowVertex>& Get() {
            return controlFlowGraph;
        }

    private:
        // ���� ������ ���������� (���������)
        CDirectGraph<CControlFlowVertex> controlFlowGraph;

        // ��������� � ���� �������, ��������������� �����������
        void AddInsructions( const std::vector<CodeGeneration::IInstruction*>& instruction );

        // ��������� LiveIn LiveOut, �������� �� ����������
        bool UpdateLiveInOut( CControlFlowVertex* vertex );

    };

}