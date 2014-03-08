#pragma once

#include <Windows.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <assert.h>

#include <sql.h>
#include <sqlext.h>
#include <sqlucode.h>
#include <sqltypes.h>

//#include "MMSSQLError.h"

enum EDatabaseVariableType
{
	DBVT_NULL		= 0,
	DBVT_BOOL,
	DBVT_CHAR,
	DBVT_UCHAR,
	DBVT_SHORT,
	DBVT_USHORT,
	DBVT_LONG,
	DBVT_ULONG,
	DBVT_FLOAT,
	DBVT_DOUBLE,
	DBVT_DATE,
	DBVT_BINARY,
	DBVT_STRING,

	DBVT_END
};

struct MDBDateTime
{
	short year;
	unsigned short month;
	unsigned short day;
	unsigned short hour;
	unsigned short minute;
	unsigned short second;
	unsigned long fraction;
};

class MDBFieldVariable
{
public:
	MDBFieldVariable()
	{
	}
	~MDBFieldVariable()
	{
	}

public:
	EDatabaseVariableType	m_nType;

public:
	union
	{
		bool				m_boolValue;
		signed char			m_charValue;
		unsigned char		m_ucharValue;
		unsigned short		m_shortValue;
		unsigned short		m_ushortValue;
		unsigned long		m_longValue;
		unsigned long		m_ulongValue;
		float				m_floatValue;
		double				m_doubleValue;
		MDBDateTime*		m_pDate;
#ifdef UNICODE
		std::wstring*		m_strString;
#else
		std::string*			m_strString;
#endif // UNICODE
	};
};

class MDBField : public MDBFieldVariable
{
public:
	MDBField();

#ifdef UNICODE
	MDBField( const bool bVal, const wchar_t* pwszColumnName );
	MDBField( const signed char nVal, const wchar_t* pwszColumnName );
	MDBField( const unsigned char nVal, const wchar_t* pwszColumnName );
	MDBField( const signed short nVal, const wchar_t* pwszColumnName );
	MDBField( const unsigned short nVal, const wchar_t* pwszColumnName );
	MDBField( const signed int nVal, const wchar_t* pwszColumnName );
	MDBField( const unsigned int nVal, const wchar_t* pwszColumnName );
	MDBField( const signed long nVal, const wchar_t* pwszColumnName );
	MDBField( const unsigned long nVal, const wchar_t* pwszColumnName );
	MDBField( const float fVal, const wchar_t* pwszColumnName );
	MDBField( const double fVal, const wchar_t* pwszColumnName );
	MDBField( const MDBDateTime& timestamp, const wchar_t* pwszColumnName );
	MDBField( const wchar_t* pwszVal, const wchar_t* pwszColumnName );

#else

	MDBField( const bool bVal, const char* pszColumnName );
	MDBField( const signed char nVal, const char* pszColumnName );
	MDBField( const unsigned char nVal, const char* pszColumnName );
	MDBField( const signed short nVal, const char* pszColumnName );
	MDBField( const unsigned short nVal, const char* pszColumnName );
	MDBField( const signed int nVal, const char* pszColumnName );
	MDBField( const unsigned int nVal, const char* pszColumnName );
	MDBField( const signed long nVal, const char* pszColumnName );
	MDBField( const unsigned long nVal, const char* pszColumnName );
	MDBField( const float fVal, const char* pszColumnName );
	MDBField( const double fVal, const char* pszColumnName );
	MDBField( const MDBDateTime& timestamp, const char* pszColumnName );
	MDBField( const char* pszVal, const char* pszColumnName );
#endif // UNICODE

	~MDBField();

public:
	MDBField& operator =( const bool bVal );
	MDBField& operator =( const signed char nVal );
	MDBField& operator =( const unsigned char nVal );
	MDBField& operator =( const signed short nVal );
	MDBField& operator =( const unsigned short nVal );
	MDBField& operator =( const signed int nVal );
	MDBField& operator =( const unsigned int nVal );
	MDBField& operator =( const signed long nVal );
	MDBField& operator =( const unsigned long nVal );
	MDBField& operator =( const float fVal );
	MDBField& operator =( const double fVal );
	MDBField& operator =( const MDBDateTime& pnStamp );

#ifdef UNICODE
	MDBField& operator =( const wchar_t* pwszVal );
#else
	MDBField& operator =( const char* pszVal );
#endif // UNICODE
	
	bool				AsBool()	const;
	signed char			AsChar()	const;
	unsigned char		AsUChar()	const;
	signed short		AsShort()	const;
	unsigned short		AsUShort()	const;
	signed int			AsInt()		const;
	unsigned int		AsUInt()	const;
	signed long			AsLong()	const;
	unsigned long		AsULong()	const;
	float				AsFloat()	const;
	double				AsDouble()	const;
	MDBDateTime			AsDate()	const;
#ifdef UNICODE
//	std::wstring		AsString()	const;
#else
//	std::string			AsString() const;
#endif

	bool IsNull()	const	{ return m_bIsNull || m_nType == DBVT_NULL; }
	bool IsBool()	const	{ return m_nType == DBVT_BOOL; }
	bool IsChar()	const	{ return m_nType == DBVT_CHAR; }
	bool IsUChar()	const	{ return m_nType == DBVT_UCHAR; }
	bool IsShort()	const	{ return m_nType == DBVT_SHORT; }
	bool IsUShort()	const	{ return m_nType == DBVT_USHORT; }
	bool IsInt()	const	{ return m_nType == DBVT_LONG; }
	bool IsUInt()	const	{ return m_nType == DBVT_ULONG; }
	bool IsLong()	const	{ return m_nType == DBVT_LONG; }
	bool IsULong()	const	{ return m_nType == DBVT_ULONG; }
	bool IsFloat()	const	{ return m_nType == DBVT_FLOAT; }
	bool IsDouble()	const	{ return m_nType == DBVT_DOUBLE; }
	bool IsDate()	const	{ return m_nType == DBVT_DATE; }
	bool IsBinary() const	{ return m_nType == DBVT_BINARY; }
	bool IsString()	const	{ return m_nType == DBVT_STRING; }
	bool IsNumber() const
	{
		return m_nType == DBVT_SHORT || m_nType == DBVT_USHORT ||
				m_nType == DBVT_LONG || m_nType == DBVT_ULONG ||
				m_nType == DBVT_FLOAT || m_nType == DBVT_DOUBLE;
	}

#ifdef UNICODE
	const wchar_t* GetName() const
	{
		return m_szwName;
	}
#else
	const char*	GetName() const
	{
		return m_szName;
	}
#endif

private:
	bool	m_bIsNull;
#ifdef UNICODE
	wchar_t	m_szwName[64];
#else
	char	m_szName[64];
#endif
};