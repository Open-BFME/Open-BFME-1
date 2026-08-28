// cl: /DNDEBUG /MD /EHsc
// Field names come from retail's own INI field table joined to upstream's
// parse table on the key: retail supplies every offset, upstream only the
// word. The offsets were derived from this class's declaration sequence and
// type sizes, never read out of the old placeholder names.
// Open-BFME5: DemoTrapUpdateModuleData::DemoTrapUpdateModuleData, retail
// 0x0028C9E0, 58 bytes.
//
// A flat field constructor. The six dwords at +0x0C are cleared through a
// materialised base pointer rather than this-relative displacements, which is
// an inline memset over an array member and not a run of field assignments.

#include <string.h>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DemoTrapUpdate.h
class DemoTrapUpdateModuleData
{
public:
	DemoTrapUpdateModuleData();
	virtual ~DemoTrapUpdateModuleData();

private:
	unsigned int m_x04;					// untouched by the constructor
	unsigned int m_detonationWeaponTemplate;
	unsigned int m_block[6];			// this+0x0C .. 0x20
	unsigned int m_manualModeWeaponSlot;
	unsigned int m_detonationWeaponSlot;
	unsigned int m_proximityModeWeaponSlot;
	unsigned int m_triggerDetonationRange;
	unsigned int m_scanFrames;
	bool m_defaultsToProximityMode;
	bool m_friendlyDetonation;
	bool m_detonateWhenKilled;
};

// ??0DemoTrapUpdateModuleData@@QAE@XZ
DemoTrapUpdateModuleData::DemoTrapUpdateModuleData()
{
	memset(m_block, 0, sizeof(m_block));
	m_defaultsToProximityMode = false;
	m_friendlyDetonation = false;
	m_manualModeWeaponSlot = 0;
	m_detonationWeaponSlot = 0;
	m_proximityModeWeaponSlot = 0;
	m_triggerDetonationRange = 0;
	m_scanFrames = 0;
	m_detonationWeaponTemplate = 0;
	m_detonateWhenKilled = false;
}
