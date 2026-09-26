// cl: /MD /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

struct Rva00473400StringRecord
{
	unsigned int m_word0;
	unsigned int m_word4;
	unsigned int m_word8;
	AsciiString m_string;

	Rva00473400StringRecord &operator=( const Rva00473400StringRecord &src );
};

Rva00473400StringRecord &Rva00473400StringRecord::operator=( const Rva00473400StringRecord &src )
{
	m_word0 = src.m_word0;
	m_word4 = src.m_word4;
	m_word8 = src.m_word8;
	m_string = src.m_string;
	return *this;
}

struct Rva004739F0StringRecord
{
	unsigned int m_word0;
	unsigned int m_word4;
	unsigned int m_word8;
	AsciiString m_string;

	Rva004739F0StringRecord( const Rva004739F0StringRecord &src );
};

Rva004739F0StringRecord::Rva004739F0StringRecord( const Rva004739F0StringRecord &src )
	: m_word0( src.m_word0 ),
	  m_word4( src.m_word4 ),
	  m_word8( src.m_word8 ),
	  m_string( src.m_string )
{
}
