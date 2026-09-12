// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/radar /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4

#include "PreRTS.h"

#include "Common/Player.h"
#include "Common/Radar.h"

// BFME stores Player::m_color at +0x1C4 in this method's retail layout.
void Radar::createPlayerEvent( Player *player, const Coord3D *world,
	RadarEventType type, Real secondsToLive )
{
	if( player == NULL || world == NULL )
		return;

	Color c;
	UnsignedByte r, g, b, a;
	RGBAColorInt color[ 2 ];
	c = *(Color *)((char *)player + 0x1C4);
	GameGetColorComponents( c, &r, &g, &b, &a );
	color[ 0 ].red = r;
	color[ 0 ].green = g;
	color[ 0 ].blue = b;
	color[ 0 ].alpha = a;

	Real darkScale = -0.75f;
	color[ 1 ] = color[ 0 ];
	color[ 1 ].red -= (Int)( color[ 0 ].red * darkScale );
	if( color[ 1 ].red < 0 )
		color[ 1 ].red = 0;
	color[ 1 ].green -= (Int)( color[ 0 ].green * darkScale );
	if( color[ 1 ].green < 0 )
		color[ 1 ].green = 0;
	color[ 1 ].blue -= (Int)( color[ 0 ].blue * darkScale );
	if( color[ 1 ].blue < 0 )
		color[ 1 ].blue = 0;

	internalCreateEvent( world, type, secondsToLive, &color[ 0 ], &color[ 1 ] );
}
