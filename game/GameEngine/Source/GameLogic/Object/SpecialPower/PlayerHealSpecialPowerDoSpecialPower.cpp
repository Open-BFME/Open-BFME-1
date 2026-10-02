// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// PlayerHealSpecialPower::doSpecialPower at retail 0x00263A40: slot 11 of the
// SpecialPowerModuleInterface table 0x010B6390, which PlayerHealSpecialPower's registered
// constructor 0x002639D0 stores at +0x10. The body is reached only through ILT
// 0x0000AF88, whose VA appears once in the image. Object::doSpecialPower
// (0x001C3790) calls slot 11 (+0x2C) with commandOptions; the body ends `ret 4`.
// Evidence: targets/game/reverse/identity_evidence/specialpower-slot11-12-dospecialpower.md


typedef unsigned int UnsignedInt;

class PlayerHealSpecialPower
{
public:
	virtual void doSpecialPower( UnsignedInt commandOptions );
};

// The override does nothing; retail is `ret 4`.
void PlayerHealSpecialPower::doSpecialPower( UnsignedInt )
{
}
