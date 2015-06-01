// Автор: Николай Левшин
// Описание: Граф потока управления

#pragma once

#include <unordered_set>
#include<vector>

#include "Temp.h"
#include "Instruction.h"
#include "DirectGraph.h"



namespace RegisterAllocation {


    // Вершина графа
    struct CControlFlowVertex {

        // множество переменных, определяемых в данной вершине
        std::unordered_set<Temp::CTemp> defs;

        // множество переменных, используемых в данной вершине
        std::unordered_set<Temp::CTemp> uses;

        // является ли инструкция в данной вершине MOVE
        bool isMove;

        // какая инструкция расположана в данной вершине
        const CodeGeneration::IInstruction* const instruction;

        CControlFlowVertex( const CodeGeneration::IInstruction* instruction );

        // Множество переменных, которые живы на каком-либо из входящих ребер узла
        std::unordered_set<Temp::CTemp> liveIn;

        // Множество переменных, которые живы на каком-лиюо выходящем ребре
        std::unordered_set<Temp::CTemp> liveOut;

        bool operator == ( const CControlFlowVertex& other ) const;

    };



    // Механизм, строящий граф потока управления
    class CControlFlowGraphBuilder {

    public:

        // Построить граф
        void Build( const CodeGeneration::TInstructionsList& instructions );

        // Получить построенный граф
        const CDirectGraph<CControlFlowVertex>& Get() {
            return controlFlowGraph;
        }

    private:
        // Граф потока управления (результат)
        CDirectGraph<CControlFlowVertex> controlFlowGraph;

        // Добавляет в граф вершины, соответствующие инструкциям
        void AddInsructions( const CodeGeneration::TInstructionsList& instruction );

        // Обновляет LiveIn LiveOut, сообщает об изменениях
        bool UpdateLiveInOut( CControlFlowVertex* vertex );

    };

}