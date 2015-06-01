// Author: Nikolay Levshin
// Реализация направленного графа

#pragma once

#include <map>
#include <vector>
#include <assert.h>


template<typename T>
class CDirectGraph {
public:
    // Добавляет новую вершину
    void AddVertex( T* vertPtr );

    // Добавляет новое ребро
    void AddEdge( T* from, T* to );

    //  Проверка на наличие элементов в графе
    bool HasVertex( T* vertPtr );
    bool HasEdge( T* from, T* to );

    // Получить текущий список вершин
    std::vector<T*> GetVertices() const;

    // Построить список вершин в порядке обхода DFS
    void BuidDFSVertices();

    // Получить список вершин в порядке обхода DFS
    std::vector<T*> GetDFSVertices() const; 

    // Получить список вершин, в которые можно попасть
    std::vector<T*> GetListOut( T* vert);

private:

    // Списки вершин, из которых можно попасть в i-ую вершину
    std::map<T*, std::vector<T*>> collectionListsIn;

    // Списки вершин, в которые можно попасть из i-ой вершины
    std::map<T*, std::vector<T*>> collectionListsOut;

    // Массив вершин
    std::vector<T*> vertices;

    // Массив вершин в порядке обхода DFS
    std::vector<T*> verticesDFS;

    // Множество вершин с метками о посещении
    std::unordered_set<const T*> visited;

    // Шаг алгоритма DFS
    void VisitDFS( T* vert );

    // Построено ли DFS представление
    bool isDFSVertices = false;
};



/*
Реализация
*/

template<typename T>
void CDirectGraph<T>::AddVertex( T* vertPtr ){

    assert( vertPtr != NULL );

    // Повторное добавление недопустимо
    assert( !HasVertex( vertPtr ) );

    vertices.push_back( vertPtr );

    isDFSVertices = false;

    // Создаем пустые списки для новой вершины
    collectionListsIn[vertPtr];
    collectionListsOut[vertPtr];
}

template<typename T>
void CDirectGraph<T>::AddEdge( T* from, T* to ){

    assert( from != NULL && to != NULL );

    // Вершины должны существовать
    assert( HasVertex( from ) );
    assert( HasVertex( to ) );

    assert( !HasEdge( from, to ) );

    isDFSVertices = false;

    collectionListsIn[to].push_back( from );
    collectionListsOut[from].push_back( to );
}

template<typename T>
bool CDirectGraph<T>::HasVertex( T* vertPtr ){
    assert( vertPtr != NULL );

    for( auto i = vertices.begin(); i != vertices.end( ); ++i ){
        if( *i == vertPtr ) {
            return true;
        }
    }
    return false;
}

template<typename T>
bool CDirectGraph<T>::HasEdge( T* from, T* to ){
    assert( from != NULL && to != NULL );

    for( auto i = collectionListsIn[to].begin( ); i != collectionListsIn[to].end( ); ++i ){
        if( *i == from ) {
            return true;
        }
    }

    return false;
}

template<typename T>
std::vector<T*> CDirectGraph<T>::GetVertices() const {
    return vertices;
}

template<typename T>
void CDirectGraph<T>::BuidDFSVertices(){
    verticesDFS.clear();
    for( auto& nextVert : collectionListsOut[vertices[0]] ) {
        if( visited.find( nextVert ) != visited.end( ) ) {
            VisitDFS( nextVert );
        }
    }
    isDFSVertices = true;
}

template<typename T>
void CDirectGraph<T>::VisitDFS( T* vert ){
//    verticesDFS.push_back( vert );
    visited.insert( vert );
    for( auto& nextVert : collectionListsOut[vert] ) {
        if( visited.find( nextVert ) != visited.end() ) {
            VisitDFS( nextVert );
        }
    }
    return;
}

template<typename T>
std::vector<T*> CDirectGraph<T>::GetListOut( T* vert ) {
    assert( HasVertex( vert ) );
    return collectionListsOut[vert];
}

template<typename T>
std::vector<T*> CDirectGraph<T>::GetDFSVertices() const {

    //Сначала нужно построить DFS представление, вызовите BuildDFSVertices
    assert( isDFSVertices );
    return verticesDFS;
}