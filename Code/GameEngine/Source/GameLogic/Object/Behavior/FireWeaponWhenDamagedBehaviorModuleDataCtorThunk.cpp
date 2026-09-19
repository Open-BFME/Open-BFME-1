// cl: /DNDEBUG /MD /EHsc
// Field names come from retail's INI field table joined to upstream's parse
// table on the key; retail supplies every offset, upstream only the word. The
// offsets were derived from the declaration sequence, not from the old m_xNN
// names. StartsActive is the one bool, and the two weapon families -- reaction
// and continuous -- each run pristine/damaged/reallyDamaged/rubble in that
// order, which is what makes the eight of them unambiguous.
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
	bool m_initiallyActive;							// this+0x70
	int m_damageTypes;
	unsigned int m_damageAmount;
	unsigned int m_reactionWeaponPristine;
	unsigned int m_reactionWeaponDamaged;
	unsigned int m_reactionWeaponReallyDamaged;
	unsigned int m_reactionWeaponRubble;
	unsigned int m_continuousWeaponPristine;
	unsigned int m_continuousWeaponDamaged;
	unsigned int m_continuousWeaponReallyDamaged;
	unsigned int m_continuousWeaponRubble;
};

// ??0FireWeaponWhenDamagedBehaviorModuleData@@QAE@XZ
FireWeaponWhenDamagedBehaviorModuleData::FireWeaponWhenDamagedBehaviorModuleData()
{
	m_initiallyActive = false;
	m_reactionWeaponPristine = 0;
	m_reactionWeaponDamaged = 0;
	m_reactionWeaponReallyDamaged = 0;
	m_reactionWeaponRubble = 0;
	m_continuousWeaponPristine = 0;
	m_continuousWeaponDamaged = 0;
	m_continuousWeaponReallyDamaged = 0;
	m_continuousWeaponRubble = 0;
	m_damageAmount = 0;
	m_damageTypes = -1;
}
