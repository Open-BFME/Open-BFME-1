// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AttackNugget::AttackNugget, retail 0x001D6CD0,
// zh_sweep packet 001d6cd0.
//
// The reference constructor unchanged. Everything matched against
// ObjectCreationList.cpp except three offsets: retail writes
// m_deliveryDecalRadius at [this+0x34], m_numberOfShots at +0x38 and
// m_weaponSlot at +0x3C, where the vendored class puts them at +0x20, +0x24 and
// +0x28. The gap is the member ahead of them: BFME's RadiusDecalTemplate is
// 0x30 bytes, the vendored one 0x1C.
//
// Its own TU because that is a header type -- widening it under
// ObjectCreationList.cpp moves every other row there, and that file has EH
// funclet rows keyed on $L labels which a layout edit takes out.
//
// The base contributes nothing: retail stamps one vtable and calls only the
// RadiusDecalTemplate constructor, so the vptr belongs to this class and the
// base subobject is empty. The SEH frame is there to destroy that member if its
// constructor throws.

typedef float Real;
typedef int Int;

enum WeaponSlotType { PRIMARY_WEAPON = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();
	// Declared so the constructor gets an unwind funclet: retail has the SEH
	// frame, which only exists to destroy this member if construction fails.
	~RadiusDecalTemplate();

private:
	unsigned char m_unreconstructed_00[0x30];				///< sizeof 0x30
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectCreationList.h
class ObjectCreationNugget
{
public:
	// Empty and contributing no bytes, but with a destructor: that is what
	// makes the member construction below an unwindable action and gives the
	// constructor the SEH frame retail has. The reference base derives from
	// MemoryPoolObject, whose destructor is non-trivial for exactly this
	// reason, while its constructor emits nothing.
	~ObjectCreationNugget();
};

class AttackNugget : public ObjectCreationNugget
{
public:
	AttackNugget();

	virtual ~AttackNugget() {}								///< places the vptr at +0x00

private:
	RadiusDecalTemplate	m_deliveryDecalTemplate;			///< +0x04
	Real				m_deliveryDecalRadius;				///< +0x34
	Int					m_numberOfShots;					///< +0x38
	WeaponSlotType		m_weaponSlot;						///< +0x3C
};

// ??0AttackNugget@@QAE@XZ
AttackNugget::AttackNugget() : 
	m_numberOfShots(1),
	m_weaponSlot(PRIMARY_WEAPON),
	m_deliveryDecalRadius(0)
{
}
