// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned char Bool;

#include "string_base.h"

struct Rva00360820Destination
{
	UnsignedInt m_first;
	UnsignedInt m_count;
	UnsignedInt m_second;
	UnsignedInt m_third;
	Bool m_active;
	StringBase<unsigned short> m_text;
};

struct Rva00360820Source
{
	UnsignedByte m_pad0[0x3c];
	UnsignedInt m_first;
	UnsignedByte m_pad40[4];
	UnsignedInt m_second;
	UnsignedInt m_third;
	UnsignedByte m_pad4c[0x2c];
	StringBase<unsigned short> m_text;
};

void rva00360820CopyInit(Rva00360820Destination *destination,
	const Rva00360820Source *source)
{
	destination->m_first = source->m_first;
	// Retail calls StringBase<unsigned short>::set (0x00888530), not
	// UnicodeString::operator= (0x00888A90).
	destination->m_text.set(source->m_text);
	destination->m_second = source->m_second;
	destination->m_third = source->m_third;
	destination->m_count = 0;
	destination->m_active = 0;
}
