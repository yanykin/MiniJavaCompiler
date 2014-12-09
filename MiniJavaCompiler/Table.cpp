#pragma once
#include "Table.h"
#include <assert.h>

namespace CSymbolsTable {
	bool CTable::AddClass( CClassInformation* classInfo ) {
		assert( classInfo );
		// ѕровер€ем наличие уже существующего класса
		for ( auto it = declaredClasses.begin(); it != declaredClasses.end(); it++ ) {
			if ( ( *it )->GetName() == classInfo->GetName() ) {
				return false;
			}
		}
		declaredClasses.push_back( classInfo );
		return true;
	}

	bool CClassInformation::AddField( CVariableInformation* varInfo ) {
		assert( varInfo );
		for ( auto it = fields.begin(); it != fields.end(); it++ ) {
			if ( ( *it )->GetName() == varInfo->GetName() ) {
				return false;
			}
		}
		fields.push_back( varInfo );
		return true;
	}

	bool CClassInformation::AddMethod( CMethodInformation *methodInfo ){
		assert( methodInfo );
		for ( auto it = methods.begin(); it != methods.end(); it++ ) {
			if ( ( *it )->GetName() == methodInfo->GetName() ) {
				return false;
			}
		}
		methods.push_back( methodInfo );
		return true;
	}

	bool CMethodInformation::AddParameter( CVariableInformation* varInfo ){
		assert( varInfo );
		for ( auto it = methodParameters.begin(); it != methodParameters.end(); it++ ) {
			if ( ( *it )->GetName() == varInfo->GetName() ) {
				return false;
			}
		}
		methodParameters.push_back( varInfo );
		return true;
	}

	bool CMethodInformation::AddLocalVariable( CVariableInformation* varInfo )
	{
		assert( varInfo );
		for ( auto it = localVariables.begin(); it != localVariables.end(); it++ ) {
			if ( ( *it )->GetName() == varInfo->GetName() ) {
				return false;
			}
		}
		localVariables.push_back( varInfo );
		return true;
	}
}