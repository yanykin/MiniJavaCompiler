// Автор: Николай Левшин
// Описание: Граф взаимодействия вершин

#pragma once

#include "ControlFlowGraphBuilder.h"


#include <unordered_map>
#include <unordered_set>

namespace RegisterAllocation {

    class CInterferenceGraphBuilder {

    public:

        // Класс, в которм будем хранить граф
        class CInterferenceGraph {
        public:

            // Добавить вершину
            void AddVertice( const Temp::CTemp vert );

            // Добавить ребро
            void AddEdge( const Temp::CTemp& from, const Temp::CTemp& to );

        private:
            std::unordered_map<Temp::CTemp, std::unordered_set<Temp::CTemp>> edges;
            std::unordered_set<Temp::CTemp> vertices;
        };

        // Построить граф взаимодействия по графу потока управления
        void Build( const CDirectGraph<CControlFlowVertex>& controlFlowGraph );

        // Получить построенный граф
        const CInterferenceGraph& Get();

    private:

        CInterferenceGraph interferenceGraph;

    };
}