#pragma once

#include "MDBField.h"

class MBaseDatabase
{
public:
	MBaseDatabase();
	virtual ~MBaseDatabase();

public:
	virtual bool ConnectW( const wchar_t* pwszHost, const wchar_t* pwszDatabase,
		const wchar_t* pwszUsername, const wchar_t* pwszPassword ) = 0;
	virtual bool ConnectA( const char* pszHost, const char* pszDatabase,
		const char* pszUsername, const char* pszPassword ) = 0;

	virtual void Disconnect() = 0;
	virtual bool GetFieldsInfo() = 0;

	virtual bool ExecuteQueryW( const wchar_t* pwszQuery ) = 0;
	virtual bool ExecuteQueryA( const char* pszQuery ) = 0;

	MDBField&	GetField( const int nIndex );
	MDBField&	GetFieldW( const wchar_t* pwszColumnName );
	MDBField&	GetFieldA( const char* pszColumnName );

#ifdef UNICODE
	virtual bool Connect( const wchar_t* pwszHost, const wchar_t* pwszDatabase,
		const wchar_t* pwszUsername, const wchar_t* pwszPassword ) = 0;

	virtual bool ExecuteQuery( const wchar_t* pwszQuery ) = 0;

	MDBField& GetField( const wchar_t* pwszColumnName );

#else
	virtual bool Connect( const char* pszHost, const char* pszDatabase,
		const char* pszUsername, const char* pszPassword ) = 0;

	virtual bool ExecuteQuery( const char* pszQuery ) = 0;

	MDBField& GetField( const char* pszQuery );
#endif // UNICODE

public:
	int			GetFieldsCount()	{ return m_nFieldsCount; }
	bool		IsConnected()		{ return m_bIsConnected; }

protected:
	MDBField*	m_pFields;
	int			m_nFieldsCount;	
	bool		m_bIsConnected;
};