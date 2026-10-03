// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/radar /Iinputs/reference/shims/gameclientxfer /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define __PLACEMENT_VEC_NEW_INLINE
#include "Common/Radar.h"
#include "Common/NameKeyGenerator.h"
#include "GameLogic/GameLogic.h"

typedef int Int;
typedef bool Bool;

enum EvaMessage
{
	EVA_INVALID = -1,
	EVA_VALUE_7 = 7
};

class Player;
class Module;

// The 0x00370730 body is slot 2 of CastleMemberBehavior's secondary
// interface at +0x10.  This view is deliberately non-virtual: it is only a
// declaration of the slot body and must not emit a partial interface table.
class Rva00370730CastleMemberInterface
{
public:
	void run( Int unused1, Int unused2, Int mode );
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Module *findModule( NameKeyType key ) const;
};

class Eva
{
public:
	Bool setShouldPlay( EvaMessage message, const Coord3D *position );
};

typedef Int (__cdecl *Rva0036ff70Callback)( void *, void * );

// Retail 0x0036ff70 iterates module-owned records and invokes the callback;
// its two explicit arguments are callback then callback context and it
// returns the callback-chain result.  This declaration emits no table.
class Rva0036ff70Module
{
public:
	Int query( Rva0036ff70Callback callback, void *context );
};

struct Rva005655C0PlayerList
{
	unsigned char m_padding00[ 0x0c ];
	Player *m_localPlayer0c;
};

struct Rva00370730ModuleData
{
	unsigned char m_padding00[ 0x29 ];
	unsigned char m_isCastleBehavior;
};

// The singleton itself is retail's PlayerList (game/GameEngine/Source/Common/RTS/PlayerList.cpp
// defines `PlayerList *ThePlayerList`); only the +0x0C local-player subobject is still
// address-named, so the global keeps its real spelling and the read is cast.
class PlayerList;

extern PlayerList *ThePlayerList;	// retail [0x012ED748]
extern GameLogic *TheGameLogic;
extern NameKeyGenerator *TheNameKeyGenerator;
extern Eva *TheEva;
extern Radar *TheRadar;

// The callback at 0x0036CFD0 is defined by BfmeConv1939.cpp. It returns
// a full EAX integer and ignores the query interface's context argument.
class BfmeThingDJ;
Int __cdecl bfmeCheckDJ(BfmeThingDJ *thing);

// ?run@Rva00370730CastleMemberInterface@@QAEXHHH@Z
void Rva00370730CastleMemberInterface::run( Int, Int, Int mode )
{
	if( mode == 3 )
	{
		unsigned char *self = (unsigned char *)this;
		Rva00370730ModuleData *moduleData =
			*(Rva00370730ModuleData **)( self - 0x0c );
		if( moduleData->m_isCastleBehavior )
		{
			Player *localPlayer =
				((Rva005655C0PlayerList *)ThePlayerList)->m_localPlayer0c;
			if( localPlayer ==
				(*(Object * volatile *)( self - 0x08 ))->getControllingPlayer() )
			{
				Object *pendingObject = TheGameLogic->findObjectByID(
					*(Int *)( self + 0x08 ) );
				if( pendingObject != 0 )
				{
					static volatile NameKeyType castleBehaviorKey =
						TheNameKeyGenerator->nameToKey(
							"CastleBehavior" );
					Module *module = pendingObject->findModule( castleBehaviorKey );
					if( module != 0 )
					{
						Rva0036ff70Callback callback =
							reinterpret_cast<Rva0036ff70Callback>(bfmeCheckDJ);
						if( ( (Rva0036ff70Module *)module )->query(
							callback, 0 ) == 1 )
						{
							if( TheEva->setShouldPlay( EVA_VALUE_7,
								(Coord3D *)( (unsigned char *)*(Object **)
									( self - 0x08 ) + 0x38 ) ) )
							{
								register Coord3D *radarPosition =
									(Coord3D *)( (unsigned char *)*(Object **)
										( self - 0x08 ) + 0x38 );
								(*(Radar * volatile *)&TheRadar)->tryEvent( RADAR_EVENT_FAKE,
									radarPosition );
							}
						}
					}
				}
			}
		}
		*(unsigned char *)( self + 0x15 ) = 1;
	}
	else if( mode < 2 )
		*(unsigned char *)( (unsigned char *)this + 0x15 ) = 0;
}
