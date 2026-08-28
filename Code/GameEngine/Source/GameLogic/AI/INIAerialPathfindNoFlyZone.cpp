// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib

// FILE: INIAerialPathfindNoFlyZone.cpp ///////////////////////////////////////
//
// The AerialPathfindNoFlyZone block, retail 0x000B7E70. BFME-only; the INI
// block table in .data names it.
//
// Two sub-tokens rather than a field table: "TriggerArea" names a map trigger
// area and "Height" is the ceiling above it. Both are read with
// INI::getNextSubToken, which takes the expected keyword and returns the value
// that followed it.
//
// TheAerialPathfinder is 0x012EF1F8, named by GameEngine::init: the literal
// "TheAerialPathfinder" is constructed into the AsciiString it hands the
// registrar immediately before that address is pushed. TheTerrainLogic at
// 0x012EF4CC is the global the rest of the tree already reaches.
//
// getTriggerAreaByName is virtual slot 36 (vtable +0x90) and takes its
// AsciiString BY VALUE - the copy temporary is what the `mov [esp+N],esp` /
// `mov ecx,esp` pair at 0x004B7EA9 is building, so the string class has to be
// the WWLib StringBase-backed AsciiString whose constructors are visible.
//
// The zone is only registered when the trigger area resolves; the height is
// scanned either way, because retail reads it before it tests.
//
///////////////////////////////////////////////////////////////////////////////

#include "Common/AsciiString.h"

typedef float Real;

class PolygonTrigger;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextSubToken( const char *expected );

	static Real scanReal( const char *token );
};

// Only the one slot this block reaches is spelled out. The padding is what
// puts it at vtable +0x90; nothing here claims to know the other 36.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void _bfme_pad_00() = 0;
	virtual void _bfme_pad_01() = 0;
	virtual void _bfme_pad_02() = 0;
	virtual void _bfme_pad_03() = 0;
	virtual void _bfme_pad_04() = 0;
	virtual void _bfme_pad_05() = 0;
	virtual void _bfme_pad_06() = 0;
	virtual void _bfme_pad_07() = 0;
	virtual void _bfme_pad_08() = 0;
	virtual void _bfme_pad_09() = 0;
	virtual void _bfme_pad_10() = 0;
	virtual void _bfme_pad_11() = 0;
	virtual void _bfme_pad_12() = 0;
	virtual void _bfme_pad_13() = 0;
	virtual void _bfme_pad_14() = 0;
	virtual void _bfme_pad_15() = 0;
	virtual void _bfme_pad_16() = 0;
	virtual void _bfme_pad_17() = 0;
	virtual void _bfme_pad_18() = 0;
	virtual void _bfme_pad_19() = 0;
	virtual void _bfme_pad_20() = 0;
	virtual void _bfme_pad_21() = 0;
	virtual void _bfme_pad_22() = 0;
	virtual void _bfme_pad_23() = 0;
	virtual void _bfme_pad_24() = 0;
	virtual void _bfme_pad_25() = 0;
	virtual void _bfme_pad_26() = 0;
	virtual void _bfme_pad_27() = 0;
	virtual void _bfme_pad_28() = 0;
	virtual void _bfme_pad_29() = 0;
	virtual void _bfme_pad_30() = 0;
	virtual void _bfme_pad_31() = 0;
	virtual void _bfme_pad_32() = 0;
	virtual void _bfme_pad_33() = 0;
	virtual void _bfme_pad_34() = 0;
	virtual void _bfme_pad_35() = 0;
	virtual PolygonTrigger *getTriggerAreaByName( AsciiString name ) = 0;	// +0x90
};

class AerialPathfinder
{
public:
	void addNoFlyZone( PolygonTrigger *area, Real height );
};

extern TerrainLogic *TheTerrainLogic;				// 0x012EF4CC
extern AerialPathfinder *TheAerialPathfinder;		// 0x012EF1F8

// ?parseAerialPathfindNoFlyZone@@YAXPAVINI@@@Z
void parseAerialPathfindNoFlyZone( INI *ini )
{
	AsciiString areaName = ini->getNextSubToken( "TriggerArea" );
	PolygonTrigger *area = TheTerrainLogic->getTriggerAreaByName( areaName );

	Real height = INI::scanReal( ini->getNextSubToken( "Height" ) );

	if( area )
		TheAerialPathfinder->addNoFlyZone( area, height );
}
