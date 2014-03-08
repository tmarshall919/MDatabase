#pragma once

#include "MMSSQLError.h"
#include "MBaseDatabase.h"

class MMSSQL : public MBaseDatabase
{
public:
	MMSSQL();
	virtual ~MMSSQL();

public:
	bool ConnectW( const wchar_t* pszwHost, const wchar_t* pszwDatabase,
		const wchar_t* pszwUsername, const wchar_t* pszwPassword );
	virtual bool ConnectA( const char* pszHost, const char* pszDatabase,
		const char* pszUsername, const char* pszwPassword );

#ifdef UNICODE
	virtual bool Connect( const wchar_t* pszwHost, const wchar_t* pszwDatabase,
		const wchar_t* pszwUsername, const wchar_t* pszwPassword );
#else
	virtual bool Connect( const char* pszHost, const char* pszDatabase,
		const char* pszUsername, const char* pszwPassword );
#endif

	virtual void Disconnect();
	virtual bool ExecuteQueryW( const wchar_t* pszwQuery );
	virtual bool ExecuteQueryA( const char* pszQuery );

#ifdef UNICODE
	virtual bool ExecuteQuery( const wchar_t* pszwQuery );
#else
	virtual bool ExecuteQuery( const char* pszQuery );
#endif

	virtual bool GetFieldsInfo();

private:
	SQLHANDLE	m_hEnvironment;
	SQLHANDLE	m_hConnection;
	SQLHANDLE	m_hStatement;
};