// cl: /DNDEBUG /MD /EHsc
// Four special powers whose slot-12 doSpecialPowerAtObject and slot-13 body both
// just forward commandOptions to their own doSpecialPower (slot 11, +0x2C):
//     mov edx,[esp+8] / mov eax,[ecx] / push edx / call [eax+0x2C] / ret 8
// Each body is reached only through its own ILT stub, whose VA appears once in
// the image, in the SpecialPowerModuleInterface table the class's registered
// constructor stores at +0x10. Slot 12 is doSpecialPowerAtObject
// (Object::doSpecialPowerAtObject 0x001C37F0 calls +0x30). Slot 13's name is
// unproven (see the evidence note's open question), so those bodies keep their
// address and take a neutral location pointer.
// Evidence: targets/game/reverse/identity_evidence/specialpower-slot11-12-dospecialpower.md
//
// Moved from VirtualSlot5CallThunk.cpp (VirtualSlot11SecondArgumentCallThunk).

typedef unsigned int UnsignedInt;

class Object;

// table 0x010b3d58, ctor 0x002596f0: slot 12 0x00259770, slot 13 0x00259760
class CombineHordeSpecialPower
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10();
	virtual void doSpecialPower(UnsignedInt commandOptions);
	virtual void doSpecialPowerAtObject(Object *obj, UnsignedInt commandOptions);
	virtual void rva00259760(void *where, UnsignedInt commandOptions);
};

void CombineHordeSpecialPower::doSpecialPowerAtObject(Object *, UnsignedInt commandOptions)
{
	doSpecialPower(commandOptions);
}

void CombineHordeSpecialPower::rva00259760(void *, UnsignedInt commandOptions)
{
	doSpecialPower(commandOptions);
}

// table 0x010b6558, ctor 0x00263f50: slot 12 0x00263FD0, slot 13 0x00263FC0
class PlayerUpgradeSpecialPower
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10();
	virtual void doSpecialPower(UnsignedInt commandOptions);
	virtual void doSpecialPowerAtObject(Object *obj, UnsignedInt commandOptions);
	virtual void rva00263FC0(void *where, UnsignedInt commandOptions);
};

void PlayerUpgradeSpecialPower::doSpecialPowerAtObject(Object *, UnsignedInt commandOptions)
{
	doSpecialPower(commandOptions);
}

void PlayerUpgradeSpecialPower::rva00263FC0(void *, UnsignedInt commandOptions)
{
	doSpecialPower(commandOptions);
}

// table 0x010b7f78, ctor 0x0026b030: slot 12 0x0026B0B0, slot 13 0x0026B0A0
class SplitHordeSpecialPower
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10();
	virtual void doSpecialPower(UnsignedInt commandOptions);
	virtual void doSpecialPowerAtObject(Object *obj, UnsignedInt commandOptions);
	virtual void rva0026B0A0(void *where, UnsignedInt commandOptions);
};

void SplitHordeSpecialPower::doSpecialPowerAtObject(Object *, UnsignedInt commandOptions)
{
	doSpecialPower(commandOptions);
}

void SplitHordeSpecialPower::rva0026B0A0(void *, UnsignedInt commandOptions)
{
	doSpecialPower(commandOptions);
}

// table 0x010b8a50, ctor 0x0026cc80: slot 12 0x0026CD20, slot 13 0x0026CD30
class WeaponChangeSpecialPowerModule
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10();
	virtual void doSpecialPower(UnsignedInt commandOptions);
	virtual void doSpecialPowerAtObject(Object *obj, UnsignedInt commandOptions);
	virtual void rva0026CD30(void *where, UnsignedInt commandOptions);
};

void WeaponChangeSpecialPowerModule::doSpecialPowerAtObject(Object *, UnsignedInt commandOptions)
{
	doSpecialPower(commandOptions);
}

void WeaponChangeSpecialPowerModule::rva0026CD30(void *, UnsignedInt commandOptions)
{
	doSpecialPower(commandOptions);
}
