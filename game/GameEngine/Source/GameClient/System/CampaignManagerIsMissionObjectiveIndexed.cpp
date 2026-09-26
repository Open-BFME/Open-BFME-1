// ?isMissionObjectiveIndexed@CampaignManager@@QAEEH@Z
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

extern "C" void _ReadWriteBarrier( void );
#pragma intrinsic(_ReadWriteBarrier)

struct Rva003BDF70Span
{
	void **m_begin;
	void **m_end;
	int size() const { return m_end - m_begin; }
};

#include "ascii_string.h"

class LivingWorldRegion
{
public:
	char m_pad00[ 0x54 ];
	Rva003BDF70Span m_first;
	char m_pad5C[ 0x4 ];
	Rva003BDF70Span m_second;
};

class LivingWorldRegionManager
{
public:
	LivingWorldRegion *rva003C8A50( const AsciiString &key );
};

static __forceinline int isInSecondSpan( const LivingWorldRegion *found, unsigned index )
{
	unsigned first = (unsigned)found->m_first.size();
	if ( index < first )
	{
		_ReadWriteBarrier();
		return 0;
	}

	unsigned second = (unsigned)found->m_second.size();
	unsigned total = first + second;
	if ( index < total )
	{
		_ReadWriteBarrier();
		return 1;
	}
	_ReadWriteBarrier();
	return 0;
}

class CampaignManager
{
public:
	unsigned char isMissionObjectiveIndexed( int index );

private:
	char m_pad00[ 0x28 ];
	LivingWorldRegionManager *m_resolver;
	char m_pad2C[ 0x4 ];
	AsciiString m_key;
};

unsigned char CampaignManager::isMissionObjectiveIndexed( int index )
{
	LivingWorldRegionManager *resolver = m_resolver;
	if ( resolver )
	{
		int idx = index;
		if ( idx >= 0 )
		{
			LivingWorldRegion *found = resolver->rva003C8A50( m_key );
			if ( found )
				return isInSecondSpan( found, (unsigned)idx );
		}
	}
	return 0;
}
