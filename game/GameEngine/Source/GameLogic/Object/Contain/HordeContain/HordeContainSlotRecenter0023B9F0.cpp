// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Recenter the slot positions around a selected slot or their mean.
// Evidence: targets/game/reverse/identity_evidence/0023b9f0-recenter.md
typedef int Int;
typedef unsigned int UnsignedInt;

#include "ascii_string.h"

class ThingTemplate
{
public:
	char m_bfmeHead[ 0xc8 ];
	UnsignedInt m_kindof;
};

class ThingFactory;

// The existing retail lookup body at RVA00137E80, reached via ILT00028560.
class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate( const AsciiString &name );
};

extern ThingFactory *TheThingFactory;

struct BfmeHordeInner12
{
	// Only the twelve-byte stride is consumed here; these words stay opaque.
	UnsignedInt a, b, c;
};

class BfmeHordeInnerVec
{
public:
	UnsignedInt size( void ) const { return (UnsignedInt)( m_end - m_begin ); }

	BfmeHordeInner12 *m_begin;
	BfmeHordeInner12 *m_end;
	BfmeHordeInner12 *m_capacity;
};

class BfmeHordeRosterEntry
{
public:
	UnsignedInt m_bfmeKey;
	AsciiString m_name;
	BfmeHordeInnerVec m_bfmeInner;
};

class BfmeHordeRosterVec
{
public:
	UnsignedInt size( void ) const { return (UnsignedInt)( m_end - m_begin ); }
	BfmeHordeRosterEntry *operator[]( UnsignedInt i ) const { return m_begin[ i ]; }

	BfmeHordeRosterEntry **m_begin;
	BfmeHordeRosterEntry **m_end;
	BfmeHordeRosterEntry **m_capacity;
};

class BfmeHordeRosterOwner
{
public:
	char m_bfmeHead[ 0x224 ];
	BfmeHordeRosterVec m_bfmeRoster;
};

struct BfmeHordePosition0023B9F0
{
	float m_x, m_y;

	BfmeHordePosition0023B9F0 &operator-=( const BfmeHordePosition0023B9F0 &other )
	{
		m_x -= other.m_x;
		m_y -= other.m_y;
		return *this;
	}
};

struct BfmeHordeSlot
{
	UnsignedInt m_bfmeKey;
	BfmeHordePosition0023B9F0 m_position;
	float m_bfmeW;
};

class BfmeHordeContainRoster
{
public:
	void rva0023B9F0( void );

private:
	char m_bfmeHead[ 4 ];
	BfmeHordeRosterOwner *m_bfmeOwner;
	char m_bfmeGap[ 0x12c - 0x08 ];
	BfmeHordeSlot *m_bfmeSlotBegin;
	BfmeHordeSlot *m_bfmeSlotEnd;
};

// ?rva0023B9F0@BfmeHordeContainRoster@@QAEXXZ
void BfmeHordeContainRoster::rva0023B9F0( void )
{
	BfmeHordeRosterOwner *owner = m_bfmeOwner;

	BfmeHordeRosterVec &roster = owner->m_bfmeRoster;

	Int total = -1;
	Int count = 0;
	for ( UnsignedInt i = 0; i < roster.size(); ++i )
	{
		const ThingTemplate *thingTemplate = reinterpret_cast<BfmeThingFactory *>(TheThingFactory)->findTemplate( roster[ i ]->m_name );
		if ( thingTemplate && ( thingTemplate->m_kindof & 0x0800 ) )
		{
			total = count;
			break;
		}

		count += roster[ i ]->m_bfmeInner.size();
	}

	Int cnt = 0;
	Int idx = 0;
	BfmeHordeSlot *begin = m_bfmeSlotBegin;
	BfmeHordePosition0023B9F0 center;
	float &sumX = center.m_x;
	float &sumY = center.m_y;
	sumX = 0.0f;
	BfmeHordeSlot *end = m_bfmeSlotEnd;
	sumY = 0.0f;

	for ( BfmeHordeSlot *slot = begin; slot != end; ++slot )
	{
		sumX += slot->m_position.m_x;
		++cnt;
		sumY += slot->m_position.m_y;
		if ( idx == total )
		{
			center = slot->m_position;
			cnt = 1;
			break;
		}
		++idx;
	}

	if ( cnt != 0 )
	{
		float inv = 1.0f / (float)cnt;
		sumX *= inv;
		sumY *= inv;
	}

	begin = m_bfmeSlotBegin;
	for ( BfmeHordeSlot *slot = begin; slot != m_bfmeSlotEnd; ++slot )
	{
		slot->m_position -= center;
	}
}
