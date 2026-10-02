// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Two unclaimed Apt string comparisons over the 8-byte string header seen in
// ValuePredicates008C4940.cpp's StringEqual008C49E0 (refs, length, capacity,
// flags, then the characters):
//
//   0x00891BD0 (56 bytes)  equal when the lengths match and either the data
//                          blocks are the same or the characters compare equal
//                          (inlined memcmp: repe cmpsb over `length` bytes)
//   0x008AC020 (83 bytes)  the negation of the same test, inlined
//
// Each sat alone in a .text gap no ledger row covered: 16-byte-aligned start
// after an int3 pad run, ret 4 followed by int3 padding, and no call, ILT
// stub, table slot, code immediate, pin or dir32 name at the address.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#include <string.h>
#pragma intrinsic( memcmp )

struct Rva00891BD0StringData
{
	unsigned short refs;
	unsigned short length;
	unsigned short capacity;
	unsigned short flags;
};

class Rva00891BD0String
{
public:
	bool equals( const Rva00891BD0String &other ) const;
	bool differs( const Rva00891BD0String &other ) const;

	inline bool same( const Rva00891BD0String &other ) const
	{
		int length = m_data->length;
		if ( length != (int)other.m_data->length )
			return false;
		if ( m_data == other.m_data )
			return true;
		return memcmp( m_data + 1, other.m_data + 1, length ) == 0;
	}

	Rva00891BD0StringData *m_data;
};

bool Rva00891BD0String::equals( const Rva00891BD0String &other ) const
{
	return same( other );
}

bool Rva00891BD0String::differs( const Rva00891BD0String &other ) const
{
	return !same( other );
}
