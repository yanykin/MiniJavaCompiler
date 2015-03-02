#include "IRTreePrinter.h"

using namespace IRTree;

CIRTreePrinter::CIRTreePrinter(const std::string& outputFileName) : totalVisitedNodes(0), currentNodeID(0)
{
	graphvizOutputFile = std::ofstream( outputFileName );
}

CIRTreePrinter::~CIRTreePrinter() {
	graphvizOutputFile.close();
}


void CIRTreePrinter::Visit( const CONST* node ) {
	totalVisitedNodes += 1;
	currentNodeID = totalVisitedNodes;

	this->addEdge( nodeStack.top(), currentNodeID );

	nodeLabels[ currentNodeID ] = "CONST " + std::to_string( node->GetValue() );
}


void CIRTreePrinter::Visit( const NAME* node ) {	
	nodeLabels[ currentNodeID ] = "NAME " + node->GetLabel()->Name();
}


void CIRTreePrinter::Visit( const TEMP* node ) {
	nodeLabels[ currentNodeID ] = "TEMP " + node->GetTemp()->Name();
}


void CIRTreePrinter::Visit( const BINOP* node ) {
	nodeLabels[ currentNodeID ] = "BINOP";

	nodeStack.push( currentNodeID );
	node->GetLeft()->Accept( this );
	currentNodeID = nodeStack.top();
	nodeStack.pop();


	nodeStack.push( currentNodeID );
	node->GetRight()->Accept( this );
	currentNodeID = nodeStack.top();
	nodeStack.pop();
}


void CIRTreePrinter::Visit( const MEM* node ) {
}


void CIRTreePrinter::Visit( const CALL* node ) {
}


void CIRTreePrinter::Visit( const ESEQ* node ) {
}


void CIRTreePrinter::Visit( const MOVE* node ) {
}


void CIRTreePrinter::Visit( const EXP* node ) {
}


void CIRTreePrinter::Visit( const JUMP* node ) {
}


void CIRTreePrinter::Visit( const CJUMP* node ) {
}


void CIRTreePrinter::Visit( const SEQ* node ) {
}


void CIRTreePrinter::Visit( const LABEL* node ) {
}
