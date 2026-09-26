// cl: /Iinputs/reference/shims/stringinline
// Open-BFME: STLport hash_map index for the Rva0045EF90Object value.
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "StringInline.h"

class Rva0045EF90Base
{
public:
	Rva0045EF90Base() : m_value( -1 ) {}
	Rva0045EF90Base( const Rva0045EF90Base &source ) : m_value( source.m_value ) {}
	virtual ~Rva0045EF90Base();

private:
	unsigned m_value;
};

class Rva0045EF90Object : public Rva0045EF90Base
{
public:
	Rva0045EF90Object();
	Rva0045EF90Object( const Rva0045EF90Object &source );
	virtual ~Rva0045EF90Object();

private:
	AsciiString m_first;
	AsciiString m_second;
	unsigned m_handle;
	float m_value14;
	float m_value18;
	float m_value1c;
	float m_value20;
	unsigned char m_value24;
	unsigned char m_padding25[ 3 ];
	AsciiString m_last;
};

Rva0045EF90Object::Rva0045EF90Object()
	: Rva0045EF90Base()
	, m_first()
	, m_second()
	, m_handle( 0 )
	, m_value24( 0 )
	, m_last()
{
	m_value14 = -1.0f;
	m_value18 = -1.0f;
	m_value1c = -1.0f;
	m_value20 = -1.0f;
}

namespace rts
{
	template <class T> struct hash
	{
		unsigned int operator()( T value ) const;
	};

	template <class T> struct equal_to
	{
		bool operator()( const T &left, const T &right ) const;
	};
}

typedef _STL::hash_map<AsciiString, Rva0045EF90Object,
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > Rva00461BF0Map;

template Rva0045EF90Object &Rva00461BF0Map::operator[]( const AsciiString &key );
