#include "MiniJavaCompiler.h"

int main(int argc, char* argv[])
{
	if ( argc != 3 ) {
		std::cout << "Usage: " << argv[ 0 ] << " SOURCE_FILE_NAME ASM_OUTPUT_FILE_NAME" << std::endl;
		exit( 1 );
	}

	MiniJavaCompiler::CMiniJavaCompiler compiler;
	std::string sourceFileName = argv[ 1 ];
	std::string asmOutputFileName = argv[ 2 ];

	MiniJavaCompiler::TErrorCode errorCode = compiler.Compile( sourceFileName, asmOutputFileName );
	if ( errorCode == MiniJavaCompiler::EC_NoError ) {
		std::cout << "Success" << std::endl;
	}
	else {
		std::cout
			<< "Error code: "
			<< errorCode
			<< " (" << MiniJavaCompiler::CMiniJavaCompiler::GetCodeDescription( errorCode ) << ")"
			<< std::endl;
	}
	return 0;
}