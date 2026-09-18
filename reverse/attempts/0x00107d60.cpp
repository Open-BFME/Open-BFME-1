// ?internalCreateEvent@Radar@@IAEXPBUCoord3D@@W4RadarEventType@@MPBURGBAColorInt@@2@Z
// partial score=0.978 date=2026-09-17
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/radar /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4

#include "PreRTS.h"

#include "Common/Radar.h"
#include "GameClient/GameClient.h"

struct BfmeRadarInternalEventRef
{
	virtual void Release_Ref( bool destroy );
	int m_refCount;
};

struct BfmeRadarInternalEvent
{
	RadarEventType type;
	Bool active;
	UnsignedInt createFrame;
	UnsignedInt dieFrame;
	UnsignedInt fadeFrame;
	RGBAColorInt color1;
	RGBAColorInt color2;
	Coord3D worldLoc;
	ICoord2D radarLoc;
	Bool soundPlayed;
	BfmeRadarInternalEventRef *ref;
};

struct BfmeRadarInternalEventStorage
{
	char padding00[ 0x28 ];
	BfmeRadarInternalEvent event[ 64 ];
	Int nextFreeRadarEvent;
	Int lastRadarEvent;
};

#pragma comment(linker, "/alternatename:?worldToRadar@Radar@@QAE_NPBUCoord3D@@PAUICoord2D@@@Z=?j_00026099@@YAXXZ")

// ?internalCreateEvent@Radar@@ present-unmatched
void Radar::internalCreateEvent( const Coord3D *world, RadarEventType type,
	Real secondsToLive, const RGBAColorInt *color1,
	const RGBAColorInt *color2 )
{
	static Real secondsBeforeDieToFade = 0.5f;

	if( world == NULL || color1 == NULL || color2 == NULL )
		return;

	ICoord2D radar;
	worldToRadar( world, &radar );

	BfmeRadarInternalEventStorage *storage =
		(BfmeRadarInternalEventStorage *)this;
	storage->event[ storage->nextFreeRadarEvent ].type = type;
	storage->event[ storage->nextFreeRadarEvent ].active = TRUE;
	storage->event[ storage->nextFreeRadarEvent ].createFrame =
		TheGameClient->getFrame();
	storage->event[ storage->nextFreeRadarEvent ].dieFrame =
		TheGameClient->getFrame() + LOGICFRAMES_PER_SECOND * secondsToLive;
	storage->event[ storage->nextFreeRadarEvent ].fadeFrame =
		storage->event[ storage->nextFreeRadarEvent ].dieFrame -
		LOGICFRAMES_PER_SECOND * secondsBeforeDieToFade;
	storage->event[ storage->nextFreeRadarEvent ].color1 = *color1;
	storage->event[ storage->nextFreeRadarEvent ].color2 = *color2;
	storage->event[ storage->nextFreeRadarEvent ].worldLoc = *world;
	storage->event[ storage->nextFreeRadarEvent ].radarLoc = radar;
	storage->event[ storage->nextFreeRadarEvent ].soundPlayed = FALSE;

	BfmeRadarInternalEventRef **ref =
		&storage->event[ storage->nextFreeRadarEvent ].ref;
	BfmeRadarInternalEventRef *value = *ref;
	if( value != NULL )
	{
		int count = --value->m_refCount;
		if( count <= 0 )
			value->Release_Ref( true );
		*ref = NULL;
	}

	if( type != (RadarEventType)6 )
		storage->lastRadarEvent = storage->nextFreeRadarEvent;

	storage->nextFreeRadarEvent++;
	if( storage->nextFreeRadarEvent >= 64 )
		storage->nextFreeRadarEvent = 0;
}
