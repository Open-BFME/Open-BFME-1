// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ModuleFactory's data-create proc 0x0012A170 allocates 0x9C and
// runs this constructor through ILT 0x00012233, which identifies
// FireWeaponWhenDamagedBehaviorModuleData. The name previously sat on the
// shared INI::initFromINIMultiProc body at 0x00852130 as one of a batch of
// ICF aliases; that address is a different function.
//
// The shared module-data base runs at this+0x08 through ILT 0x0000F0A6 (the
// ICF-folded 0x00129C10 body), so everything from 0x70 up is this class.

class FWWD_BaseModuleData
{
public:
	FWWD_BaseModuleData();

private:
	unsigned char m_raw[0x68];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponWhenDamagedBehavior.h
class FireWeaponWhenDamagedBehaviorModuleData
{
public:
	FireWeaponWhenDamagedBehaviorModuleData();
	virtual ~FireWeaponWhenDamagedBehaviorModuleData();

private:
	void *m_x04;
	FWWD_BaseModuleData m_base;			// this+0x08
	bool m_x70;							// this+0x70
	int m_x74;
	unsigned int m_x78;
	unsigned int m_x7c;
	unsigned int m_x80;
	unsigned int m_x84;
	unsigned int m_x88;
	unsigned int m_x8c;
	unsigned int m_x90;
	unsigned int m_x94;
	unsigned int m_x98;
};

// ??0FireWeaponWhenDamagedBehaviorModuleData@@QAE@XZ
FireWeaponWhenDamagedBehaviorModuleData::FireWeaponWhenDamagedBehaviorModuleData()
{
	m_x70 = false;
	m_x7c = 0;
	m_x80 = 0;
	m_x84 = 0;
	m_x88 = 0;
	m_x8c = 0;
	m_x90 = 0;
	m_x94 = 0;
	m_x98 = 0;
	m_x78 = 0;
	m_x74 = -1;
}
