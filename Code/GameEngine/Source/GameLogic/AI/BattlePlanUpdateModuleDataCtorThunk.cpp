// cl: /DNDEBUG /MD /EHsc
// readable body of ??0BattlePlanUpdateModuleData@@QAE@XZ: Code/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdate.cpp
// Field names come from retail's own INI field table joined to upstream's
// parse table on the key: retail supplies every offset, upstream only the
// word. The offsets were derived from this class's declaration sequence and
// type sizes, never read out of the old placeholder names.
// Open-BFME5: the named ILT 0x0003025B reaches this body, and ModuleFactory's
// data-create proc 0x00117420 allocates 0x90 for it, so this is
// BattlePlanUpdateModuleData's constructor.
//
// The shared module-data base runs at this+0x08 through ILT 0x0000F0A6 (the
// ICF-folded 0x00129C10 body), so everything from 0x70 up is this class.

#include <string.h>

class BPU_BaseModuleData
{
public:
	BPU_BaseModuleData();

private:
	unsigned char m_raw[0x68];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BattlePlanUpdate.h
class BattlePlanUpdateModuleData
{
public:
	BattlePlanUpdateModuleData();
	virtual ~BattlePlanUpdateModuleData();

private:
	void *m_x04;
	BPU_BaseModuleData m_base;			// this+0x08
	float m_x70;						// this+0x70
	unsigned int m_x74;
	unsigned int m_x78;
	unsigned int m_x7c[3];				// this+0x7C .. 0x84
	int m_searchAndDestroySightRangeScalar;
	bool m_strategyCenterSearchAndDestroySightRangeScalar;
	bool m_x8d;
};

// ??0BattlePlanUpdateModuleData@@QAE@XZ
BattlePlanUpdateModuleData::BattlePlanUpdateModuleData()
{
	memset(m_x7c, 0, sizeof(m_x7c));
	m_strategyCenterSearchAndDestroySightRangeScalar = false;
	m_x74 = 0;
	m_x78 = 0;
	m_x8d = false;
	m_searchAndDestroySightRangeScalar = 5;
	m_x70 = 100.0f;
}
