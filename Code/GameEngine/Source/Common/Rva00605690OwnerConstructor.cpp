// The still-dump caller at 0x006059F0 is the only function that calls retail
// body 0x00605690. Retail calls StringBase<char>'s copy constructor at
// 0x00887B60 and clears 40-byte regions at this+0x0c and this+0x34.
// Neither the caller nor a vtable names the owner, so the class keeps the RVA
// 0x00605690 in its name. Volatile scalar members reproduce retail's store
// order after it clears both zero registers.
// cl: /O2 /Ob1 /ICode/Libraries/Source/WWVegas/WWLib

#include <string.h>

#define private public
#include "string_base.h"
#undef private

// This address-derived wrapper has the same four-byte layout as StringBase<char>.
class Rva00605690CharPart
{
public:
	__forceinline Rva00605690CharPart(
		const Rva00605690CharPart &other )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other );
	}

private:
	char *m_storage;
};

class Rva00605690Owner
{
public:
	Rva00605690Owner(
		const Rva00605690CharPart &part, int kind );

private:
	Rva00605690CharPart m_opaque00;
	volatile int m_4;
	volatile int m_8;
	int m_c[ 10 ];
	int m_34[ 10 ];
	volatile unsigned char m_5c;
};

Rva00605690Owner::Rva00605690Owner(
	const Rva00605690CharPart &part, int kind )
	: m_opaque00( part ), m_4( 0 ), m_8( kind )
{
	memset( m_c, 0, sizeof( m_c ) );
	memset( m_34, 0, sizeof( m_34 ) );
	m_5c = 0;
}

typedef char Rva00605690OwnerSizeCheck[
	( sizeof( Rva00605690Owner ) == 0x60 ) ? 1 : -1 ];
