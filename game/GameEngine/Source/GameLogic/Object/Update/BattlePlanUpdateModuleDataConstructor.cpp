// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ??0BattlePlanUpdateModuleData@@QAE@XZ: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdate.cpp
//
// BattlePlanUpdateModuleData::BattlePlanUpdateModuleData, retail 0x00285F10,
// 164 bytes (plain ret at +0xA3). The matched
// BattlePlanUpdate::friend_newModuleData (0x00119D50) allocates 0xA0 bytes
// and constructs them through ILT 0x000287C7, which jumps here; the matched
// scalar deleting destructor (0x00285FE0) and destructor (0x00286010) follow
// directly. The body stores the vftable 0x010BBFC0 and then initialises every
// member in Zero Hour's declaration order: the AsciiString members are the
// zero handles, the two KindOf masks are cleared 192-bit sets, and the tail
// is Zero Hour's scalar defaults. BFME also zeroes m_transitionIdleFrames.

#include <bitset>

#include "ascii_string.h"

#include "../../../../Include/Common/BitFlags/BitFlags.h"

typedef BitFlags<192> KindOfMaskType;

class SpecialPowerTemplate;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual ~ModuleData() {}

private:
	unsigned int m_moduleTagNameKey;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
#include "../../../../Include/Common/Enums/MaxHealthChangeType.h"






// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BattlePlanUpdate.h
class BattlePlanUpdateModuleData : public ModuleData
{
public:
	SpecialPowerTemplate *m_specialPowerTemplate;			// +0x08

	unsigned int m_bombardmentPlanAnimationFrames;			// +0x0C
	unsigned int m_holdTheLinePlanAnimationFrames;			// +0x10
	unsigned int m_searchAndDestroyPlanAnimationFrames;		// +0x14
	unsigned int m_transitionIdleFrames;				// +0x18

	AsciiString m_bombardmentUnpackName;				// +0x1C
	AsciiString m_bombardmentPackName;
	AsciiString m_bombardmentMessageLabel;
	AsciiString m_bombardmentAnnouncementName;
	AsciiString m_searchAndDestroyUnpackName;
	AsciiString m_searchAndDestroyIdleName;
	AsciiString m_searchAndDestroyPackName;
	AsciiString m_searchAndDestroyMessageLabel;
	AsciiString m_searchAndDestroyAnnouncementName;
	AsciiString m_holdTheLineUnpackName;
	AsciiString m_holdTheLinePackName;
	AsciiString m_holdTheLineMessageLabel;
	AsciiString m_holdTheLineAnnouncementName;			// +0x4C

	unsigned int m_battlePlanParalyzeFrames;			// +0x50
	KindOfMaskType m_validMemberKindOf;				// +0x54
	KindOfMaskType m_invalidMemberKindOf;				// +0x6C

	float m_holdTheLineArmorDamageScalar;				// +0x84
	float m_searchAndDestroySightRangeScalar;			// +0x88
	float m_strategyCenterSearchAndDestroySightRangeScalar;	// +0x8C
	bool m_strategyCenterSearchAndDestroyDetectsStealth;		// +0x90
	float m_strategyCenterHoldTheLineMaxHealthScalar;		// +0x94
	MaxHealthChangeType m_strategyCenterHoldTheLineMaxHealthChangeType;	// +0x98

	AsciiString m_visionObjectName;					// +0x9C

	BattlePlanUpdateModuleData();
	virtual ~BattlePlanUpdateModuleData();
};

// ??0BattlePlanUpdateModuleData@@QAE@XZ
BattlePlanUpdateModuleData::BattlePlanUpdateModuleData() :
	m_specialPowerTemplate(0),
	m_bombardmentPlanAnimationFrames(0),
	m_holdTheLinePlanAnimationFrames(0),
	m_searchAndDestroyPlanAnimationFrames(0),
	m_transitionIdleFrames(0),
	m_battlePlanParalyzeFrames(0),
	m_holdTheLineArmorDamageScalar(1.0f),
	m_searchAndDestroySightRangeScalar(1.0f),
	m_strategyCenterSearchAndDestroySightRangeScalar(1.0f),
	m_strategyCenterSearchAndDestroyDetectsStealth(true),
	m_strategyCenterHoldTheLineMaxHealthScalar(1.0f),
	m_strategyCenterHoldTheLineMaxHealthChangeType(PRESERVE_RATIO)
{
}
