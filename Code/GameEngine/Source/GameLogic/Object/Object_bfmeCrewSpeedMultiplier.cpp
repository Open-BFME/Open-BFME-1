// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Object crew-powered speed multiplier query, retail 0x001BF020,
// 25 bytes. The wrapper returns 1.0 when this Object has no contain module;
// otherwise it tail-forwards to BFME's ContainModuleInterface slot 48 (+0xC0).
//
// The slot's implementations establish its behavior: OpenContain returns 1.0,
// while SiegeEngineContain/RiderChangeContain and HordeSiegeEngineContain
// multiply the current crew count by the module-data SpeedPercentPerCrew value.
// Neither the BFME1 binary nor the BFME2/ROTWK module-property reference exposes
// the original C++ member spelling. The bfme-prefixed name below is therefore
// deliberately descriptive, not a claim about the stripped retail identifier.
// Likewise, this no-argument thiscall body does not encode cv-qualification;
// const records its observed query-only behavior rather than symbol metadata.

typedef int Int;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	// Only the slot count is asserted here. The placeholder names and Int
	// signatures deliberately make no claim about BFME's stripped declarations.
	virtual Int bfmeSlot00() = 0; virtual Int bfmeSlot01() = 0;
	virtual Int bfmeSlot02() = 0; virtual Int bfmeSlot03() = 0;
	virtual Int bfmeSlot04() = 0; virtual Int bfmeSlot05() = 0;
	virtual Int bfmeSlot06() = 0; virtual Int bfmeSlot07() = 0;
	virtual Int bfmeSlot08() = 0; virtual Int bfmeSlot09() = 0;
	virtual Int bfmeSlot10() = 0; virtual Int bfmeSlot11() = 0;
	virtual Int bfmeSlot12() = 0; virtual Int bfmeSlot13() = 0;
	virtual Int bfmeSlot14() = 0; virtual Int bfmeSlot15() = 0;
	virtual Int bfmeSlot16() = 0; virtual Int bfmeSlot17() = 0;
	virtual Int bfmeSlot18() = 0; virtual Int bfmeSlot19() = 0;
	virtual Int bfmeSlot20() = 0; virtual Int bfmeSlot21() = 0;
	virtual Int bfmeSlot22() = 0; virtual Int bfmeSlot23() = 0;
	virtual Int bfmeSlot24() = 0; virtual Int bfmeSlot25() = 0;
	virtual Int bfmeSlot26() = 0; virtual Int bfmeSlot27() = 0;
	virtual Int bfmeSlot28() = 0; virtual Int bfmeSlot29() = 0;
	virtual Int bfmeSlot30() = 0; virtual Int bfmeSlot31() = 0;
	virtual Int bfmeSlot32() = 0; virtual Int bfmeSlot33() = 0;
	virtual Int bfmeSlot34() = 0; virtual Int bfmeSlot35() = 0;
	virtual Int bfmeSlot36() = 0; virtual Int bfmeSlot37() = 0;
	virtual Int bfmeSlot38() = 0; virtual Int bfmeSlot39() = 0;
	virtual Int bfmeSlot40() = 0; virtual Int bfmeSlot41() = 0;
	virtual Int bfmeSlot42() = 0; virtual Int bfmeSlot43() = 0;
	virtual Int bfmeSlot44() = 0; virtual Int bfmeSlot45() = 0;
	virtual Int bfmeSlot46() = 0; virtual Int bfmeSlot47() = 0;
	virtual Real bfmeGetCrewSpeedMultiplier() const = 0; // slot 48, +0xC0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Real bfmeGetCrewSpeedMultiplier() const;

private:
	Int m_bfmeObjectPrefix[0x1FC / sizeof(Int)];
	ContainModuleInterface *m_contain; // +0x1FC
};

// ?bfmeGetCrewSpeedMultiplier@Object@@QBEMXZ
Real Object::bfmeGetCrewSpeedMultiplier() const
{
	ContainModuleInterface *contain = m_contain;
	if (contain == 0)
		return 1.0f;
	return contain->bfmeGetCrewSpeedMultiplier();
}
