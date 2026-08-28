// cl: /DNDEBUG /MD /EHsc

// BeaconClientUpdate's constructor, retail 0x006030C0. DrawModule's base -
// twelve bytes, one vftable pointer and eight bytes of state - then two fields
// of its own: a zero at +0x0C and the current frame at +0x10, read straight out
// of TheGameLogic at +0x3C with the accessor inlined.
//
// The name was aliased onto 0x0024FC20, a forty-six byte constructor several
// unrelated modules share; a fifty-one byte body with a global read is not that.

typedef unsigned int UnsignedInt;

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_unmodelled_00[ 0x3C ];
	UnsignedInt m_frame;					// +0x3C
};

extern GameLogic *TheGameLogic;				// 0x012F0898

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
class DrawModule
{
public:
	DrawModule( Thing *thing, const ModuleData *moduleData );

	virtual void drawModuleAnchor();

private:
	unsigned char m_data[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Module/BeaconClientUpdate.h
class BeaconClientUpdate : public DrawModule
{
public:
	BeaconClientUpdate( Thing *thing, const ModuleData *moduleData );

private:
	int m_unmodelled_0C;					// +0x0C
	UnsignedInt m_createdFrame;				// +0x10
};

// ??0BeaconClientUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
BeaconClientUpdate::BeaconClientUpdate( Thing *thing, const ModuleData *moduleData )
	: DrawModule( thing, moduleData ),
	  m_unmodelled_0C( 0 ),
	  m_createdFrame( TheGameLogic->m_frame )
{
}
