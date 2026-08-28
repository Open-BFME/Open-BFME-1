// cl: /DNDEBUG /MD /EHsc
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
	unsigned int m_x08;
	unsigned int m_block[6];			// this+0x0C .. 0x20
	unsigned int m_x24;
	unsigned int m_x28;
	unsigned int m_x2c;
	unsigned int m_x30;
	unsigned int m_x34;
	bool m_x38;
	bool m_x39;
	bool m_x3a;
};

// ??0DemoTrapUpdateModuleData@@QAE@XZ
DemoTrapUpdateModuleData::DemoTrapUpdateModuleData()
{
	memset(m_block, 0, sizeof(m_block));
	m_x38 = false;
	m_x39 = false;
	m_x24 = 0;
	m_x28 = 0;
	m_x2c = 0;
	m_x30 = 0;
	m_x34 = 0;
	m_x08 = 0;
	m_x3a = false;
}
