// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/radar /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4

#include "PreRTS.h"

#include "Common/Radar.h"
#include "GameClient/GameClient.h"

// BFME reads the client frame here: retail loads TheGameClient at 0x012F1464
// and calls its virtual getFrame through slot 26 (+0x68).

// Retail Radar events begin at this+0x28, are 0x50 bytes wide, and carry the
// global Coord3D world location at record+0x34.  Radar::clearAllEvents and
// Radar::update independently use the same event base, stride, and frame slots.
struct BfmeRadarTryEventRecord
{
	RadarEventType type;
	Bool active;
	UnsignedInt createFrame;
	char padding0C[ 0x28 ];
	Coord3D worldLoc;
	char padding40[ 0x10 ];
};

struct BfmeRadarTryEventView
{
	char padding00[ 0x28 ];
	BfmeRadarTryEventRecord event[ 64 ];
};

// The matched caller at 0x00370730 loads TheRadar, pushes Object+0x38 as a
// Coord3D pointer and event 10, then calls ILT 0x0001B6D0, whose jump target is
// this body.  Retail returns Bool in AL and uses ret 8: this is a nonvirtual
// two-argument member call, with neither a by-value Coord3D nor hidden sret.
Bool Radar::tryEvent( RadarEventType event, const Coord3D *pos )
{
	if( event >= RADAR_EVENT_NUM_EVENTS || pos == NULL )
		return FALSE;

	UnsignedInt currentFrame = TheGameClient->getFrame();
	const Real closeEnoughDistanceSq = 250.0f * 250.0f;
	const UnsignedInt framesBetweenEvents = LOGICFRAMES_PER_SECOND * 10;
	BfmeRadarTryEventView *radar = (BfmeRadarTryEventView *)this;

	for( Int i = 0; i < 64; ++i )
	{
		if( radar->event[ i ].type == event )
		{
			const Real *posY = &pos->y;
			Real distSquared = radar->event[ i ].worldLoc.x - pos->x * radar->event[ i ].worldLoc.x - pos->x +
										 radar->event[ i ].worldLoc.y - *posY * radar->event[ i ].worldLoc.y - *posY;

			if( distSquared <= closeEnoughDistanceSq )
			{
				if( currentFrame - radar->event[ i ].createFrame < framesBetweenEvents )
					return FALSE;
			}
		}
	}

	createEvent( pos, event );
	return TRUE;
}
