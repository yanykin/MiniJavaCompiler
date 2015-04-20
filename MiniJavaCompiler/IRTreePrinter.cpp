#include "IRTreePrinter.h"

using namespace IRTree;

CIRTreePrinter::CIRTreePrinter(const std::string& outputFileName) : totalVisitedNodes(0), currentNodeID(0),
lastVisitedNodeID(0)
{
	graphvizOutputFile = std::ofstream( outputFileName );
}

CIRTreePrinter::~CIRTreePrinter() {
	graphvizOutputFile.close();
}


void CIRTreePrinter::Visit( const CONST* node ) {
	visitNewNode();

	nodeLabels[ currentNodeID ] = "CONST " + std::to_string( node->GetValue() );

	leaveNode();
}


void CIRTreePrinter::Visit( const NAME* node ) {
	visitNewNode();

	nodeLabels[ currentNodeID ] = "NAME " + node->GetLabel()->Name();

	leaveNode();
}


void CIRTreePrinter::Visit( const TEMP* node ) {
	visitNewNode();

	nodeLabels[ currentNodeID ] = "TEMP " + node->GetTemp()->Name();

	leaveNode();
}


void CIRTreePrinter::Visit( const BINOP* node ) {
	visitNewNode();

	

	// Создаём дополнительный узел
	// size_t tmpNode = createNewNode();
	std::string tmpNodeLabel;
	switch ( node->GetBinop() ) {
	case BO_PLUS:
		tmpNodeLabel = "PLUS (+)";
		break;
	case BO_MINUS:
		tmpNodeLabel = "MINUS (-)";
		break;
	case BO_MUL:
		tmpNodeLabel = "MUL (*)";
		break;
	case BO_DIV:
		tmpNodeLabel = "DIV (/)";
		break;
	default:
		tmpNodeLabel = "unknown binary operation";
	}
	nodeLabels[ currentNodeID ] = tmpNodeLabel;
	//nodeLabels[ tmpNode ] = tmpNodeLabel;
	// this->addEdge( currentNodeID, tmpNode );

	node->GetLeft()->Accept( this );
	node->GetRight()->Accept( this );

	leaveNode();
}


void CIRTreePrinter::Visit( const MEM* node ) {
	visitNewNode();

	nodeLabels[ currentNodeID ] = "MEM";
	node->GetExp()->Accept( this );

	leaveNode();
}


void CIRTreePrinter::Visit( const CALL* node ) {
	visitNewNode();

	nodeLabels[ currentNodeID ] = "CALL";
	node->GetFunc()->Accept( this );

	if ( node->GetArgs() ) {
		node->GetArgs()->Accept( this );
	}

	leaveNode();
}


void CIRTreePrinter::Visit( const ESEQ* node ) {
	visitNewNode();

	nodeLabels[ currentNodeID ] = "ESEQ";

	node->GetStm()->Accept( this );
	node->GetExp()->Accept( this );

	leaveNode();
}


void CIRTreePrinter::Visit( const MOVE* node ) {
	visitNewNode();

	nodeLabels[ currentNodeID ] = "MOVE";
	
	node->GetDst()->Accept( this );
	node->GetSrc()->Accept( this );

	leaveNode();
}


void CIRTreePrinter::Visit( const EXP* node ) {
	visitNewNode();

	nodeLabels[ currentNodeID ] = "EXP";

	node->GetExp()->Accept( this );

	leaveNode();
}


void CIRTreePrinter::Visit( const JUMP* node ) {
	visitNewNode();

	nodeLabels[ currentNodeID ] = "JUMP";

	leaveNode();
}


void CIRTreePrinter::Visit( const CJUMP* node ) {
	visitNewNode();

	nodeLabels[ currentNodeID ] = "CJUMP";

	size_t tmpNode = createNewNode();
	std::string tmpNodeLabel;
	switch ( node->GetRelop() )
	{
	case CJ_EQ:
		tmpNodeLabel = "==";
		break;
	case CJ_GE:
		tmpNodeLabel = ">=";
		break;
	case CJ_GT:
		tmpNodeLabel = ">";
		break;
	case CJ_LE:
		tmpNodeLabel = "<=";
		break;
	case CJ_LT:
		tmpNodeLabel = "<";
		break;
	case CJ_NE:
		tmpNodeLabel = "!=";
		break;
	default:
		tmpNodeLabel = "unknown binary operation";
		break;
	}
	nodeLabels[ tmpNode ] = tmpNodeLabel;
	this->addEdge( currentNodeID, tmpNode );

	node->GetLeft()->Accept( this );
	node->GetRight()->Accept( this );
	
	tmpNode = createNewNode();
	nodeLabels[ tmpNode ] = "LABEL " + node->GetIfTrue()->Name();
	this->addEdge( currentNodeID, tmpNode );

	tmpNode = createNewNode();
	nodeLabels[ tmpNode ] = "LABEL " + node->GetIfFalse()->Name();
	this->addEdge( currentNodeID, tmpNode );

	leaveNode();
}


void CIRTreePrinter::Visit( const SEQ* node ) {
	visitNewNode();

	nodeLabels[ currentNodeID ] = "SEQ";

	if ( node->GetLeft() ) {
		node->GetLeft()->Accept( this );
	}
	
	if ( node->GetRight() ) {
		node->GetRight()->Accept( this );
	}

	leaveNode();
}


void CIRTreePrinter::Visit( const LABEL* node ) {
	visitNewNode();

	nodeLabels[ currentNodeID ] = "LABEL " + node->GetLabel()->Name();

	leaveNode();
}

void CIRTreePrinter::Visit( const CExpList* node ) {
	// visitNewNode();

	const IExp* nextExp = node->GetHead();
	const CExpList* tail = node->GetTail();
	
	if ( nextExp ) {
		nextExp->Accept( this );
	}
	
	if ( tail ) {
		tail->Accept( this );
	}	

	// leaveNode();
}


void CIRTreePrinter::Visit( const CStmList* node ) {

	// visitNewNode();

	const IStm* nextExp = node->GetHead();
	const CStmList* tail = node->GetTail();
	
	if ( nextExp ) {
		nextExp->Accept( this );
	}

	if ( tail ) {
		tail->Accept( this );
	}

	// leaveNode();
}

