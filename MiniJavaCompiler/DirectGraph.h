// Author: Nikolay Levshin
// Объявления направленного графа

#pragma once

#include <map>
#include <vector>


template<typename T>
class CDirectGraph {
public:
    // Добавляет новую вершину
    void AddVertex( T* vertPtr);

    // Добавляет новое ребро
    void AddEdge( const T& from, const T& to );
    void AddEdge( T* from, T* to );

    //  Проверка на наличие элементов в графе
    bool HasVertex( const T& val );
    bool HasEdge( const T& from, const T& to );

private:

    // Списки вершин, из которых можно попасть в i-ую вершину
    std::map<T*, std::vector<T*>> collectionListsIn;

    // Списки вершин, в которые можно попасть из i-ой вершины
    std::map<T*, std::vector<T*>> collectionListsOut;

    // Массив вершин
    vector<T*> vertices;
};