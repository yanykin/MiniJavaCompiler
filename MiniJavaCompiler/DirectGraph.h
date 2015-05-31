// Author: Nikolay Levshin
// ���������� ������������� �����

#pragma once

#include <map>
#include <vector>
#include <assert.h>


template<typename T>
class CDirectGraph {
public:
    // ��������� ����� �������
    void AddVertex( T* vertPtr );

    // ��������� ����� �����
    void AddEdge( T* from, T* to );

    //  �������� �� ������� ��������� � �����
    bool HasVertex( T* vertPtr );
    bool HasEdge( T* from, T* to );

    // ������� ������� ������ ������
    std::vector<T*> GetVertices();

    // �������� ������ ������, � ������� ����� �������
    std::vector<Y*> GetListOut( const T* vert);

private:

    // ������ ������, �� ������� ����� ������� � i-�� �������
    std::map<T*, std::vector<T*>> collectionListsIn;

    // ������ ������, � ������� ����� ������� �� i-�� �������
    std::map<T*, std::vector<T*>> collectionListsOut;

    // ������ ������
    std::vector<T*> vertices;
};



/*
����������
*/

template<typename T>
void CDirectGraph<T>::AddVertex( T* vertPtr ){

    assert( vertPtr != NULL );

    // ��������� ���������� �����������
    assert( HasVertex( vertPtr ) );

    vertices.push_back( vertPtr );

    // ������� ������ ������ ��� ����� �������
    collectionListsIn[vertPtr];
    collectionListsOut[vertPtr];
}

template<typename T>
void CDirectGraph<T>::AddEdge( T* from, T* to ){

    assert( from != NULL && to != NULL );

    // ������� ������ ������������
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

template<typename T>
std::vector<T*> CDirectGraph<T>::GetVertices(){
    return vertices;
}

template<typename T>
std::vector<Y*> CDirectGraph<T>::GetListOut( const T* vert ) {
    assert( HasVertex( vert ) );
    return collectionListsOut[vert];
}
