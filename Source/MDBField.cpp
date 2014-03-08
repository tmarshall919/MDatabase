/* TODO
 * Strings need some checks!! A.S.A.P!
 * Sanity checks for invalid heap pointing!!
 * "Blobs"/Binary & DateTime needs to be implemented fully.

 * Needs to be tested COMPLETELY!!
*/
 

#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <sstream>
#include <assert.h>

#include "MDBField.h"

MDBField::MDBField()
{
	m_nType = DBVT_NULL;
}

#ifdef UNICODE
MDBField::MDBField( const bool bVal, const wchar_t* pwszColumnName )
{
	m_nType = DBVT_BOOL;
	m_boolValue = bVal;

	wcscpy_s( m_szwName, pwszColumnName );
}

MDBField::MDBField( const signed char nVal, const wchar_t* pwszColumnName )
{
	m_nType = DBVT_CHAR;
	m_charValue = nVal;

	wcscpy_s( m_szwName, pwszColumnName );
}

MDBField::MDBField( const unsigned char nVal, const wchar_t* pwszColumnName )
{
	m_nType = DBVT_UCHAR;
	m_ucharValue = nVal;

	wcscpy_s( m_szwName, pwszColumnName );
}

MDBField::MDBField( const signed short nVal, const wchar_t* pwszColumnName )
{
	m_nType = DBVT_SHORT;
	m_shortValue = nVal;

	wcscpy_s( m_szwName, pwszColumnName );
}

MDBField::MDBField( const unsigned short nVal, const wchar_t* pwszColumnName )
{
	m_nType = DBVT_USHORT;
	m_ushortValue = nVal;

	wcscpy_s( m_szwName, pwszColumnName );
}

MDBField::MDBField( const signed int nVal, const wchar_t* pwszColumnName )
{
	m_nType = DBVT_LONG;
	m_longValue = (signed long)nVal;

	wcscpy_s( m_szwName, pwszColumnName );
}

MDBField::MDBField( const unsigned int nVal, const wchar_t* pwszColumnName )
{
	m_nType = DBVT_ULONG;
	m_longValue = (unsigned long)nVal;

	wcscpy_s( m_szwName, pwszColumnName );
}

MDBField::MDBField( const signed long nVal, const wchar_t* pwszColumnName )
{
	m_nType = DBVT_LONG;
	m_longValue = nVal;

	wcscpy_s( m_szwName, pwszColumnName );
}

MDBField::MDBField( const unsigned long nVal, const wchar_t* pwszColumnName )
{
	m_nType = DBVT_ULONG;
	m_longValue = nVal;

	wcscpy_s( m_szwName, pwszColumnName );
}

MDBField::MDBField( const float fVal, const wchar_t* pwszColumnName )
{
	m_nType = DBVT_FLOAT;
	m_floatValue = fVal;

	wcscpy_s( m_szwName, pwszColumnName );
}

MDBField::MDBField( const double fVal, const wchar_t* pwszColumnName )
{
	m_nType = DBVT_DOUBLE;
	m_doubleValue = fVal;

	wcscpy_s( m_szwName, pwszColumnName );
}

MDBField::MDBField( const MDBDateTime& timestamp, const wchar_t* pwszColumnName )
{
	m_nType = DBVT_DATE;
	m_pDate = new MDBDateTime( timestamp );

	wcscpy_s( m_szwName, pwszColumnName );
}

MDBField::MDBField( const wchar_t* pwszVal, const wchar_t* pwszColumnName )
{
	m_nType = DBVT_STRING;
	m_strString = new std::wstring( pwszVal );

	wcscpy_s( m_szwName, pwszColumnName );
}

#else

MDBField::MDBField( const bool bVal, const char* pszColumnName )
{
	m_nType = DBVT_BOOL;
	m_boolValue = bVal;

	strcpy_s( m_szName, pszColumnName );
}

MDBField::MDBField( const signed char nVal, const char* pszColumnName )
{
	m_nType = DBVT_CHAR;
	m_charValue = nVal;

	strcpy_s( m_szName, pszColumnName );
}

MDBField::MDBField( const unsigned char nVal, const char* pszColumnName )
{
	m_nType = DBVT_UCHAR;
	m_ucharValue = nVal;

	strcpy_s( m_szName, pszColumnName );
}

MDBField::MDBField( const signed short nVal, const char* pszColumnName )
{
	m_nType = DBVT_SHORT;
	m_shortValue = nVal;

	strcpy_s( m_szName, pszColumnName );
}

MDBField::MDBField( const unsigned short nVal, const char* pszColumnName )
{
	m_nType = DBVT_USHORT;
	m_ushortValue = nVal;

	strcpy_s( m_szName, pszColumnName );
}

MDBField::MDBField( const signed int nVal, const char* pszColumnName )
{
	m_nType = DBVT_LONG;
	m_longValue = (signed long)nVal;

	strcpy_s( m_szName, pszColumnName );
}

MDBField::MDBField( const unsigned int nVal, const char* pszColumnName )
{
	m_nType = DBVT_ULONG;
	m_longValue = (unsigned long)nVal;

	strcpy_s( m_szName, pszColumnName );
}

MDBField::MDBField( const signed long nVal, const char* pszColumnName )
{
	m_nType = DBVT_LONG;
	m_longValue = nVal;

	strcpy_s( m_szName, pszColumnName );
}

MDBField::MDBField( const unsigned long nVal, const char* pszColumnName )
{
	m_nType = DBVT_ULONG;
	m_longValue = nVal;

	strcpy_s( m_szName, pszColumnName );
}

MDBField::MDBField( const float fVal, const char* pszColumnName )
{
	m_nType = DBVT_FLOAT;
	m_floatValue = fVal;

	strcpy_s( m_szName, pszColumnName );
}

MDBField::MDBField( const double fVal, const char* pszColumnName )
{
	m_nType = DBVT_DOUBLE;
	m_doubleValue = fVal;

	strcpy_s( m_szName, pszColumnName );
}

MDBField::MDBField( const TIMESTAMP_STRUCT& timestamp, const char* pszColumnName )
{
	m_nType = DBVT_DATE;
	m_pDate = new TIMESTAMP_STRUCT( timestamp );

	strcpy_s( m_szName, pszColumnName );
}

MDBField::MDBField( const char* pszVal, const char* pszColumnName )
{
	m_nType = DBVT_STRING;
	m_pString = std::string( pszVal );

	strcpy_s( m_szName, pszColumnName );
}

#endif // UNICODE

MDBField::~MDBField()
{
}

MDBField& MDBField::operator =( const bool bVal )
{
	switch( m_nType )
	{
		case DBVT_BOOL:
			m_boolValue = bVal;
			return *this;
		case DBVT_CHAR:
			m_charValue = bVal ? L'T' : L'F';
			return *this;
		case DBVT_UCHAR:
			m_ucharValue = bVal ? L'T' : L'F';
			return *this;
		case DBVT_SHORT:
			m_shortValue = bVal ? 1 : 0;
			return *this;
		case DBVT_USHORT:
			m_ushortValue = bVal ? 1 : 0;
			return *this;
		case DBVT_LONG:
			m_longValue = bVal ? 1 : 0;
			return *this;
		case DBVT_ULONG:
			m_ulongValue = bVal ? 1 : 0;
			return *this;
		case DBVT_FLOAT:
			m_floatValue = bVal ? 1.0f : 0.0f;
			return *this;
		case DBVT_DOUBLE:
			m_doubleValue = bVal ? 1.0f : 0.0f;
			return *this;
		case DBVT_STRING:
		{
#ifdef UNICODE
			m_strString = new std::wstring( (bVal ? L"T" : L"F") );
#else
			m_strString = new std::string( (bVal ? 'T' : 'F') );
#endif
			return *this;
		}

		case DBVT_NULL:
		case DBVT_DATE:
			_ASSERT( false );
			return *this;
		default:
			_ASSERT( false );
	}

	return *this;
}

MDBField& MDBField::operator =( const signed char nVal )
{
	switch( m_nType )
	{
		case DBVT_BOOL:
			m_boolValue = (nVal == 1) ? true : false;
			return *this;
		case DBVT_CHAR:
			m_charValue = nVal;
			return *this;
		case DBVT_UCHAR:
			m_ucharValue = (unsigned char)nVal;
			return *this;
		case DBVT_SHORT:
			m_shortValue = (signed short)nVal;
			return *this;
		case DBVT_USHORT:
			m_ushortValue = (unsigned short)nVal;
			return *this;
		case DBVT_LONG:
			m_longValue = (signed long)nVal;
			return *this;
		case DBVT_ULONG:
			m_ulongValue = (unsigned long)nVal;
			return *this;
		case DBVT_FLOAT:
			m_floatValue = (float)nVal;
			return *this;
		case DBVT_DOUBLE:
			m_doubleValue = (double)nVal;
			return *this;
		case DBVT_STRING:
		{
#ifdef UNICODE
			std::wostringstream oss;
			oss << (int)nVal;
			m_strString = new std::wstring( oss.str() );
#else
			std::ostringstream oss;
			oss << (int)nVal;
			m_strString = new std::string( oss.str() );
#endif
			return *this;
		}

		case DBVT_NULL:
		case DBVT_DATE:
			_ASSERT( false );
			return *this;
		default:
			_ASSERT( false );
	}

	return *this;
}

MDBField& MDBField::operator =( const unsigned char nVal )
{
	switch( m_nType )
	{
		case DBVT_BOOL:
			m_boolValue = (nVal == 1) ? true : false;
			return *this;
		case DBVT_CHAR:
			m_charValue = (signed char)nVal;
			return *this;
		case DBVT_UCHAR:
			m_ucharValue = nVal;
			return *this;
		case DBVT_SHORT:
			m_shortValue = (signed short)nVal;
			return *this;
		case DBVT_USHORT:
			m_ushortValue = (unsigned short)nVal;
			return *this;
		case DBVT_LONG:
			m_longValue = (signed long)nVal;
			return *this;
		case DBVT_ULONG:
			m_ulongValue = (unsigned long)nVal;
			return *this;
		case DBVT_FLOAT:
			m_floatValue = (float)nVal;
			return *this;
		case DBVT_DOUBLE:
			m_doubleValue = (double)nVal;
			return *this;
		case DBVT_STRING:
		{
#ifdef UNICODE
			std::wostringstream oss;
			oss << (int)nVal;
			m_strString = new std::wstring( oss.str() );
#else
			std::ostringstream oss;
			oss << (int)nVal;
			m_strString = new std::string( oss.str() );
#endif
			return *this;
		}
		
		case DBVT_NULL:
		case DBVT_DATE:
			_ASSERT( false );
			return *this;
		default:
			_ASSERT( false );
	}

	return *this;
}

MDBField& MDBField::operator =( const signed short nVal )
{
	switch( m_nType )
	{
		case DBVT_BOOL:
			m_boolValue = (nVal == 1) ? true : false;
			return *this;
		case DBVT_CHAR:
			m_charValue = (signed char)nVal;
			return *this;
		case DBVT_UCHAR:
			m_ucharValue = (unsigned char)nVal;
			return *this;
		case DBVT_SHORT:
			m_shortValue = nVal;
			return *this;
		case DBVT_USHORT:
			m_ushortValue = (unsigned short)nVal;
			return *this;
		case DBVT_LONG:
			m_longValue = (signed long)nVal;
			return *this;
		case DBVT_ULONG:
			m_ulongValue = (unsigned long)nVal;
			return *this;
		case DBVT_FLOAT:
			m_floatValue = (float)nVal;
			return *this;
		case DBVT_DOUBLE:
			m_doubleValue = (double)nVal;
			return *this;
		case DBVT_STRING:
		{
#ifdef UNICODE
			std::wostringstream oss;
			oss << (int)nVal;
			m_strString = new std::wstring( oss.str() );
#else
			std::ostringstream oss;
			oss << (int)nVal;
			m_strString = new std::string( oss.str() );
#endif
			return *this;
		}

		case DBVT_NULL:
		case DBVT_DATE:
			_ASSERT( false );
			return *this;
		default:
			_ASSERT( false );
	}

	return *this;
}

MDBField& MDBField::operator =( const unsigned short nVal )
{
	switch( m_nType )
	{
		case DBVT_BOOL:
			m_boolValue = (nVal == 1) ? true : false;
			return *this;
		case DBVT_CHAR:
			m_charValue = (signed char)nVal;
			return *this;
		case DBVT_UCHAR:
			m_ucharValue = (unsigned char)nVal;
			return *this;
		case DBVT_SHORT:
			m_shortValue = (signed short)nVal;
			return *this;
		case DBVT_USHORT:
			m_ushortValue = nVal;
			return *this;
		case DBVT_LONG:
			m_longValue = (signed long)nVal;
			return *this;
		case DBVT_ULONG:
			m_ulongValue = (unsigned long)nVal;
			return *this;
		case DBVT_FLOAT:
			m_floatValue = (float)nVal;
			return *this;
		case DBVT_DOUBLE:
			m_doubleValue = (double)nVal;
			return *this;
		case DBVT_STRING:
		{
#ifdef UNICODE
			std::wostringstream oss;
			oss << (int)nVal;
			m_strString = new std::wstring( oss.str() );
#else
			std::ostringstream oss;
			oss << (int)nVal;
			m_strString = new std::string( oss.str() );
#endif
			return *this;
		}

		case DBVT_NULL:
		case DBVT_DATE:
			_ASSERT( false );
			return *this;
		default:
			_ASSERT( false );
	}

	return *this;
}

MDBField& MDBField::operator =( const signed int nVal )
{
	switch( m_nType )
	{
		case DBVT_BOOL:
			m_boolValue = (nVal == 1) ? true : false;
			return *this;
		case DBVT_CHAR:
			m_charValue = (signed char)nVal;
			return *this;
		case DBVT_UCHAR:
			m_ucharValue = (unsigned char)nVal;
			return *this;
		case DBVT_SHORT:
			m_shortValue = (signed short)nVal;
			return *this;
		case DBVT_USHORT:
			m_ushortValue = (unsigned short)nVal;
			return *this;
		case DBVT_LONG:
			m_longValue = (signed long)nVal;
			return *this;
		case DBVT_ULONG:
			m_ulongValue = (unsigned long)nVal;
			return *this;
		case DBVT_FLOAT:
			m_floatValue = (float)nVal;
			return *this;
		case DBVT_DOUBLE:
			m_doubleValue = (double)nVal;
			return *this;
		case DBVT_STRING:
		{
#ifdef UNICODE
			std::wostringstream oss;
			oss << (int)nVal;
			m_strString = new std::wstring( oss.str() );
#else
			std::ostringstream oss;
			oss << (int)nVal;
			m_strString = new std::string( oss.str() );
#endif
			return *this;
		}
		
		case DBVT_NULL:
		case DBVT_DATE:
			_ASSERT( false );
			return *this;
		default:
			_ASSERT( false );
	}

	return *this;
}

MDBField& MDBField::operator =( const unsigned int nVal )
{
	switch( m_nType )
	{
		case DBVT_BOOL:
			m_boolValue = (nVal == 1) ? true : false;
			return *this;
		case DBVT_CHAR:
			m_charValue = (signed char)nVal;
			return *this;
		case DBVT_UCHAR:
			m_ucharValue = (unsigned char)nVal;
			return *this;
		case DBVT_SHORT:
			m_shortValue = (signed short)nVal;
			return *this;
		case DBVT_USHORT:
			m_ushortValue = (unsigned short)nVal;
			return *this;
		case DBVT_LONG:
			m_longValue = (signed long)nVal;
			return *this;
		case DBVT_ULONG:
			m_ulongValue = (unsigned long)nVal;
			return *this;
		case DBVT_FLOAT:
			m_floatValue = (float)nVal;
			return *this;
		case DBVT_DOUBLE:
			m_doubleValue = (double)nVal;
			return *this;
		case DBVT_STRING:
		{
#ifdef UNICODE
			std::wostringstream oss;
			oss << (int)nVal;
			m_strString = new std::wstring( oss.str() );
#else
			std::ostringstream oss;
			oss << (int)nVal;
			m_strString = new std::string( oss.str() );
#endif
			return *this;
		}
		
		case DBVT_NULL:
		case DBVT_DATE:
			_ASSERT( false );
			return *this;
		default:
			_ASSERT( false );
	}

	return *this;
}

MDBField& MDBField::operator =( const signed long nVal )
{
	switch( m_nType )
	{
		case DBVT_BOOL:
			m_boolValue = (nVal == 1) ? true : false;
			return *this;
		case DBVT_CHAR:
			m_charValue = (signed char)nVal;
			return *this;
		case DBVT_UCHAR:
			m_ucharValue = (unsigned char)nVal;
			return *this;
		case DBVT_SHORT:
			m_shortValue = (signed short)nVal;
			return *this;
		case DBVT_USHORT:
			m_ushortValue = (unsigned short)nVal;
			return *this;
		case DBVT_LONG:
			m_longValue = nVal;
			return *this;
		case DBVT_ULONG:
			m_ulongValue = (unsigned long)nVal;
			return *this;
		case DBVT_FLOAT:
			m_floatValue = (float)nVal;
			return *this;
		case DBVT_DOUBLE:
			m_doubleValue = (double)nVal;
			return *this;
		case DBVT_STRING:
		{
#ifdef UNICODE
			std::wostringstream oss;
			oss << (int)nVal;
			m_strString = new std::wstring( oss.str() );
#else
			std::ostringstream oss;
			oss << (int)nVal;
			m_strString = new std::string( oss.str() );
#endif
			return *this;
		}
		
		case DBVT_NULL:
		case DBVT_DATE:
			_ASSERT( false );
			return *this;
		default:
			_ASSERT( false );
	}

	return *this;
}

MDBField& MDBField::operator =( const unsigned long nVal )
{
	switch( m_nType )
	{
		case DBVT_BOOL:
			m_boolValue = (nVal == 1) ? true : false;
			return *this;
		case DBVT_CHAR:
			m_charValue = (signed char)nVal;
			return *this;
		case DBVT_UCHAR:
			m_ucharValue = (unsigned char)nVal;
			return *this;
		case DBVT_SHORT:
			m_shortValue = (signed short)nVal;
			return *this;
		case DBVT_USHORT:
			m_ushortValue = (unsigned short)nVal;
			return *this;
		case DBVT_LONG:
			m_longValue = (signed long)nVal;
			return *this;
		case DBVT_ULONG:
			m_ulongValue = nVal;
			return *this;
		case DBVT_FLOAT:
			m_floatValue = (float)nVal;
			return *this;
		case DBVT_DOUBLE:
			m_doubleValue = (double)nVal;
			return *this;
		case DBVT_STRING:
		{
#ifdef UNICODE
			std::wostringstream oss;
			oss << (int)nVal;
			m_strString = new std::wstring( oss.str() );
#else
			std::ostringstream oss;
			oss << (int)nVal;
			m_strString = new std::string( oss.str() );
#endif
			return *this;
		}
		
		case DBVT_NULL:
		case DBVT_DATE:
			_ASSERT( false );
			return *this;
		default:
			_ASSERT( false );
	}

	return *this;
}

MDBField& MDBField::operator =( const float fVal )
{
	switch( m_nType )
	{
		case DBVT_BOOL:
			m_boolValue = (fVal == 1.0f) ? true : false;
			return *this;
		case DBVT_CHAR:
			m_charValue = (signed char)fVal;
			return *this;
		case DBVT_UCHAR:
			m_ucharValue = (unsigned char)fVal;
			return *this;
		case DBVT_SHORT:
			m_shortValue = (signed short)fVal;
			return *this;
		case DBVT_USHORT:
			m_ushortValue = (unsigned short)fVal;
			return *this;
		case DBVT_LONG:
			m_longValue = (signed long)fVal;
			return *this;
		case DBVT_ULONG:
			m_ulongValue = (unsigned long)fVal;
			return *this;
		case DBVT_FLOAT:
			m_floatValue = fVal;
			return *this;
		case DBVT_DOUBLE:
			m_doubleValue = (double)fVal;
			return *this;
		case DBVT_STRING:
		{
#ifdef UNICODE
			std::wostringstream oss;
			oss << (int)fVal;
			m_strString = new std::wstring( oss.str() );
#else
			std::ostringstream oss;
			oss << (int)fVal;
			m_strString = new std::string( oss.str() );
#endif
			return *this;
		}
		
		case DBVT_NULL:
		case DBVT_DATE:
			_ASSERT( false );
			return *this;
		default:
			_ASSERT( false );
	}

	return *this;
}

MDBField& MDBField::operator =( const double fVal )
{
	switch( m_nType )
	{
		case DBVT_BOOL:
			m_boolValue = (fVal == 1.0f) ? true : false;
			return *this;
		case DBVT_CHAR:
			m_charValue = (signed char)fVal;
			return *this;
		case DBVT_UCHAR:
			m_ucharValue = (unsigned char)fVal;
			return *this;
		case DBVT_SHORT:
			m_shortValue = (signed short)fVal;
			return *this;
		case DBVT_USHORT:
			m_ushortValue = (unsigned short)fVal;
			return *this;
		case DBVT_LONG:
			m_longValue = (signed long)fVal;
			return *this;
		case DBVT_ULONG:
			m_ulongValue = (unsigned long)fVal;
			return *this;
		case DBVT_FLOAT:
			m_floatValue = (float)fVal;
			return *this;
		case DBVT_DOUBLE:
			m_doubleValue = fVal;
			return *this;
		case DBVT_STRING:
		{
#ifdef UNICODE
			std::wostringstream oss;
			oss << (int)fVal;
			m_strString = new std::wstring( oss.str() );
#else
			std::ostringstream oss;
			oss << (int)fVal;
			m_strString = new std::string( oss.str() );
#endif
			return *this;
		}
		
		case DBVT_NULL:
		case DBVT_DATE:
			_ASSERT( false );
			return *this;
		default:
			_ASSERT( false );
	}

	return *this;
}

MDBField& MDBField::operator =( const MDBDateTime& pnStamp )
{
	switch( m_nType )
	{
		case DBVT_NULL:
		case DBVT_BOOL:
		case DBVT_CHAR:
		case DBVT_UCHAR:
		case DBVT_SHORT:
		case DBVT_USHORT:
		case DBVT_LONG:
		case DBVT_ULONG:
		case DBVT_FLOAT:
		case DBVT_DOUBLE:
			_ASSERT( false );

		case DBVT_DATE:
		{
			if( m_pDate != NULL )
				delete m_pDate;
			m_pDate = new MDBDateTime();

			m_pDate->day = pnStamp.day;
			m_pDate->fraction = pnStamp.fraction;
			m_pDate->hour = pnStamp.hour;
			m_pDate->minute = pnStamp.minute;
			m_pDate->month = pnStamp.month;
			m_pDate->second = pnStamp.second;
			m_pDate->year = pnStamp.year;
			return *this;
		}

		case DBVT_STRING:
		{
#ifdef UNICODE
			std::wostringstream oss;
#else
			std::ostringstream oss;
#endif
			oss << m_pDate->month << _T("//") <<
				m_pDate->day << _T("//") <<
				m_pDate->year << _T(" ") <<
				m_pDate->hour << _T(":") <<
				m_pDate->minute << _T(":") <<
				m_pDate->second << _T(":");
#ifdef UNICODE
			m_strString = new std::wstring( oss.str() );
#else
			m_strString = new std::string( oss.str() );
#endif
			return *this;
		}
		default:
			_ASSERT( false );
	}

	return *this;
}

#ifdef UNICODE
MDBField& MDBField::operator =( const wchar_t* pwszVal )
{
	switch( m_nType )
	{
		case DBVT_BOOL:
			m_boolValue = _wtoi( pwszVal ) != 0;
			return *this;
		case DBVT_CHAR:
			m_charValue = (signed char)pwszVal[0];
			return *this;
		case DBVT_UCHAR:
			m_ucharValue = (unsigned char)pwszVal[0];
			return *this;
		case DBVT_SHORT:
			m_shortValue = (signed short)_wtoi( pwszVal );
			return *this;
		case DBVT_USHORT:
			m_ushortValue = (unsigned short)_wtoi( pwszVal );
			return *this;
		case DBVT_LONG:
			m_longValue = (signed long)_wtoi( pwszVal );
			return *this;
		case DBVT_ULONG:
			m_ulongValue = (unsigned long)_wtoi( pwszVal );
			return *this;
		case DBVT_FLOAT:
			m_floatValue = (float)_wtof( pwszVal );
			return *this;
		case DBVT_DOUBLE:
			m_doubleValue = (double)_wtof( pwszVal );
			return *this;
		case DBVT_STRING:
			m_strString = new std::wstring( pwszVal );
			return *this;
		case DBVT_DATE: //TODO
			return *this;

		case DBVT_NULL:
			_ASSERT( false );
		default:
			_ASSERT( false );
	}

	return *this;
}

#else
MDBField& MDBField::operator =( const char* pszVal )
{
	switch( m_nType )
	{
		case DBVT_BOOL:
			m_boolValue = atoi( pszVal ) != 0;
			return *this;
		case DBVT_CHAR:
			m_charValue = (signed char)pszVal[0];
			return *this;
		case DBVT_UCHAR:
			m_ucharValue = (unsigned char)pszVal[0];
			return *this;
		case DBVT_SHORT:
			m_shortValue = (signed short)atoi( pszVal );
			return *this;
		case DBVT_USHORT:
			m_ushortValue = (unsigned short)atoi( pszVal );
			return *this;
		case DBVT_LONG:
			m_longValue = (signed long)atoi( pszVal );
			return *this;
		case DBVT_ULONG:
			m_ulongValue = (unsigned long)atoi( pszVal );
			return *this;
		case DBVT_FLOAT:
			m_floatValue = (float)atof( pszVal );
			return *this;
		case DBVT_DOUBLE:
			m_doubleValue = (double)atof( pszVal );
			return *this;
		case DBVT_STRING:
			m_strString = pszVal;
			return *this;
		case DBVT_DATE: //TODO
			return *this;

		case DBVT_NULL:
			_ASSERT( false );
		default:
			_ASSERT( false );
	}

	return *this;
}

#endif

bool MDBField::AsBool()	const
{
	if( IsNull() )
		return false;

	switch( m_nType )
	{
		case DBVT_NULL:
			return false;
		case DBVT_BOOL:
			return m_boolValue;
		case DBVT_UCHAR:
			return (m_ucharValue == _T('T') || m_ucharValue == _T('1'));
		case DBVT_SHORT:
			return (m_shortValue != 0);
		case DBVT_LONG:
			return (m_longValue != 0);
		case DBVT_FLOAT:
			return (m_floatValue != 0.0f);
		case DBVT_DOUBLE:
			return (m_doubleValue != 0.0f);
		case DBVT_DATE:
			_ASSERT( false );
		default:
			_ASSERT( false );
	}

	return false;
}

signed char MDBField::AsChar() const
{
	if( IsNull() )
		return 0;

	switch( m_nType )
	{
		case DBVT_NULL:
			return 0;
		case DBVT_BOOL:
			return m_boolValue ? 1 : 0;
		case DBVT_CHAR:
			return m_charValue;
		case DBVT_UCHAR:
			return (signed char)m_ucharValue;
		case DBVT_SHORT:
			return (signed char)m_shortValue;
		case DBVT_USHORT:
			return (signed char)m_ushortValue;
		case DBVT_LONG:
			return (signed char)m_longValue;
		case DBVT_ULONG:
			return (signed char)m_ulongValue;
		case DBVT_FLOAT:
			return (signed char)m_floatValue;
		case DBVT_DOUBLE:
			return (signed char)m_doubleValue;
		case DBVT_DATE:
			_ASSERT( false );
		case DBVT_STRING:
			if( m_strString != NULL && m_strString->length() > 0 )
				return (signed char)m_strString->at( 0 );
		default:
			_ASSERT( false );
	}

	return 0;
}

unsigned char MDBField::AsUChar() const
{
	if( IsNull() )
		return 0;

	switch( m_nType )
	{
		case DBVT_NULL:
			return 0;
		case DBVT_BOOL:
			return m_boolValue ? 1 : 0;
		case DBVT_CHAR:
			return (unsigned char)m_charValue;
		case DBVT_UCHAR:
			return m_ucharValue;
		case DBVT_SHORT:
			return (unsigned char)m_shortValue;
		case DBVT_USHORT:
			return (unsigned char)m_ushortValue;
		case DBVT_LONG:
			return (unsigned char)m_longValue;
		case DBVT_ULONG:
			return (unsigned char)m_ulongValue;
		case DBVT_FLOAT:
			return (unsigned char)m_floatValue;
		case DBVT_DOUBLE:
			return (unsigned char)m_doubleValue;
		case DBVT_DATE:
			_ASSERT( false );
		case DBVT_STRING:
			if( m_strString != NULL && m_strString->length() > 0 )
				return (signed char)m_strString->at( 0 );
		default:
			_ASSERT( false );
	}

	return 0;
}

signed short MDBField::AsShort() const
{
	if( IsNull() )
		return 0;

	switch( m_nType )
	{
		case DBVT_NULL:
			return 0;
		case DBVT_BOOL:
			return m_boolValue ? 1 : 0;
		case DBVT_CHAR:
			return (signed short)m_charValue;
		case DBVT_UCHAR:
			return (signed short)m_ucharValue;
		case DBVT_SHORT:
			return m_shortValue;
		case DBVT_USHORT:
			return (signed short)m_ushortValue;
		case DBVT_LONG:
			return (signed short)m_longValue;
		case DBVT_ULONG:
			return (signed short)m_ulongValue;
		case DBVT_FLOAT:
			return (signed short)m_floatValue;
		case DBVT_DOUBLE:
			return (signed short)m_doubleValue;
		case DBVT_DATE:
			_ASSERT( false );
		case DBVT_STRING:
#ifdef UNICODE
			return (signed short)_wtoi( m_strString->c_str() );
#else
			return (signed short)atoi( m_strString->c_str() );
#endif
		default:
			_ASSERT( false );
	}

	return 0;
}

unsigned short MDBField::AsUShort() const
{
	if( IsNull() )
		return 0;

	switch( m_nType )
	{
		case DBVT_NULL:
			return 0;
		case DBVT_BOOL:
			return m_boolValue ? 1 : 0;
		case DBVT_CHAR:
			return (unsigned short)m_charValue;
		case DBVT_UCHAR:
			return (unsigned short)m_ucharValue;
		case DBVT_SHORT:
			return (unsigned short)m_shortValue;
		case DBVT_USHORT:
			return m_ushortValue;
		case DBVT_LONG:
			return (unsigned short)m_longValue;
		case DBVT_ULONG:
			return (unsigned short)m_ulongValue;
		case DBVT_FLOAT:
			return (unsigned short)m_floatValue;
		case DBVT_DOUBLE:
			return (unsigned short)m_doubleValue;
		case DBVT_DATE:
			_ASSERT( false );
		case DBVT_STRING:
#ifdef UNICODE
			return (unsigned short)_wtoi( m_strString->c_str() );
#else
			return (unsigned short)atoi( m_strString->c_str() );
#endif
		default:
			_ASSERT( false );
	}

	return 0;
}

signed int MDBField::AsInt() const
{
	if( IsNull() )
		return 0;

	switch( m_nType )
	{
		case DBVT_NULL:
			return 0;
		case DBVT_BOOL:
			return m_boolValue ? 1 : 0;
		case DBVT_CHAR:
			return (signed int)m_charValue;
		case DBVT_UCHAR:
			return (signed int)m_ucharValue;
		case DBVT_SHORT:
			return (signed int)m_shortValue;
		case DBVT_USHORT:
			return (signed int)m_ushortValue;
		case DBVT_LONG:
			return (signed int)m_longValue;
		case DBVT_ULONG:
			return (signed int)m_ulongValue;
		case DBVT_FLOAT:
			return (signed int)m_floatValue;
		case DBVT_DOUBLE:
			return (signed int)m_doubleValue;
		case DBVT_DATE:
			_ASSERT( false );
		case DBVT_STRING:
#ifdef UNICODE
			return (signed int)_wtoi( &m_strString->at(0) );
#else
			return (signed int)atoi( &m_strString->at(0) );
#endif
		default:
			_ASSERT( false );
	}

	return 0;
}

unsigned int MDBField::AsUInt() const
{
	if( IsNull() )
		return 0;

	switch( m_nType )
	{
		case DBVT_NULL:
			return 0;
		case DBVT_BOOL:
			return m_boolValue ? 1 : 0;
		case DBVT_CHAR:
			return (unsigned int)m_charValue;
		case DBVT_UCHAR:
			return (unsigned int)m_ucharValue;
		case DBVT_SHORT:
			return (unsigned int)m_shortValue;
		case DBVT_USHORT:
			return (unsigned int)m_ushortValue;
		case DBVT_LONG:
			return (unsigned int)m_longValue;
		case DBVT_ULONG:
			return (unsigned int)m_ulongValue;
		case DBVT_FLOAT:
			return (unsigned int)m_floatValue;
		case DBVT_DOUBLE:
			return (unsigned int)m_doubleValue;
		case DBVT_DATE:
			_ASSERT( false );
		case DBVT_STRING:
#ifdef UNICODE
			return (unsigned int)_wtoi( &m_strString->at(0) );
#else
			return (unsigned int)atoi( &m_strString->at(0) );
#endif
		default:
			_ASSERT( false );
	}

	return 0;
}

signed long MDBField::AsLong()	const
{
	if( IsNull() )
		return 0;

	switch( m_nType )
	{
		case DBVT_NULL:
			return 0;
		case DBVT_BOOL:
			return m_boolValue ? 1 : 0;
		case DBVT_CHAR:
			return (signed long)m_charValue;
		case DBVT_UCHAR:
			return (signed long)m_ucharValue;
		case DBVT_SHORT:
			return (signed long)m_shortValue;
		case DBVT_USHORT:
			return (signed long)m_ushortValue;
		case DBVT_LONG:
			return m_longValue;
		case DBVT_ULONG:
			return (signed long)m_ulongValue;
		case DBVT_FLOAT:
			return (signed long)m_floatValue;
		case DBVT_DOUBLE:
			return (signed long)m_doubleValue;
		case DBVT_DATE:
			_ASSERT( false );
		case DBVT_STRING:
#ifdef UNICODE
			return (signed long)_wtoi( &m_strString->at(0) );
#else
			return (signed long)atoi( &m_strString->at(0) );
#endif
		default:
			_ASSERT( false );
	}

	return 0;
}

unsigned long MDBField::AsULong()	const
{
	if( IsNull() )
		return 0;

	switch( m_nType )
	{
		case DBVT_NULL:
			return 0;
		case DBVT_BOOL:
			return m_boolValue ? 1 : 0;
		case DBVT_CHAR:
			return (unsigned long)m_charValue;
		case DBVT_UCHAR:
			return (unsigned long)m_ucharValue;
		case DBVT_SHORT:
			return (unsigned long)m_shortValue;
		case DBVT_USHORT:
			return (unsigned long)m_ushortValue;
		case DBVT_LONG:
			return (unsigned long)m_longValue;
		case DBVT_ULONG:
			return m_ulongValue;
		case DBVT_FLOAT:
			return (unsigned long)m_floatValue;
		case DBVT_DOUBLE:
			return (unsigned long)m_doubleValue;
		case DBVT_DATE:
			_ASSERT( false );
		case DBVT_STRING:
#ifdef UNICODE
			return (unsigned long)_wtoi( &m_strString->at(0) );
#else
			return (unsigned long)atoi( &m_strString->at(0) );
#endif
		default:
			_ASSERT( false );
	}

	return 0;
}

float MDBField::AsFloat() const
{
	if( IsNull() )
		return 0;

	switch( m_nType )
	{
		case DBVT_NULL:
			return 0;
		case DBVT_BOOL:
			return m_boolValue ? 1.0f : 0.0f;
		case DBVT_CHAR:
			return (float)m_charValue;
		case DBVT_UCHAR:
			return (float)m_ucharValue;
		case DBVT_SHORT:
			return (float)m_shortValue;
		case DBVT_USHORT:
			return (float)m_ushortValue;
		case DBVT_LONG:
			return (float)m_longValue;
		case DBVT_ULONG:
			return (float)m_ulongValue;
		case DBVT_FLOAT:
			return (float)m_floatValue;
		case DBVT_DOUBLE:
			return (float)m_doubleValue;
		case DBVT_DATE:
			_ASSERT( false );
		case DBVT_STRING:
#ifdef UNICODE
			return (float)_wtoi( &m_strString->at(0) );
#else
			return (float)atoi( &m_strString->at(0) );
#endif
		default:
			_ASSERT( false );
	}

	return 0.0f;
}

double MDBField::AsDouble()	const
{
	if( IsNull() )
		return 0;

	switch( m_nType )
	{
		case DBVT_NULL:
			return 0;
		case DBVT_BOOL:
			return m_boolValue ? 1 : 0;
		case DBVT_CHAR:
			return (double)m_charValue;
		case DBVT_UCHAR:
			return (double)m_ucharValue;
		case DBVT_SHORT:
			return (double)m_shortValue;
		case DBVT_USHORT:
			return (double)m_ushortValue;
		case DBVT_LONG:
			return (double)m_longValue;
		case DBVT_ULONG:
			return (double)m_ulongValue;
		case DBVT_FLOAT:
			return (double)m_floatValue;
		case DBVT_DOUBLE:
			return (double)m_doubleValue;
		case DBVT_DATE:
			_ASSERT( false );
		case DBVT_STRING:
#ifdef UNICODE
			return (double)_wtoi( &m_strString->at(0) );
#else
			return (double)atoi( &m_strString->at(0) );
#endif
		default:
			_ASSERT( false );
	}

	return 0.0f;
}

MDBDateTime MDBField::AsDate()	const
{
	return MDBDateTime();
}