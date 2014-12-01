/*
* ��������� ������� ����� ������������ ���������������� ������
*/
#pragma once
#include "Visitor.h"

class CPrettyPrinter : public IVisitor
{
public:
	CPrettyPrinter(): marginInTabs(0) {};

	// �������� �������� ����� ��������
	void PrintTabs( size_t tabs ) const;
	// �������� ������ � ������������ � ������� ������� ��������
	void PrintMargin() const;
	// ����������� � ��������� ������
	void IncreaseMargin() { marginInTabs += 1; };
	void DecreaseMargin() { if ( marginInTabs > 0 ) marginInTabs -= 1; };
	void SetMargin( size_t value ) { marginInTabs = value; };


	void Visit( const CProgram* node );
	void Visit( const CMainClassDeclaration* node );
	void Visit( const CClassDeclaration* node );
	void Visit( const CClassExtendsDeclaration* node );
	void Visit( const CClassDeclarationList* node );
	void Visit( const CVariableDeclaration* node );
	void Visit( const CVariableDeclarationList* node );
	void Visit( const CMethodDeclaration* node );
	void Visit( const CMethodDeclarationList* node );
	void Visit( const CFormalList* node );
	void Visit( const CFormalRestList* node );
	void Visit( const CBuiltInType* node );
	void Visit( const CUserType* node );
	void Visit( const CStatementList* node );
	void Visit( const CStatementBlock* node );
	void Visit( const CIfStatement* node );
	void Visit( const CWhileStatement* node );
	void Visit( const CPrintStatement* node );
	void Visit( const CAssignmentStatement* node );
	void Visit( const CArrayElementAssignmentStatement* node );
	void Visit( const CBinaryOperatorExpression* node );
	void Visit( const CIndexAccessExpression* node );
	void Visit( const CLengthExpression* node );
	void Visit( const CMethodCallExpression* node );
	void Visit( const CIntegerOrBooleanExpression* node );
	void Visit( const CIdentifierExpression* node );
	void Visit( const CThisExpression* node );
	void Visit( const CNewIntegerArrayExpression* node );
	void Visit( const CNewObjectExpression* node );
	void Visit( const CNegationExpression* node );
	void Visit( const CParenthesesExpression* node );
	void Visit( const CExpressionList* node );

private:
	static std::string marginString; // ������, ������� ����� ���������� ��� ������
	size_t marginInTabs; // ����� ������� �������, �� ������� ����� ����������� ������
};

