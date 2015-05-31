// Author: Nikolay Levshin
// ���������� ������������� �����

#pragma once

#include <map>
#include <vector>


template<typename T>
class CDirectGraph {
public:
    // ��������� ����� �������
    void AddVertex( T* vertPtr);

    // ��������� ����� �����
    void AddEdge( const T& from, const T& to );
    void AddEdge( T* from, T* to );

    //  �������� �� ������� ��������� � �����
    bool HasVertex( const T& val );
    bool HasEdge( const T& from, const T& to );

private:

    // ������ ������, �� ������� ����� ������� � i-�� �������
    std::map<T*, std::vector<T*>> collectionListsIn;

    // ������ ������, � ������� ����� ������� �� i-�� �������
    std::map<T*, std::vector<T*>> collectionListsOut;

    // ������ ������
    vector<T*> vertices;
};