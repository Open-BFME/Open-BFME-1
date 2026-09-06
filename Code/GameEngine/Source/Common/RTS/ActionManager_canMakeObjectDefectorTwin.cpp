// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

// Open-BFME7: near-miss twin of ActionManager::canMakeObjectDefector (dump
// target 0x000C41C0, near copy in the already-landed ActionManager.cpp:
// same file, only one field offset differs). ActionManager.cpp's own
// present-unmatched canMakeObjectDefector calls objectToMakeDefector->
// isEffectivelyDead(), which this tree resolves to Object::m_privateStatus
// at +0x297; retail keeps it at +0x344 (already fixed the same way at
// ActionManager.cpp:377 and in several other TUs -- see
// promoted__isGroupAiDead_AIGroup_QBE_NXZ_00151390.cpp's comment "BFME grew
// Object past ZH's layout: m_privateStatus sits at +0x344 here, not
// +0x297"). isObjectShroudedForAction is `static` (internal linkage) in
// ActionManager.cpp, so it is duplicated verbatim here rather than calling
// across TUs; its call target is masked by relocation for byte-match
// purposes, so a private local copy is fine. This is a byte-exact twin
// under an address-tagged name so it does not collide with the real
// mangled symbol already defined (with the wrong offset) in
// ActionManager.cpp.
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/ActionManager.h"
#include "Common/Player.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"

// Verbatim copy of ActionManager.cpp's own file-local isObjectShroudedForAction.
static Bool Rva000C41C0_isObjectShroudedForAction(const Object *source, const Object *target, CommandSourceType commandSource)
{
	if (target)
	{
		// BFME reserves this signed ObjectID range for non-world objects, which cannot be shrouded targets.
		Int targetID = *reinterpret_cast<const Int *>(reinterpret_cast<const char *>(target) + 0x74);
		if (targetID >= 0x05f5e0fc && targetID <= 0x05f5e0ff)
			return FALSE;
	}

	if (source && target && source->getControllingPlayer())
	{
		if (*reinterpret_cast<const Int *>(reinterpret_cast<const char *>(source->getControllingPlayer()) + 0x2c) == PLAYER_HUMAN &&
				commandSource != CMD_FROM_SCRIPT &&
				target->getShroudedStatus(source->getControllingPlayer()->getPlayerIndex()) >= OBJECTSHROUD_FOGGED)
		{
			return TRUE;
		}
	}

	return FALSE;
}

class Rva000C41C0ActionManager
{
public:
	Bool canMakeObjectDefector( const Object *obj, const Object *objectToMakeDefector, CommandSourceType commandSource );
};

Bool Rva000C41C0ActionManager::canMakeObjectDefector( const Object *obj, const Object *objectToMakeDefector, CommandSourceType commandSource ) //LORENZEN
{
	// sanity
	if( obj == NULL || objectToMakeDefector == NULL )
	{
		return FALSE;
	}

	Relationship r = obj->getRelationship(objectToMakeDefector);

	//Only make defectors of enemy objects
	if( r != ENEMIES )
	{
		return FALSE;
	}

	//Make sure it's alive. Retail keeps Object::m_privateStatus at +0x344,
	//not this tree's +0x297.
	if( *reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(objectToMakeDefector) + 0x344) & 1 )
	{
		return FALSE;
	}

	// if the target is in the shroud, we can't do anything
	if (Rva000C41C0_isObjectShroudedForAction(obj, objectToMakeDefector, commandSource))
	{
		return FALSE;
	}

	return TRUE;
}
