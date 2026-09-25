// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

// S4SortElem8::BfmeLess00574AA0, retail 0x00574AA0, 224 bytes.
// The score-row STLport sort layer (__median 0x005755A0, __introsort_loop
// 0x00577760, __unguarded_partition 0x00575620, __adjust_heap 0x005757E0)
// calls this element comparison through ILT 0x00013471. Order: bit 25 of the
// word at record+0xD0 first, then the army int at +0x44 descending, then the
// army names ascending (getName ILT 0x000041D3, compare ILT 0x000220C5).

#include "ascii_string.h"

class LivingWorldArmy
{
public:
	AsciiString getName() const;

	char m_unmodelled00[ 0x44 ];
	int m_field44;
};

struct Rva00574AA0Bits
{
	unsigned int m_bits;

	bool test( int bit ) const { return ( m_bits & ( 1 << bit ) ) != 0; }
};

class Rva00574AA0Record
{
public:
	// Retail keeps the loaded word and re-shifts it for the result instead of
	// reusing the compare's shift: the result reads a by-value copy.
	Rva00574AA0Bits getFlagsD0() const { return m_flagsD0; }

	char m_unmodelled00[ 0xD0 ];
	Rva00574AA0Bits m_flagsD0;
};

struct S4SortElem8
{
	LivingWorldArmy *m_army;
	Rva00574AA0Record *m_record;

	bool BfmeLess00574AA0( const S4SortElem8 &other ) const;
};

bool S4SortElem8::BfmeLess00574AA0( const S4SortElem8 &other ) const
{
	if ( m_record->m_flagsD0.test( 25 ) != other.m_record->m_flagsD0.test( 25 ) )
		return m_record->getFlagsD0().test( 25 );
	int leftKey = m_army->m_field44;
	int rightKey = other.m_army->m_field44;
	if ( leftKey != rightKey )
		return leftKey > rightKey;
	return m_army->getName().compare( other.m_army->getName() ) < 0;
}
