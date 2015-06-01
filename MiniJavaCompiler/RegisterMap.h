// Автор: Николай Левшин
// Описание: Построение карты раскраски ( распределение по регистрам )


#pragma once

#include "InterferenceGraph.h"

#include <unordered_map>
#include <stack>

namespace RegisterAllocation {

    class CRegisterMapBuilder {
    public:
        CRegisterMapBuilder( int k, const CInterferenceGraphBuilder::CInterferenceGraph& interferenceGraph );

        // Попробовать раскрасить, если удалось, в isColored будет записано TRUE
        void Build();

        // Получить раскраску
        std::unordered_map<Temp::CTemp, int>& GetMap();
        
    private:
        // один шаг упрощения, возвращает FALSE, если упрощение не удалось
        bool Simplify();

        // Подбираем вершине подходящий цвет
        void ChooseColor( Temp::CTemp& vert );

        // стек, в который сбрасываются вершины при упрощении
        std::stack<Temp::CTemp> vertStack;

        // исходный граф взаимодействия переменных
        const CInterferenceGraphBuilder::CInterferenceGraph sourceInterferenceGraph;

        // текущий, упрощенный граф
        CInterferenceGraphBuilder::CInterferenceGraph temporaryInterferenceGraph;

        // количество доступных регистров
        const int k = 6;

        // раскрашен ли граф
        bool isColored = false;

        // карта раскраски
        std::unordered_map<Temp::CTemp, int> colorMap;
    };
    
}