// cl: /MD /ICode/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

struct Rva0075E980StringRecord
{
	unsigned int m_word0;
	unsigned int m_word4;
	unsigned int m_word8;
	AsciiString m_string;

	Rva0075E980StringRecord &operator=( const Rva0075E980StringRecord &src );
};

Rva0075E980StringRecord &Rva0075E980StringRecord::operator=( const Rva0075E980StringRecord &src )
{
	m_word0 = src.m_word0;
	m_word4 = src.m_word4;
	m_word8 = src.m_word8;
	m_string = src.m_string;
	return *this;
}

struct Rva00764790StringRecord
{
	unsigned int m_word0;
	unsigned int m_word4;
	unsigned int m_word8;
	AsciiString m_string;

	Rva00764790StringRecord( const Rva00764790StringRecord &src );
};

Rva00764790StringRecord::Rva00764790StringRecord( const Rva00764790StringRecord &src )
	: m_word0( src.m_word0 ),
	  m_word4( src.m_word4 ),
	  m_word8( src.m_word8 ),
	  m_string( src.m_string )
{
}
