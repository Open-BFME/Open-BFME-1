// ?append@Rva003BABE0Owner@@QAEXPAVRva003BABE0Record@@@Z
// partial score=0.98 date=2026-09-20
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// Open-BFME7: the region reinforcement append routine at retail 0x003B25D0.
// ParseRegionReinforcementBlock proves the owner and record relationship. The
// record getter and vector overflow call use the retail ILTs recovered from
// the two calls in this body.

#include <new>
#include "string_base.h"

extern "C" int __cdecl memcmp( const void *, const void *, unsigned int );
#pragma intrinsic(memcmp)

class AsciiString
{
public:
	AsciiString( const AsciiString &other )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
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

private:
	char *m_text;
};

inline bool operator==( const AsciiString &left, const AsciiString &right )
{
	return left.compare( right ) == 0;
}

class Rva003BABE0Record
{
public:
	__declspec( noinline ) AsciiString getRegionName();
	Rva003BABE0Record( const Rva003BABE0Record &other );
	virtual ~Rva003BABE0Record();

private:
	AsciiString m_regionName;
	char m_tail[ 0x1C ];
};

typedef char Rva003BABE0RecordSizeMustBe24[
	sizeof( Rva003BABE0Record ) == 0x24 ? 1 : -1];

// The method is the same return-by-value shape as the retail body reached by
// the 0x0001073F ILT. The source record only exposes its name at offset +4.
AsciiString Rva003BABE0Record::getRegionName()
{
	return m_regionName;
}

namespace _STL
{
struct __false_type
{
};

template <class T>
class allocator
{
};

template <class T, class A = allocator<T> >
class vector
{
public:
	T *begin() const
	{
		return m_start;
	}

	T *finish() const
	{
		return m_finish;
	}

	T *end_of_storage() const
	{
		return m_end_of_storage;
	}

	unsigned int size() const
	{
		return (unsigned int)( m_finish - m_start );
	}

	void _M_insert_overflow( T *position, const T &value,
		const __false_type &, unsigned int fillLength, bool atEnd );

	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
};
}

class Rva003BABE0Owner
{
private:
	char m_prefix[ 0x60 ];
	_STL::vector<Rva003BABE0Record> m_records;

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

	Rva003BABE0Record *finish = records.finish();
	if( finish != records.end_of_storage() )
	{
		new ( finish ) Rva003BABE0Record( *record );
		++records.m_finish;
	}
	else
	{
		records._M_insert_overflow( records.m_finish, *record,
			reinterpret_cast<const _STL::__false_type &>( record ), 1, true );
	}
}
