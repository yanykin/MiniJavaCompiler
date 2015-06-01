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

    // �������� ������� ������ ������
    std::vector<T*> GetVertices() const;

    // ��������� ������ ������ � ������� ������ DFS
    void BuidDFSVertices();

    // �������� ������ ������ � ������� ������ DFS
    std::vector<T*> GetDFSVertices() const; 

    // �������� ������ ������, � ������� ����� �������
    std::vector<T*> GetListOut( T* vert);

private:

    // ������ ������, �� ������� ����� ������� � i-�� �������
    std::map<T*, std::vector<T*>> collectionListsIn;

    // ������ ������, � ������� ����� ������� �� i-�� �������
    std::map<T*, std::vector<T*>> collectionListsOut;

    // ������ ������
    std::vector<T*> vertices;

    // ������ ������ � ������� ������ DFS
    std::vector<T*> verticesDFS;

    // ��������� ������ � ������� � ���������
    std::unordered_set<const T*> visited;

    // ��� ��������� DFS
    void VisitDFS( T* vert );

    // ��������� �� DFS �������������
    bool isDFSVertices = false;
};



/*
����������
*/

template<typename T>
void CDirectGraph<T>::AddVertex( T* vertPtr ){

    assert( vertPtr != NULL );

    // ��������� ���������� �����������
    assert( !HasVertex( vertPtr ) );

    vertices.push_back( vertPtr );

    isDFSVertices = false;

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

    //������� ����� ��������� DFS �������������, �������� BuildDFSVertices
    assert( isDFSVertices );
    return verticesDFS;
}