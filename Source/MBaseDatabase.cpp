#include "MBaseDatabase.h"

MBaseDatabase::MBaseDatabase()
{
	m_pFields = NULL;
	m_nFieldsCount = 0;
	m_bIsConnected = false;
}

MBaseDatabase::~MBaseDatabase()
{
}

MDBField& MBaseDatabase::GetField( const int nIndex )
{
	if( nIndex < 0 || nIndex > m_nFieldsCount )
	{
		_ASSERT( false );
		return *new MDBField();
	}

	return m_pFields[nIndex];
}

MDBField& MBaseDatabase::GetFieldW( const wchar_t* pwszColumnName )
{
#ifdef UNICODE
	for( int i = 0; i < m_nFieldsCount; i++ )
	{
		if( !wcscmp( m_pFields[i].GetName(), pwszColumnName ) )
			return m_pFields[i];
	}
#else
	char szColumnName[64] = { 0 };
	WideCharToMultiByte( CP_ACP, MB_COMPOSITE, pwszColumnName, -1, szColumnName,
		sizeof(szColumnName), NULL, NULL );

	for( int i = 0; i < m_nFieldsCount; i++ )
	{
		if( !_stricmp( m_pFields[i].GetName(), szColumnName ) )
			return m_pFields[i];
	}
#endif

	return *new MDBField();
}

MDBField& MBaseDatabase::GetFieldA( const char* pszColumnName )
{
#ifdef UNICODE
	wchar_t wszColumnName[64] = { 0 };
	MultiByteToWideChar( CP_ACP, MB_COMPOSITE, pszColumnName, -1, wszColumnName,
		(sizeof(wszColumnName) / 2) );

	for( int i = 0; i < m_nFieldsCount; i++ )
	{
		if( !wcscmp( m_pFields[i].GetName(), wszColumnName ) )
			return m_pFields[i];
	}
#else
	for( int i = 0; i < m_nFieldsCount; i++ )
	{
		if( !_stricmp( m_pFields[i].GetName(), pszColumnName ) )
			return m_pFields[i];
	}
#endif

	return *new MDBField();
}

#ifdef UNICODE
MDBField& MBaseDatabase::GetField( const wchar_t* pwszColumnName )
{
	return GetFieldW( pwszColumnName );
}

#else
MDBField& MBaseDatabase::GetField( const char* pszColumnName )
{
	return GetFieldA( pszColumnName );
}
#endif // UNICODE