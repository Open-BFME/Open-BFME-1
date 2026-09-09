// cl: /DNDEBUG /MD /O2 /EHsc /Ireference/shims/stringinline
// The load-game fade callback queues the defeated-mission world-text event.
// Rva00612160Post.cpp names this callback and passes its address to the fade
// operation queue.  The retail body also clears the active region state when
// its lookup finds a completed region.

#include "StringInline.h"

typedef bool Bool;

void * __cdecl operator new( unsigned int size );

class BfmeHost961
{
public:
	void bfmeFallback961( int first, int second );
};

class BfmeGameLogic
{
};

extern BfmeGameLogic *TheBfmeGameLogic;

class LivingWorldRegion
{
public:
	char m_pad00[ 0x84 ];
	unsigned char m_ready;
	char m_pad85[ 0x17 ];
	int m_begin;
	int m_end;
};

class LivingWorldRegionManager
{
public:
	LivingWorldRegion *rva003C8A50( const AsciiString &regionName );
	char m_pad00[ 0x10 ];
	unsigned char m_active;
};

class Glo012F1028Type
{
public:
	char m_pad00[ 0x28 ];
	LivingWorldRegionManager *m_regionManager;
	char m_pad2c[ 4 ];
	AsciiString m_currentRegionName;

};

extern Glo012F1028Type *Glo012F1028;

class BfmeLivingWorldCampaignManager
{
public:
	char m_pad00[ 0x1c ];
	Bool m_evilCampaign;
};

extern BfmeLivingWorldCampaignManager *TheLivingWorldCampaignManager;

class BfmeBaseVNH
{
public:
	BfmeBaseVNH( unsigned width, char flag );
	virtual ~BfmeBaseVNH();
	virtual void handle();
	unsigned m_width;
	char m_flag;
	char m_pad09[ 3 ];
	};

class BfmeRectVNH : public BfmeBaseVNH
{
public:
	BfmeRectVNH( unsigned width, const AsciiString &text, char flag );
	AsciiString m_text;
};

#pragma comment(linker, "/alternatename:?rva003C8A50@LivingWorldRegionManager@@QAEPAVLivingWorldRegion@@ABVAsciiString@@@Z=?j_0002bf0d@@YAXXZ")

class Rva003C2280Item
{
public:
	char m_pad00[ 8 ];
	bool m_flag;
};

class Rva003C2280Owner
{
public:
	void append( const Rva003C2280Item *item );
};

extern void b_003c48e0();

class Rva003C48E0Call
{
public:
	void clear();
};

static __forceinline void clearRegion( Glo012F1028Type *owner )
{
	typedef void (Rva003C48E0Call::*Function)();
	union
	{
		void (*raw)(void);
		Function member;
	} fn;
	fn.raw = b_003c48e0;
	(reinterpret_cast<Rva003C48E0Call *>(owner)->*fn.member)();
}

__forceinline BfmeRectVNH *makeDelayedWorldTextEvent(
	unsigned delay, const char *text )
{
	return new BfmeRectVNH( delay, AsciiString( text ), 0 );
}

// ?fade0060F010@@YAIM_N@Z
unsigned fade0060F010( float, Bool )
{
	AsciiString regionName( Glo012F1028->m_currentRegionName );
	LivingWorldRegion *lookup = Glo012F1028->m_regionManager != 0
		? Glo012F1028->m_regionManager->rva003C8A50( regionName ) : 0;
	void *region = lookup;

	((BfmeHost961 *)TheBfmeGameLogic)->bfmeFallback961( 0, 0 );

	if( region != 0 )
	{
		LivingWorldRegion *found = (LivingWorldRegion *)region;
		if( (found->m_end - found->m_begin) / 36 != 0 ||
			found->m_ready != 0 )
		{
			clearRegion( Glo012F1028 );
			LivingWorldRegionManager *manager =
				Glo012F1028->m_regionManager;
			manager->m_active = 1;
		}
	}

	if( TheLivingWorldCampaignManager != 0 )
	{
		if( TheLivingWorldCampaignManager->m_evilCampaign )
			region = makeDelayedWorldTextEvent( 2,
				"LW:DefeatedMissionTextEvil" );
		else
			region = makeDelayedWorldTextEvent( 2,
				"LW:DefeatedMissionTextGood" );
		((Rva003C2280Owner *)Glo012F1028)->append(
			(const Rva003C2280Item *)region );
	}

	return 3;
}
