// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Rva003BA500 ctor, retail 0x003BA9C0, 102 bytes.
// Same vtable 0x010ED46C as ??1Rva003BA500. Zeros scalars, builds the
// +0x0C range member, then range-assigns start/finish (ILT 0x00024C17).
#include "string_base.h"

class AsciiString : private StringBase<char>
{
public:
	static void copy( void *destination, const void *source )
	{
		((StringBase<char> *)destination)->StringBase<char>::StringBase(
			*(const StringBase<char> *)source);
	}
};

class Rva003BA9C0Str
{
public:
	Rva003BA9C0Str()
	{
		m_buf = 0;
	}
	Rva003BA9C0Str( const Rva003BA9C0Str &other )
	{
		AsciiString::copy( this, &other );
	}
	~Rva003BA9C0Str();

	char *m_buf;
};

struct BfmeLegendStringVec
{
public:
	BfmeLegendStringVec()
	{
		m_start = 0;
		m_finish = 0;
		m_end = 0;
	}
	BfmeLegendStringVec( const BfmeLegendStringVec &other );
	~BfmeLegendStringVec();
	void assign( void *first, void *last );

	void *volatile m_start;
	void *volatile m_finish;
	void *m_end;
};

#pragma comment(linker, "/alternatename:??0BfmeLegendStringVec@@QAE@ABU0@@Z=?j_00015474@@YAXXZ")

class Rva003BA9C0Range
{
public:
	void assign( void *first, void *last );

	void *volatile m_start;
	void *volatile m_finish;
};

class Rva003BA500
{
public:
	__declspec( noinline ) Rva003BA500();
	Rva003BA500( const Rva003BA500 &other );
	virtual void handle();

private:
	Rva003BA9C0Str m_at04;
	int m_at08;
	BfmeLegendStringVec m_at0C;
	bool m_at18;
	char m_pad19[ 3 ];
	Rva003BA9C0Str m_at1C;
	int m_at20;
};

// ??0Rva003BA500@@QAE@XZ
Rva003BA500::Rva003BA500()
	: m_at08( 0 ), m_at18( false ), m_at20( 0 )
{
	Rva003BA9C0Range *p = (Rva003BA9C0Range *)&m_at0C;
	void *last = p->m_finish;
	void *first = p->m_start;
	p->assign( first, last );
}

// ??0Rva003BA500@@QAE@ABV0@@Z
Rva003BA500::Rva003BA500( const Rva003BA500 &other )
	: m_at04( other.m_at04 ), m_at08( other.m_at08 ), m_at0C( other.m_at0C ),
	  m_at18( other.m_at18 ), m_at1C( other.m_at1C ), m_at20( other.m_at20 )
{
}
