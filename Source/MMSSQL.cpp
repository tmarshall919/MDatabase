/** READ!
 * This is in no way complete, nor safe to use.. Yet.
 ** (E.G; Unicode incomplete, crashes / memory leaks, so on so forth.. Just
 *** think of this as revision 0.001 :)
 * It has not been fully tested, and some functions are not yet complete.
**/

#include "MMSSQL.h"

MMSSQL::MMSSQL()
{
	m_hEnvironment = m_hConnection = m_hStatement = NULL;
	m_bIsConnected = false;
	m_nFieldsCount = 0;
}

MMSSQL::~MMSSQL()
{
}

bool MMSSQL::ConnectW( const wchar_t* pszwHost, const wchar_t* pszwDatabase,
		const wchar_t* pszwUsername, const wchar_t* pszwPassword )
{
	SQLRETURN hRet = SQL_SUCCESS;

	hRet = SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnvironment );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_ENV, m_hEnvironment, hRet, false );

	hRet = SQLSetEnvAttr( m_hEnvironment, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, NULL );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_ENV, m_hEnvironment, hRet, false );

	hRet = SQLAllocHandle( SQL_HANDLE_DBC, m_hEnvironment, &m_hConnection );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_DBC, m_hConnection, hRet, false );

	hRet = SQLConnectW( m_hConnection, (SQLWCHAR*)pszwDatabase, SQL_NTS,
		(SQLWCHAR*)pszwUsername, SQL_NTS, (SQLWCHAR*)pszwPassword, SQL_NTS );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_DBC, m_hConnection, hRet, false );

	m_bIsConnected = true;

	return true;
}

bool MMSSQL::ConnectA( const char* pszHost, const char* pszDatabase,
		const char* pszUsername, const char* pszPassword )
{
	SQLRETURN hRet = SQL_SUCCESS;

	hRet = SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnvironment );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_ENV, m_hEnvironment, hRet, false );

	hRet = SQLSetEnvAttr( m_hEnvironment, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, NULL );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_ENV, m_hEnvironment, hRet, false );

	hRet = SQLAllocHandle( SQL_HANDLE_DBC, m_hEnvironment, &m_hConnection );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_DBC, m_hConnection, hRet, false );

	hRet = SQLConnectA( m_hConnection, (SQLCHAR*)pszDatabase, SQL_NTS,
		(SQLCHAR*)pszUsername, SQL_NTS, (SQLCHAR*)pszPassword, SQL_NTS );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_DBC, m_hConnection, hRet, false );

	m_bIsConnected = true;

	return true;
}

#ifdef UNICODE

bool MMSSQL::Connect( const wchar_t* pszwHost, const wchar_t* pszwDatabase,
		const wchar_t* pszwUsername, const wchar_t* pszwPassword )
{
	SQLRETURN hRet = SQL_SUCCESS;

	hRet = SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnvironment );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_ENV, m_hEnvironment, hRet, false );

	hRet = SQLSetEnvAttr( m_hEnvironment, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, NULL );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_ENV, m_hEnvironment, hRet, false );

	hRet = SQLAllocHandle( SQL_HANDLE_DBC, m_hEnvironment, &m_hConnection );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_DBC, m_hConnection, hRet, false );

	hRet = SQLConnectW( m_hConnection, (SQLWCHAR*)pszwDatabase, SQL_NTS,
		(SQLWCHAR*)pszwUsername, SQL_NTS, (SQLWCHAR*)pszwPassword, SQL_NTS );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_DBC, m_hConnection, hRet, false );

	m_bIsConnected = true;

	return true;
}

#else

bool MMSSQL::Connect( const char* pszHost, const char* pszDatabase,
		const char* pszUsername, const char* pszPassword )
{
	SQLRETURN hRet = SQL_SUCCESS;

	hRet = SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnvironment );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_ENV, m_hEnvironment, hRet, false );

	hRet = SQLSetEnvAttr( m_hEnvironment, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, NULL );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_ENV, m_hEnvironment, hRet, false );

	hRet = SQLAllocHandle( SQL_HANDLE_DBC, m_hEnvironment, &m_hConnection );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_DBC, m_hConnection, hRet, false );

	hRet = SQLConnectA( m_hConnection, (SQLCHAR*)pszDatabase, SQL_NTS,
		(SQLCHAR*)pszUsername, SQL_NTS, (SQLCHAR*)pszPassword, SQL_NTS );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_DBC, m_hConnection, hRet, false );

	m_bIsConnected = true;

	return true;
}

#endif



void MMSSQL::Disconnect()
{
	//TODO : If still executing, wait.
	SQLFreeHandle( SQL_HANDLE_STMT, m_hStatement );

	SQLDisconnect( m_hConnection );

	SQLFreeHandle( SQL_HANDLE_DBC, m_hConnection );
	SQLFreeHandle( SQL_HANDLE_ENV, m_hEnvironment );

	m_bIsConnected = false;
}

bool MMSSQL::ExecuteQueryW( const wchar_t* pszwQuery )
{
	if( !m_bIsConnected )
		return false;

	if( m_hStatement != NULL )
	{
		//TODO : Make sure we're not executing anything.
	}

	SQLRETURN hRet = SQLAllocHandle( SQL_HANDLE_STMT, m_hConnection, &m_hStatement );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_STMT, m_hStatement, hRet, false );

	hRet = SQLExecDirectW( m_hStatement, (SQLWCHAR*)pszwQuery, SQL_NTS );
	if( hRet == SQL_SUCCESS || hRet == SQL_SUCCESS_WITH_INFO )
	{
		if( GetFieldsInfo() )
			return true;
	}

	_MSSQL_CHECK_HANDLE( SQL_HANDLE_STMT, m_hStatement, hRet, false );
	return false;
}

bool MMSSQL::ExecuteQueryA( const char* pszQuery )
{
	if( !m_bIsConnected )
		return false;

	if( m_hStatement != NULL )
	{
		//TODO : Make sure we're not executing anything.
	}

	SQLRETURN hRet = SQLAllocHandle( SQL_HANDLE_STMT, m_hConnection, &m_hStatement );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_STMT, m_hStatement, hRet, false );

	hRet = SQLExecDirectA( m_hStatement, (SQLCHAR*)pszQuery, SQL_NTS );
	if( hRet == SQL_SUCCESS || hRet == SQL_SUCCESS_WITH_INFO )
	{
		if( GetFieldsInfo() )
			return true;
	}

	_MSSQL_CHECK_HANDLE( SQL_HANDLE_STMT, m_hStatement, hRet, false );
	return false;
}

#ifdef UNICODE

bool MMSSQL::ExecuteQuery( const wchar_t* pszwQuery )
{
	if( !m_bIsConnected )
		return false;

	if( m_hStatement != NULL )
	{
		//TODO : Make sure we're not executing anything.
	}

	SQLRETURN hRet = SQLAllocHandle( SQL_HANDLE_STMT, m_hConnection, &m_hStatement );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_STMT, m_hStatement, hRet, false );

	hRet = SQLExecDirectW( m_hStatement, (SQLWCHAR*)pszwQuery, SQL_NTS );
	if( hRet == SQL_SUCCESS || hRet == SQL_SUCCESS_WITH_INFO )
	{
		if( GetFieldsInfo() )
			return true;
	}

	_MSSQL_CHECK_HANDLE( SQL_HANDLE_STMT, m_hStatement, hRet, false );
	return false;
}

#else

bool MMSSQL::ExecuteQuery( const char* pszQuery )
{
	if( !m_bIsConnected )
		return false;

	if( m_hStatement != NULL )
	{
		//TODO : Make sure we're not executing anything.
	}

	SQLRETURN hRet = SQLAllocHandle( SQL_HANDLE_STMT, m_hConnection, &m_hStatement );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_STMT, m_hStatement, hRet, false );

	hRet = SQLExecDirectA( m_hStatement, (SQLCHAR*)pszQuery, SQL_NTS );
	if( hRet == SQL_SUCCESS || hRet == SQL_SUCCESS_WITH_INFO )
	{
		if( GetFieldsInfo() )
			return true;
	}

	_MSSQL_CHECK_HANDLE( SQL_HANDLE_STMT, m_hStatement, hRet, false );
	return false;
}

#endif

bool MMSSQL::GetFieldsInfo()
{
	SQLRETURN hRet = SQL_SUCCESS;

	if( m_pFields != NULL )
	{
		delete[] m_pFields;
		m_pFields = NULL;
	}
	
	hRet = SQLNumResultCols( m_hStatement, (SQLSMALLINT*)&m_nFieldsCount );
	_MSSQL_CHECK_HANDLE( SQL_HANDLE_STMT, m_hStatement, hRet, false );

	m_pFields = new MDBField[m_nFieldsCount];

	for( int i = 0; i < m_nFieldsCount; i++ )
	{
		SQLSMALLINT nColumnNameLength = 0;
		SQLSMALLINT nColumnType = 0;
		SQLUINTEGER nColumnSize = 0;
		SQLSMALLINT nNumOfDecimals = 0;
		SQLSMALLINT nAllowsNulls = 0;

#ifdef UNICODE
		wchar_t szwColumnName[64] = { 0 };

		hRet = SQLDescribeColW( m_hStatement, (SQLUSMALLINT)i + 1, (SQLWCHAR*)szwColumnName,
			(SQLSMALLINT)64, &nColumnNameLength, &nColumnType, &nColumnSize, &nNumOfDecimals,
			&nAllowsNulls );
#else
		char szColumnName[64] = { 0 };

		hRet = SQLDescribeColA( m_hStatement, (SQLUSMALLINT)i + 1, (SQLCHAR*)szColumnName,
			(SQLSMALLINT)64, &nColumnNameLength, &nColumnType, &nColumnSize, &nNumOfDecimals,
			&nAllowsNulls );
#endif

		if( hRet == SQL_SUCCESS || hRet == SQL_SUCCESS_WITH_INFO )
		{
			switch( nColumnType )
			{
				case SQL_TINYINT: //Unsigned Char
				{
					hRet = SQLFetch( m_hStatement );
					if( hRet == SQL_SUCCESS || hRet == SQL_SUCCESS_WITH_INFO )
					{
						unsigned char nVal = 0;
						hRet = SQLGetData( m_hStatement, (SQLUSMALLINT)i + 1,
							SQL_C_UTINYINT, (SQLPOINTER)&nVal, sizeof(unsigned char),
							NULL );

#ifdef UNICODE
						m_pFields[i] = MDBField( (unsigned char)nVal, szwColumnName );
#else
						m_pFields[i] = MDBField( (unsigned char)nVal, szColumnName );
#endif
					}
					else if( hRet == SQL_NO_DATA )
						break;
					break;
				}

				case SQL_SMALLINT:			//Unsigned Short
				{
					hRet = SQLFetch( m_hStatement );
					if( hRet == SQL_SUCCESS || hRet == SQL_SUCCESS_WITH_INFO )
					{
						unsigned short nVal = 0;
						hRet = SQLGetData( m_hStatement, (SQLUSMALLINT)i + 1,
							SQL_C_USHORT, (SQLPOINTER)&nVal, sizeof(unsigned short),
							NULL );

#ifdef UNICODE
						m_pFields[i] = MDBField( (unsigned short)nVal, szwColumnName );
#else
						m_pFields[i] = MDBField( (unsigned short)nVal, szColumnName );
#endif
					}
					else if( hRet == SQL_NO_DATA )
						break;
					break;
				}

				case SQL_BIGINT:			//Unigned Long
				case SQL_INTEGER:
				{
					hRet = SQLFetch( m_hStatement );
					if( hRet == SQL_SUCCESS || hRet == SQL_SUCCESS_WITH_INFO )
					{
						unsigned long nVal = 0;
						hRet = SQLGetData( m_hStatement, (SQLUSMALLINT)i + 1,
							SQL_C_ULONG, (SQLPOINTER)&nVal, sizeof(unsigned long),
							NULL );

#ifdef UNICODE
						m_pFields[i] = MDBField( (unsigned long)nVal, szwColumnName );
#else
						m_pFields[i] = MDBField( (unsigned long)nVal, szColumnName );
#endif
					}
					else if( hRet == SQL_NO_DATA )
						break;
					break;
				}

				case SQL_FLOAT:			//Float
				{
					hRet = SQLFetch( m_hStatement );
					if( hRet == SQL_SUCCESS || hRet == SQL_SUCCESS_WITH_INFO )
					{
						float fVal = 0;
						hRet = SQLGetData( m_hStatement, (SQLUSMALLINT)i + 1,
							SQL_C_FLOAT, (SQLPOINTER)&fVal, sizeof(float),
							NULL );

#ifdef UNICODE
						m_pFields[i] = MDBField( (float)fVal, szwColumnName );
#else
						m_pFields[i] = MDBField( (float)fVal, szColumnName );
#endif
					}
					else if( hRet == SQL_NO_DATA )
						break;
					break;
				}

				case SQL_DOUBLE:			//Double
				{
					hRet = SQLFetch( m_hStatement );
					if( hRet == SQL_SUCCESS || hRet == SQL_SUCCESS_WITH_INFO )
					{
						double fVal = 0;
						hRet = SQLGetData( m_hStatement, (SQLUSMALLINT)i + 1,
							SQL_C_DOUBLE, (SQLPOINTER)&fVal, sizeof(double),
							NULL );

#ifdef UNICODE
						m_pFields[i] = MDBField( (double)fVal, szwColumnName );
#else
						m_pFields[i] = MDBField( (double)fVal, szColumnName );
#endif
					}
					else if( hRet == SQL_NO_DATA )
						break;
					break;
				}

				case SQL_TYPE_DATE:		//Date
				{
					hRet = SQLFetch( m_hStatement );
					if( hRet == SQL_SUCCESS || hRet == SQL_SUCCESS_WITH_INFO )
					{
						DATE_STRUCT date;
						ZeroMemory( &date, sizeof(DATE_STRUCT) );

						hRet = SQLGetData( m_hStatement, (SQLUSMALLINT)i + 1,
							SQL_C_TYPE_DATE, (SQLPOINTER)&date, sizeof(DATE_STRUCT),
							NULL );

						TIMESTAMP_STRUCT stamp;
						ZeroMemory( &stamp, sizeof(TIMESTAMP_STRUCT) );
						stamp.year = date.year;
						stamp.month = date.month;
						stamp.day = date.day;

#ifdef UNICODE
//						m_pFields[i] = MDBField( stamp, szwColumnName );
#else
						m_pFields[i] = MDBField( stamp, szColumnName );
#endif
					}
					else if( hRet == SQL_NO_DATA )
						break;
					break;
				}
				case SQL_TYPE_TIME:		//Time
				{
					hRet = SQLFetch( m_hStatement );
					if( hRet == SQL_SUCCESS || hRet == SQL_SUCCESS_WITH_INFO )
					{
						TIME_STRUCT time;
						ZeroMemory( &time, sizeof(TIME_STRUCT) );

						hRet = SQLGetData( m_hStatement, (SQLUSMALLINT)i + 1,
							SQL_C_TYPE_TIME, (SQLPOINTER)&time, sizeof(DATE_STRUCT),
							NULL );

					TIMESTAMP_STRUCT stamp;
					ZeroMemory( &stamp, sizeof(TIMESTAMP_STRUCT) );
					stamp.hour = time.hour;
					stamp.minute = time.minute;
					stamp.second = time.second;

#ifdef UNICODE
//						m_pFields[i] = MDBField( stamp, szwColumnName );
#else
						m_pFields[i] = MDBField( stamp, szColumnName );
#endif
					}
					else if( hRet == SQL_NO_DATA )
						break;
					break;
				}
				case SQL_TYPE_TIMESTAMP:	//TimeStamp
				{
					hRet = SQLFetch( m_hStatement );
					if( hRet == SQL_SUCCESS || hRet == SQL_SUCCESS_WITH_INFO )
					{
						TIMESTAMP_STRUCT timestamp;
						ZeroMemory( &timestamp, sizeof(TIMESTAMP_STRUCT) );

						hRet = SQLGetData( m_hStatement, (SQLUSMALLINT)i + 1,
							SQL_C_TYPE_TIMESTAMP, (SQLPOINTER)&timestamp, sizeof(DATE_STRUCT),
							NULL );

#ifdef UNICODE
//						m_pFields[i] = MDBField( timestamp, szwColumnName );
#else
						m_pFields[i] = MDBField( timestamp, szColumnName );
#endif
					}
					else if( hRet == SQL_NO_DATA )
						break;
					break;
				}

				//TODO : BINARY

				case SQL_CHAR:			//String
				case SQL_VARCHAR:
				{
					hRet = SQLFetch( m_hStatement );
					if( hRet == SQL_SUCCESS || hRet == SQL_SUCCESS_WITH_INFO )
					{
#ifdef UNICODE
						wchar_t szwBuffer[256] = { 0 };

						hRet = SQLGetData( m_hStatement, (SQLUSMALLINT)i + 1,
							SQL_C_WCHAR, (SQLPOINTER)szwBuffer, 256, NULL );

						m_pFields[i] = MDBField( szwBuffer, szwColumnName );
#else
						char szBuffer[256] = { 0 };

						hRet = SQLGetData( m_hStatement, (SQLUSMALLINT)i + 1,
							SQL_C_CHAR, (SQLPOINTER)szBuffer, 256, NULL );

						m_pFields[i] = MDBField( szBuffer, szColumnName );
#endif
					}
					else if( hRet == SQL_NO_DATA )
						break;
					break;
				}
				default:
					break;
			}
		}
	}
}