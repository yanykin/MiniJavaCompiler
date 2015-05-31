// Author: Nikolay Levshin
// Реализация направленного графа

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

private:

    // Списки вершин, из которых можно попасть в i-ую вершину
    std::map<T*, std::vector<T*>> collectionListsIn;

    // Списки вершин, в которые можно попасть из i-ой вершины
    std::map<T*, std::vector<T*>> collectionListsOut;

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
bool CDirectGraph<T>::HasVertex( T* vertPtr ){
    assert( vertPtr != NULL );

    for( auto i = vertices.begin; i != vertices.end( ); ++i ){
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