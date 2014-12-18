/*
* ??????????????? ?????, ??????? ????? ??????? ?????????? ?????? - ???? ??????????????? ??????
*/

#pragma once
struct YYLTYPE;

class CCoordinatesHolder
{
public:	
	CCoordinatesHolder( const YYLTYPE& yylloc );

	int GetColumn() const { return column; }
	int GetRow() const { return row; }
private:
	int row;
	int column;
};

