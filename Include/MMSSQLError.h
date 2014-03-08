#pragma once

#include <Windows.h>
#include <stdio.h>
#include <crtdbg.h>

#include <sql.h>
#include <sqlext.h>
#include <sqlucode.h>
#include <sqltypes.h>

/**
 * Returns the error (if any) from the handle. Unicode version.
 * @param hHandleType The type of handle point to in the hHandle parameter.
 * @param hHandle The handle to check for (if any) errors for.
 * @param nNativeIDOut Assigns the SQL Error ID.
 * @param pszwErrorMsgOut Sets the description of the param to this wchar_t array.
 * @param nMsgMaxLength (Usually) size of the pszwErrorMsgOut array.
 * @return True if successful. Else, false.
 */
bool GetLastMSSQLErrorW( SQLSMALLINT hHandleType, SQLHANDLE hHandle,
	int* nNativeIDOut, wchar_t* pszwErrorMsgOut, int nMsgMaxLength );

/**
 * Returns the error (if any) from the handle. ANSI version.
 * @param hHandleType The type of handle point to in the hHandle parameter.
 * @param hHandle The handle to check for (if any) errors for.
 * @param nNativeIDOut Assigns the SQL Error ID.
 * @param pszErrorMsgOut Sets the description of the param to this char_ array.
 * @param nMsgMaxLength (Usually) size of the pszErrorMsgOut array.
 * @return True if successful. Else, false.
 */
bool GetLastMSSQLErrorA( SQLSMALLINT hHandleType, SQLHANDLE hHandle,
	int* nNativeIDOut, char* pszErrorMsgOut, int nMsgMaxLength );

#ifdef UNICODE
/**
 * Global connection function. If the configuration is Unicode, then
 * this function will point to 'GetLastSQLErrorW'. Else, if the configuration is
 * ANSI, this function will point to 'GetLastSQLErrorA'.
 * See GetLastSQLErrorW and GetLastSQLErrorA
 *
 * @param hHandleType The type of handle point to in the hHandle parameter.
 * @param hHandle The handle to check for (if any) errors for.
 * @param nNativeIDOut Assigns the SQL Error ID.
 * @param pszwErrorMsgOut Sets the description of the param to this wchar_t array.
 * @param nMsgMaxLength (Usually) size of the pszwErrorMsgOut array.
 * @return True if successful. Else, false.
 */
bool GetLastMSSQLError( SQLSMALLINT hHandleType, SQLHANDLE hHandle,
	int* nNativeIDOut, wchar_t* pszwErrorMsgOut, int nMsgMaxLength );
#else
/**
 * Global connection function. If the configuration is Unicode, then
 * this function will point to 'GetLastSQLErrorW'. Else, if the configuration is
 * ANSI, this function will point to 'GetLastSQLErrorA'.
 * See GetLastSQLErrorW and GetLastSQLErrorA
 *
 * @param hHandleType The type of handle point to in the hHandle parameter.
 * @param hHandle The handle to check for (if any) errors for.
 * @param nNativeIDOut Assigns the SQL Error ID.
 * @param pszErrorMsgOut Sets the description of the param to this char array.
 * @param nMsgMaxLength (Usually) size of the pszwErrorMsgOut array.
 * @return True if successful. Else, false.
 */
bool GetLastMSSQLError( SQLSMALLINT hHandleType, SQLHANDLE hHandle,
	int* nNativeIDOut, char* pszErrorMsgOut, int nMsgMaxLength );
#endif

#ifdef UNICODE
#define _MSSQL_CHECK_HANDLE_SIMPLE( handletype, handle, returntype )			\
{																				\
	if( (returntype) != SQL_SUCCESS || (returntype) != SQL_SUCCESS_WITH_INFO )	\
	{																			\
		int nSQLNativeID = 0;													\
		wchar_t szwSQLErrorMsg[1024] = { 0 };									\
																				\
		if( GetLastMSSQLErrorW( (handletype), (handle), &nSQLNativeID,			\
			szwSQLErrorMsg, 1024 ) )											\
		{																		\
			OutputDebugStringW( L"[SQL ERROR - " );								\
			OutputDebugStringW( szwSQLErrorMsg );								\
			_ASSERT( false );													\
			return (returntype);												\
		}																		\
	}																			\
}
#else
#define _MSSQL_CHECK_HANDLE_SIMPLE( handletype, handle, returntype )			\
{																				\
	if( (returntype) != SQL_SUCCESS || (returntype) != SQL_SUCCESS_WITH_INFO )	\
	{																			\
		int nSQLNativeID = 0;													\
		char szSQLErrorMsg[1024] = { 0 };										\
																				\
		if( GetLastMSSQLErrorA( (handletype), (handle), &nSQLNativeID,			\
			szSQLErrorMsg, 1024 ) )												\
		{																		\
			OutputDebugStringA( "[SQL ERROR - " );								\
			OutputDebugStringA( szSQLErrorMsg );								\
			_ASSERT( false );													\
			return (returntype);												\
		}																		\
	}																			\
}
#endif

#ifdef UNICODE
#define _MSSQL_CHECK_HANDLE( handletype, handle, sqlreturn, returntype )		\
	if( (sqlreturn) != SQL_SUCCESS )										\
	{																		\
		int nSQLNativeID = 0;												\
		wchar_t szwSQLErrorMsg[1024] = { 0 };								\
																			\
		if( GetLastMSSQLErrorW( (handletype), (handle), &nSQLNativeID,		\
			szwSQLErrorMsg, 1024 ) )										\
		{																	\
			if( (sqlreturn) == SQL_SUCCESS_WITH_INFO )						\
			{																\
				OutputDebugStringW( L"[SQL Warning] - " );					\
				OutputDebugStringW( szwSQLErrorMsg );						\
			}																\
			else															\
			{																\
				OutputDebugStringW( L"[SQL ERROR] - " );					\
				OutputDebugStringW( szwSQLErrorMsg );						\
				_ASSERT( false );											\
				return (returntype);										\
			}																\
		}																	\
	}
#else
#define _MSSQL_CHECK_HANDLE( handletype, handle, sqlreturn, returntype )		\
	if( (sqlreturn) != SQL_SUCCESS )										\
	{																		\
		int nSQLNativeID = 0;												\
		char szSQLErrorMsg[1024] = { 0 };									\
																			\
		if( GetLastMSSQLErrorA( (handletype), (handle), &nSQLNativeID,		\
			szSQLErrorMsg, 1024 ) )											\
		{																	\
			if( (sqlreturn) == SQL_SUCCESS_WITH_INFO )						\
			{																\
				OutputDebugStringA( "[SQL Warning] - " );					\
				OutputDebugStringA( szSQLErrorMsg );						\
			}																\
			else															\
			{																\
				OutputDebugStringA( "[SQL ERROR] - " );						\
				OutputDebugStringA( szSQLErrorMsg );						\
				_ASSERT( false );											\
				return (returntype);										\
			}																\
		}																	\
	}
#endif