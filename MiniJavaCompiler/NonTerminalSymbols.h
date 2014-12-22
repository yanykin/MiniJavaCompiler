/*
* ???????????? ?????????????? ???????? ?????????? ? ?? ??????????????? ???????
*/
#pragma once

class CProgram;
class CMainClassDeclaration;
class CClassDeclaration;
class CClassDeclarationList;
class CClassExtendsDeclaration;
class CVariableDeclaration;
class CVariableDeclarationList;
class CMethodDeclaration;
class CMethodDeclarationList;
class CFormalList;
class CFormalRestList;
class CBuiltInType;
class CUserType;
class CStatementList;
class CStatementBlock;
class CIfStatement;
class CWhileStatement;
class CPrintStatement;
class CAssignmentStatement;
class CArrayElementAssignmentStatement;
class CBinaryOperatorExpression;
class CIndexAccessExpression;
class CLengthExpression;
class CMethodCallExpression;
class CIntegerOrBooleanExpression;
class CIdentifierExpression;
class CThisExpression;
class CNewIntegerArrayExpression;
class CNewObjectExpression;
class CNegationExpression;
class CParenthesesExpression;
class CExpressionList;

namespace IRTree
{
	class CONST;
	class BINOP;
	class CALL;
	class CJUMP;
	class ESEQ;
	class EXP;
	class JUMP;
	class LABEL;
	class MEM;
	class MOVE;
	class NAME;
	class SEQ;
	class TEMP;
}