#pragma once
#include "Table.h"
#include <assert.h>

namespace CSymbolsTable {
	
	/* === CTable === */
	bool CTable::AddClass( CClassInformation* classInfo ) {
		assert( classInfo );
		Symbol::CSymbol* className = Symbol::CSymbol::GetSymbol( classInfo->GetName() );
		// ѕровер€ем наличие уже существующего класса
		if (!declaredClasses.GetObject(className)) {
			return false;
		}
		declaredClasses.InsertObject( className, classInfo );
		return true;
	}

	CClassInformation* CTable::GetClassByName(const std::string& className ) {
		return declaredClasses.GetObject( Symbol::CSymbol::GetSymbol( className ) );
	}

	/* === CClassInformation === */
	bool CClassInformation::AddField( CVariableInformation* varInfo ) {
		assert( varInfo );
		Symbol::CSymbol* fieldName = Symbol::CSymbol::GetSymbol( varInfo->GetName() );
		if ( !fields.GetObject( fieldName )) {
			return false;
		}
		fields.InsertObject( fieldName, varInfo );
		return true;
	}

	bool CClassInformation::AddMethod( CMethodInformation *methodInfo ){
		assert( methodInfo );
		Symbol::CSymbol* methodName = Symbol::CSymbol::GetSymbol( methodInfo->GetName() );
		if ( !methods.GetObject( methodName ) ) {
			return false;
		}
		methods.InsertObject( methodName, methodInfo );
		return true;
	}

	CMethodInformation* CClassInformation::GetMethodByName( std::string& methodName ) {
		return methods.GetObject( Symbol::CSymbol::GetSymbol( methodName ) );
	}

	Symbol::CSymbol* CClassInformation::GetFieldType( std::string& fieldName ) {
		CVariableInformation* field = fields.GetObject( Symbol::CSymbol::GetSymbol( fieldName ) );
		return field ? field->GetType() : NULL;
	}

	/* === CMethodInformation === */
	bool CMethodInformation::AddParameter( CVariableInformation* varInfo ){
		assert( varInfo );
		Symbol::CSymbol* parameterName = Symbol::CSymbol::GetSymbol( varInfo->GetName() );
		if ( !methodParameters.GetObject( parameterName ) ) {
			return false;
		}
		methodParameters.InsertObject( parameterName, varInfo );
		return true;
	}

	bool CMethodInformation::AddLocalVariable( CVariableInformation* varInfo )
	{
		assert( varInfo );
		Symbol::CSymbol* variableName = Symbol::CSymbol::GetSymbol( varInfo->GetName() );
		if ( !localVariables.GetObject( variableName ) ) {
			return false;
		}
		localVariables.InsertObject( variableName, varInfo );
		return true;
	}
	
	Symbol::CSymbol* CMethodInformation::GetArgumentType( const std::string& argumentName ) {
		CVariableInformation *method = methodParameters.GetObject( Symbol::CSymbol::GetSymbol( argumentName ) );
		return method ? method->GetType() : NULL;
	}

	Symbol::CSymbol* CMethodInformation::GetLocalVariableType( const std::string& variableName ) {
		CVariableInformation *variable = localVariables.GetObject( Symbol::CSymbol::GetSymbol( variableName ) );
		return variable ? variable->GetType() : NULL;
	}
}