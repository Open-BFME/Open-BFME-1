// ?appearsToContainFriendlies@@YA_NPBVObject@@0@Z
// partial score=0.75 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

// Open-BFME7: near-miss twin of ActionManager.cpp's file-local
// appearsToContainFriendlies (dump target 0x000C3F30, near copy in the
// already-landed ActionManager.cpp: same file, only field/vtable offsets
// differ). The in-file present-unmatched version resolves Object::getContain()
// to this tree's +0x190 (retail +0x1fc, same delta already documented in
// ActionManagerCanPlayerGarrison.cpp), Object::getTeam() to +0x1d0 (retail
// +0x23c, same file), Player's default-team field to +0x160 (retail +0x230,
// same as GarrisonContain.cpp's BFME_PLAYER_DEFAULTTEAM and
// StealthUpdate_calcStealthedStatusForPlayer.cpp), and
// ContainModuleInterface::getApparentControllingPlayer to vtable+0x38
// (retail +0x3c). getControllingPlayer@Object and getRelationship@Team are
// already pinned in reverse/symbols.csv from that same TU, so the real
// classes are used for those two calls. This is a byte-exact twin under an
// address-tagged name so it does not collide with the real (file-static)
// symbol already defined in ActionManager.cpp.
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/ActionManager.h"
#include "Common/Player.h"
#include "Common/Team.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"

// Retail-offset stub of ContainModuleInterface: only the vtable slot for
// getApparentControllingPlayer is needed, at +0x3c (not this tree's +0x38).
class Rva000C3F30ContainModuleInterface
{
public:
	virtual void slot_000();
	virtual void slot_004();
	virtual void slot_008();
	virtual void slot_00c();
	virtual void slot_010();
	virtual void slot_014();
	virtual void slot_018();
	virtual void slot_01c();
	virtual void slot_020();
	virtual void slot_024();
	virtual void slot_028();
	virtual void slot_02c();
	virtual void slot_030();
	virtual void slot_034();
	virtual void slot_038();
	virtual Player *getApparentControllingPlayer( Player *localPlayer ) = 0;	///< +0x3c
};

Bool Rva000C3F30_appearsToContainFriendlies( const Object *obj, const Object *otherObject )
{
	// check if the object is a container containing stealth units tricking
	// the player into thinking it isn't actually an enemy.
	// Retail: Object::m_contain (getContain()) at +0x1fc, not this tree's +0x190.
	Rva000C3F30ContainModuleInterface *otherContain =
		*(Rva000C3F30ContainModuleInterface **)((const char *)otherObject + 0x1fc);
	if( otherContain )
	{
		Player *otherPlayer = otherContain->getApparentControllingPlayer(obj->getControllingPlayer());
		if (otherPlayer &&
			// Retail: Object::m_team (getTeam()) at +0x23c, not this tree's +0x1d0.
			(*(Team **)((const char *)obj + 0x23c))->getRelationship(
				// Retail: Player's default-team field at +0x230, not this tree's +0x160.
				*(Team * const *)((const char *)otherPlayer + 0x230)) != ENEMIES)
		{
			return TRUE;
		}
	}
	return FALSE;
}
