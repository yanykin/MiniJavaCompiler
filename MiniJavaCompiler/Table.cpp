#pragma once
#include "Table.h"
#include <assert.h>

namespace CSymbolsTable {
	
	/* === CTable === */
	bool CTable::AddClass( CClassInformation* classInfo ) {
		assert( classInfo );
		std::string className = classInfo->GetName();
		// ѕровер€ем наличие уже существующего класса
		if (declaredClasses.find(className) != declaredClasses.end()) {
			return false;
		}
		declaredClasses[ className ] = classInfo;
		return true;
	}

	CClassInformation* CTable::GetClassByName( std::string& className ) {
		auto result = declaredClasses.find( className );
		if ( result == declaredClasses.end() ) {
			return NULL;
		}
		else {
			return result->second;
		}
	}

	/* === CClassInformation === */
	bool CClassInformation::AddField( CVariableInformation* varInfo ) {
		assert( varInfo );
		std::string fieldName = varInfo->GetName();
		if ( fields.find( fieldName ) != fields.end() ) {
			return false;
		}
		fields[ fieldName ] = varInfo;
		return true;
	}

	bool CClassInformation::AddMethod( CMethodInformation *methodInfo ){
		assert( methodInfo );
		std::string methodName = methodInfo->GetName();
		if ( methods.find( methodName ) != methods.end()) {
			return false;
		}
		methods[ methodName ] = methodInfo;
		return true;
	}

	CMethodInformation* CClassInformation::GetMethodByName( std::string& methodName ) {
		auto result = methods.find( methodName );
		if ( result == methods.end() ) {
			return NULL;
		}
		else {
			return result->second;
		}
	}

	CType* CClassInformation::GetFieldType( std::string& fieldName ) {
		auto result = fields.find( fieldName );
		if ( result == fields.end() ) {
			return NULL;
		}
		else {
			return result->second->GetType();
		}
	}

	/* === CMethodInformation === */
	bool CMethodInformation::AddParameter( CVariableInformation* varInfo ){
		assert( varInfo );
		std::string argumentName = varInfo->GetName();
		if ( methodParameters.find( argumentName ) != methodParameters.end() ) {
			return false;
		}
		methodParameters[ argumentName] =  varInfo;
		return true;
	}

	bool CMethodInformation::AddLocalVariable( CVariableInformation* varInfo )
	{
		assert( varInfo );
		std::string variableName = varInfo->GetName();
		if ( localVariables.find( variableName ) != localVariables.end() ) {
			return false;
		}
		localVariables[ variableName ] = varInfo;
		return true;
	}
	
	CType* CMethodInformation::GetArgumentType( std::string& argumentName ) {
		auto result = methodParameters.find( argumentName );
		if ( result == methodParameters.end() ) {
			return NULL;
		}
		else {
			return result->second->GetType();
		}
	}

	CType* CMethodInformation::GetLocalVariableType( std::string& argumentName ) {
		auto result = localVariables.find( argumentName );
		if ( result == localVariables.end() ) {
			return NULL;
		}
		else {
			return result->second->GetType();
		}
	}
}