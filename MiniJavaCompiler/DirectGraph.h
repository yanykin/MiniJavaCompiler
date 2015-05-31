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
    bool HasVertex( const T* vertPtr );
    bool HasEdge( const T* from, const T* to );

    // Получит текущий список вершин
    const std::vector<T*> GetVertices() const;

    // Получить список вершин, в которые можно попасть
    std::vector<T*> GetListOut( const T* vert);

private:

    // Списки вершин, из которых можно попасть в i-ую вершину
    std::map<const T*, std::vector<T*>> collectionListsIn;

    // Списки вершин, в которые можно попасть из i-ой вершины
    std::map<const T*, std::vector<T*>> collectionListsOut;

    // Массив вершин
    std::vector<T*> vertices;
};



/*
Реализация
*/

template<typename T>
void CDirectGraph<T>::AddVertex( T* vertPtr ){

    assert( vertPtr != NULL );

    // Повторное добавление недопустимо
    assert( HasVertex( vertPtr ) );

    vertices.push_back( vertPtr );

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

    collectionListsIn[to].push_back( from );
    collectionListsOut[from].push_back( to );
}

template<typename T>
bool CDirectGraph<T>::HasVertex( const T* vertPtr ){
    assert( vertPtr != NULL );

    for( auto i = vertices.begin(); i != vertices.end( ); ++i ){
        if( *i == vertPtr ) {
            return true;
        }
    }
    return false;
}

template<typename T>
bool CDirectGraph<T>::HasEdge( const T* from, const T* to ){
    assert( from != NULL && to != NULL );

    for( auto i = collectionListsIn[to].begin( ); i != collectionListsIn[to].end( ); ++i ){
        if( *i == from ) {
            return true;
        }
    }

    return false;
}

template<typename T>
const std::vector<T*> CDirectGraph<T>::GetVertices() const {
    return vertices;
}

template<typename T>
std::vector<T*> CDirectGraph<T>::GetListOut( const T* vert ) {
    assert( HasVertex( vert ) );
    return collectionListsOut[vert];
}
