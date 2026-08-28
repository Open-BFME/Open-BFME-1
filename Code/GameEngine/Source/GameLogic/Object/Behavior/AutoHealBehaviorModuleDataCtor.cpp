// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME5: AutoHealBehaviorModuleData::AutoHealBehaviorModuleData,
// 0x00129D50, 180 bytes. ModuleFactory's data-create proc 0x00129E40
// allocates 0xA8 and runs this body; the name previously sat on its five-byte
// incremental-link thunk at 0x000287C7.
//
// The shared module-data base runs at this+0x08 through ILT 0x0000F0A6, so
// everything from 0x70 up is this class. The 0x18-byte flag word at 0x88 is an
// STLport bitset: the trailing `and ecx,0x1FFFFF` is its sanitize step, and
// 5*32 + 21 names the template argument as 181 bits. Its default constructor
// is the first run of six zero stores, `reset()` the second, and `flip()` the
// not-and-sanitize tail.

#include <bitset>

class AHB_BaseModuleData
{
public:
	AHB_BaseModuleData();

private:
	unsigned char m_raw[0x68];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoHealBehavior.h
class AutoHealBehaviorModuleData
{
public:
	AutoHealBehaviorModuleData();
	virtual ~AutoHealBehaviorModuleData();

private:
	void *m_x04;
	AHB_BaseModuleData m_base;			// this+0x08
	bool m_x70;							// this+0x70
	bool m_x71;
	bool m_x72;
	unsigned int m_x74;
	int m_x78;
	unsigned int m_x7c;
	unsigned int m_x80;
	bool m_x84;
	bool m_x85;
	bool m_x86;
	_STL::bitset<181> m_bits;			// this+0x88
	bool m_xa0;							// this+0xA0
	unsigned int m_xa4;
};

// ??0AutoHealBehaviorModuleData@@QAE@XZ
AutoHealBehaviorModuleData::AutoHealBehaviorModuleData()
{
	m_x70 = false;
	m_x71 = false;
	m_x72 = false;
	m_x74 = 0;
	m_x7c = 0;
	m_x80 = 0;
	m_x84 = false;
	m_x85 = false;
	m_x86 = false;
	m_xa0 = false;
	m_xa4 = 0;
	m_x78 = -1;
	m_bits.reset();
	m_bits.flip();
}
