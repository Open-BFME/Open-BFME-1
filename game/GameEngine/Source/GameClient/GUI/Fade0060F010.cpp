// cl: /DNDEBUG /MD /O2 /EHsc /Iinputs/reference/shims/stringinline
// The load-game fade callback queues the defeated-mission world-text event.
// Rva00612160Post.cpp names this callback and passes its address to the fade
// operation queue.  The retail body also clears the active region state when
// its lookup finds a completed region.

#include "StringInline.h"
#include "../../Common/System/xfer.h"

typedef bool Bool;

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

void * __cdecl operator new( unsigned int size );

class BfmeHost961
{
public:
	void bfmeFallback961( int first, int second );
};

class GameLogic
{
public:
	int rva0002615c(Xfer *xfer);
};

extern GameLogic *TheBfmeGameLogic;
extern void j_0002615c();

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

class Rva003C48E0XferInterface
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void transfer(Xfer *xfer);
};

class Rva003C48E0PrimaryBase
{
public:
	virtual void primary0();
	char m_pad04[4];
};

class BfmeLivingWorldCampaignManager : public Rva003C48E0PrimaryBase,
	public Rva003C48E0XferInterface
{
public:
	char m_pad0C[ 0x10 ];
	Bool m_evilCampaign;
};

extern BfmeLivingWorldCampaignManager *TheLivingWorldCampaignManager;

class BfmeGameCW : public Rva003C48E0PrimaryBase,
	public Rva003C48E0XferInterface
{
};

extern BfmeGameCW *g_bfmeGameCW;

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

class File
{
public:
	virtual ~File();
};
extern File *createMemoryReadFile( char *data, int size );

class Gen009D8CA0 : public Xfer
{
public:
	Gen009D8CA0( int first, int second, int third );
	virtual ~Gen009D8CA0();
	bool readAt009D89E0( File *file, void *output );

private:
	int m_first;
	int m_third;
	int m_second;
	bool m_flag;
	unsigned char m_pad[3];
	int m_valueA;
	int m_valueB;
	int m_index;
};

class Rva009D8AA0
{
public:
	void apply();
};

struct Gen003BDC50CallPairBase
{
	Gen003BDC50CallPairBase() {}
	Gen003BDC50CallPairBase( const Gen003BDC50CallPairBase &other ) :
		m_a( other.m_a ), m_b( other.m_b )
	{
	}
	int m_a;
	int m_b;
};

struct Gen003BDC50CallPair : Gen003BDC50CallPairBase
{
	Gen003BDC50CallPair( const Gen003BDC50CallPairBase &other ) :
		Gen003BDC50CallPairBase( other )
	{
	}
	~Gen003BDC50CallPair() {}
};

class BfmeCallJ378F8
{
public:
	void invoke( Gen003BDC50CallPair pair, int third );
};

class BfmeHostESM;
extern BfmeHostESM *g_bfmeStateDF;

class Glo012F1028Sub
{
public:
	virtual void slot0();
	virtual void first();
	virtual void slot2();
	virtual void transfer( Xfer *xfer );
	void refresh003CAD90();
	void bfmeNotify();
};

class Rva003C48E0
{
public:
	void rva003C48E0();
	int rva003C4160( Xfer *xfer );

private:
	char m_pad00[0x28];
	Glo012F1028Sub *m_field28;
	char m_pad2c[0xD4 - 0x2C];
	char *m_data;
	int m_size;
};
extern void j_000353b4();

void Rva003C48E0::rva003C48E0()
{
	if( m_data == 0 )
		return;
	if( m_size == 0 )
		return;

	File *file = createMemoryReadFile( m_data, m_size );
	if( file == 0 )
		return;

	int fileVersion;
	union VersionAndZero
	{
		Xfer::Version version;
		int zero;
	} versionAndZero;
	Coord3DBase position;
	Gen009D8CA0 xfer( 0, 0, 0 );
	xfer.readAt009D89E0( file, &fileVersion );
	typedef int (Rva003C48E0::*LoadFunction)( Xfer * );
	union { void (*raw)(void); LoadFunction member; } loadFunction;
	loadFunction.raw = j_000353b4;
	int version = (this->*loadFunction.member)( &xfer );
	TheLivingWorldCampaignManager->transfer( &xfer );
	m_field28->transfer( &xfer );
	typedef int (GameLogic::*LogicFunction)( Xfer * );
	union { void (*raw)(void); LogicFunction member; } logicFunction;
	logicFunction.raw = j_0002615c;
	(TheBfmeGameLogic->*logicFunction.member)( &xfer );
	g_bfmeGameCW->transfer( &xfer );

	if( version >= 3 )
	{
		versionAndZero.version.data[0] = 1;
		versionAndZero.version.data[1] = 2;
		xfer == versionAndZero.version;
		int serializedVersionValue = versionAndZero.version.data[1];
		if( serializedVersionValue >= 2 )
		{
			position.x = 0.0f;
			position.y = 0.0f;
			position.z = 0.0f;
			xfer == position;
			versionAndZero.zero = 0;
			xfer == *reinterpret_cast<float *>( &versionAndZero.zero );
			((BfmeCallJ378F8 *)g_bfmeStateDF)->invoke(
				*(const Gen003BDC50CallPair *)&position,
				versionAndZero.zero );
		}
	}

	reinterpret_cast<Rva009D8AA0 *>( &xfer )->apply();
	delete file;
	m_field28->first();
	m_field28->refresh003CAD90();
	m_field28->bfmeNotify();
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
