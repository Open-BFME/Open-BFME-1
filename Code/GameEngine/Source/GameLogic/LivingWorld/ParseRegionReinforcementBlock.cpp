// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// Open-BFME7: ParseRegionReinforcementBlock (retail 0x003BABE0 157 B; a gap claimed through its
// own exception text).  With no INI or instance it throws INIException(3
// "ParseRegionReinforcementBlock::Invalid data passed in."); otherwise a 0x24-byte record built by
// the out-of-line constructor at 0x003BAB40 is filled through
// INI::initFromINI with the table at VA 0x010ED6A0 handed to the
// instance's append routine (0x003B25D0) and destroyed by the out-of-line
// destructor at 0x003BA580.  Address-derived names.

#define _STLP_NO_EXCEPTIONS 1
#include <new>
#include <vector>

#include "string_base.h"

extern "C" int __cdecl memcmp( const void *, const void *, unsigned int );
#pragma intrinsic(memcmp)

class AsciiString
{
public:
	static const AsciiString TheEmptyString;

	AsciiString( const AsciiString &other )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}

	const char *str() const
	{
		return m_text ? m_text + 8 : (const char *)0x0107388B;
	}

	int getLength() const
	{
		return m_text ? *(const unsigned short *)( m_text + 4 ) : 0;
	}

	int compare( const AsciiString &other ) const
	{
		int otherLength = other.getLength();
		const char *otherData = other.str();
		int thisLength = getLength();
		const char *thisData = str();
		int count = thisLength < otherLength ? thisLength : otherLength;
		int result = memcmp( thisData, otherData, count );
		if( result != 0 )
			return result;
		return thisLength - otherLength;
	}
	~AsciiString();

private:
	char *m_text;
};

// The record's range member is the ordinary three-pointer STLport vector.
// Retail nevertheless reaches the shared range-cleanup ILT 0x00024C17 from
// this constructor; this ABI view keeps that call's already-proven parameter
// order without claiming a second vector implementation.
class Rva003BA9C0Range
{
public:
	void assign( void *first, void *last );

	void *volatile m_start;
	void *volatile m_finish;
	void *m_end;
};

namespace _STL
{
template <class T>
class allocator
{
};

template <class T, class A = allocator<T> >
class vector
{
public:
	vector()
	{
		m_start = 0;
		m_finish = 0;
		m_end = 0;
	}
	vector( const vector &other );
	~vector();

private:
	T *volatile m_start;
	T *volatile m_finish;
	T *m_end;
};
}

typedef int Int;

struct FieldParse;

class INIException
{
public:
	INIException( Int code, const char *msg, ... );
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_msg;
};

class INI
{
public:
	void initFromINI( void *what, const FieldParse *parseTable );
};

class Rva003BABE0Record
{
public:
	Rva003BABE0Record();
	Rva003BABE0Record( const Rva003BABE0Record &other );
	virtual ~Rva003BABE0Record();
	__declspec( noinline ) AsciiString getRegionName();

private:
	AsciiString m_regionName;
	_STL::vector<AsciiString> m_addReinforcementArmy;
	Int m_closeDistanceTime;
	Int m_mediumDistanceTime;
	Int m_farDistanceTime;
	bool m_pathFindRuleAllRegions;
	bool m_pathFindRulePlayerOwned;
	bool m_autoSummon;
};

typedef char Rva003BABE0RecordSizeMustBe24[
	sizeof( Rva003BABE0Record ) == 0x24 ? 1 : -1];

inline bool operator==( const AsciiString &left, const AsciiString &right )
{
	return left.compare( right ) == 0;
}

AsciiString Rva003BABE0Record::getRegionName()
{
	return m_regionName;
}

namespace _STL
{
struct __false_type
{
};

template <> class vector<Rva003BABE0Record,
	allocator<Rva003BABE0Record> >
{
public:
	Rva003BABE0Record *begin() const
	{
		return m_start;
	}

	Rva003BABE0Record *finish() const
	{
		return m_finish;
	}

	Rva003BABE0Record *end_of_storage() const
	{
		return m_end_of_storage;
	}

	unsigned int size() const
	{
		return (unsigned int)( m_finish - m_start );
	}

	void _M_insert_overflow( Rva003BABE0Record *position,
		const Rva003BABE0Record &value, const __false_type &, unsigned int fillLength,
		bool atEnd );

	Rva003BABE0Record *m_start;
	Rva003BABE0Record *m_finish;
	Rva003BABE0Record *m_end_of_storage;
};
}

// ??0Rva003BABE0Record@@QAE@XZ
Rva003BABE0Record::Rva003BABE0Record()
	: m_regionName( AsciiString::TheEmptyString ),
	  m_closeDistanceTime( 0 ),
	  m_mediumDistanceTime( 0 ),
	  m_farDistanceTime( 0 ),
	  m_pathFindRuleAllRegions( false ),
	  m_pathFindRulePlayerOwned( false ),
	  m_autoSummon( false )
{
	Rva003BA9C0Range *range =
		reinterpret_cast<Rva003BA9C0Range *>( &m_addReinforcementArmy );
	void *last = range->m_finish;
	void *first = range->m_start;
	range->assign( first, last );
}

Rva003BABE0Record::Rva003BABE0Record( const Rva003BABE0Record &other )
	: m_regionName( other.m_regionName ),
	  m_addReinforcementArmy( other.m_addReinforcementArmy )
{
	m_closeDistanceTime = other.m_closeDistanceTime;
	m_mediumDistanceTime = other.m_mediumDistanceTime;
	m_farDistanceTime = other.m_farDistanceTime;
	m_pathFindRuleAllRegions = other.m_pathFindRuleAllRegions;
	m_pathFindRulePlayerOwned = other.m_pathFindRulePlayerOwned;
	m_autoSummon = other.m_autoSummon;
}

extern const FieldParse Rva003BABE0RecordFieldParseTable[];

class Rva003BABE0Owner
{
public:
	void append( Rva003BABE0Record *record );
};

// ?append@Rva003BABE0Owner@@QAEXPAVRva003BABE0Record@@@Z
void Rva003BABE0Owner::append( Rva003BABE0Record *record )
{
	_STL::vector<Rva003BABE0Record> &records =
		*reinterpret_cast<_STL::vector<Rva003BABE0Record> *>(
			reinterpret_cast<char *>( this ) + 0x60 );
	for( unsigned int index = 0; index < records.size(); ++index )
	{
		if( records.begin()[ index ].getRegionName() == record->getRegionName() )
			return;
	}

	if( records.m_finish != records.m_end_of_storage )
	{
		Rva003BABE0Record *finish = records.m_finish;
		new ( finish ) Rva003BABE0Record( *record );
		++records.m_finish;
	}
	else
	{
		records._M_insert_overflow( records.m_finish, *record,
			reinterpret_cast<const _STL::__false_type &>( record ), 1, true );
	}
}

// ?ParseRegionReinforcementBlock@@YAXPAVINI@@PAX1PBX@Z
void ParseRegionReinforcementBlock( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva003BABE0Record record;
		ini->initFromINI( &record, Rva003BABE0RecordFieldParseTable );
		((Rva003BABE0Owner *)instance)->append( &record );
	}
	else
		throw INIException( 3, "ParseRegionReinforcementBlock::Invalid data passed in." );
}
