// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: CrateCollideModuleData's constructor, retail 0x00217870, 147
// bytes, recovered from the naked __emit lift that carried it under four
// over-claiming derived names (Shroud/Heal/Money/ConvertToCarBomb).
//
// The member list and every offset come from the retail FieldParse table at
// 0x00CAA4B0 (targets/game/reverse/field_names.csv): m_kindof +0x08,
// m_kindofnot +0x20, m_isForbidOwnerPlayer +0x38, m_isBuildingPickup +0x39,
// m_isHumanOnlyPickup +0x3A, m_pickupScience +0x3C, m_executeFX +0x40,
// m_executionAnimationTemplate +0x44, m_executeAnimationDisplayTimeInSeconds
// +0x48, m_executeAnimationZRisePerSecond +0x4C, m_executeAnimationFades
// +0x50.  The two masks are the 192-bit BitFlags the rest of the engine uses
// (see ClosestKindOfDataConstructor.cpp), and they are the only members whose
// construction is a sub-object clear.
//
// Retail builds the two masks first (each one lea's its own base and stores six
// dwords off it), then the three Bools, then m_pickupScience (-1), then
// m_executeFX, then copy-constructs the animation template from the global
// empty AsciiString at 0x01336E50, and only then writes the two Reals and the
// trailing Bool from the constructor body.  The one unwind-state store sits
// immediately before the string call, because nothing before it can throw.

#include "ascii_string.h"
#include <string.h>

typedef unsigned int UnsignedInt;
typedef float Real;
typedef unsigned char Bool;

class FXList;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/BitFlags.h
template <int NUMBITS>
class BitFlags
{
public:
	BitFlags() { clear(); }

	void clear() { memset(this, 0, sizeof(*this)); }

private:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<192> KindOfMaskType;

// The shared narrow empty string, retail 0x01336E50
// (??Rva01336E50EmptyString@@3VAsciiString@@B).
extern const AsciiString Rva01336E50EmptyString;

// CollideModuleData / BehaviorModuleData / ModuleData contribute the vptr and
// the four bytes before m_kindof; the base's own virtuals are the seventeen
// ModuleData slots the vtable 0x010AA378 holds.
class BfmeCrateCollideModuleDataBase
{
public:
	// Out of line and virtual: it is the vtable's slot zero and the only reason
	// this constructor carries an SEH frame at all.
	virtual ~BfmeCrateCollideModuleDataBase();
	virtual void bfmeSlot01();

private:
	char m_bfmePad[0x08 - 0x04];
};

class CrateCollideModuleData : public BfmeCrateCollideModuleDataBase
{
public:
	CrateCollideModuleData();

private:
	KindOfMaskType m_kindof;								// +0x08
	KindOfMaskType m_kindofnot;							// +0x20
	Bool m_isForbidOwnerPlayer;							// +0x38
	Bool m_isBuildingPickup;								// +0x39
	Bool m_isHumanOnlyPickup;							// +0x3A
	int m_pickupScience;									// +0x3C
	FXList *m_executeFX;									// +0x40
	AsciiString m_executionAnimationTemplate;			// +0x44
	Real m_executeAnimationDisplayTimeInSeconds;			// +0x48
	Real m_executeAnimationZRisePerSecond;				// +0x4C
	Bool m_executeAnimationFades;						// +0x50
};

// ??0CrateCollideModuleData@@QAE@XZ
CrateCollideModuleData::CrateCollideModuleData()
	: m_isForbidOwnerPlayer(0),
	  m_isBuildingPickup(0),
	  m_isHumanOnlyPickup(0),
	  m_pickupScience(-1),
	  m_executeFX(0),
	  m_executionAnimationTemplate(Rva01336E50EmptyString)
{
	m_executeAnimationDisplayTimeInSeconds = 0.0f;
	m_executeAnimationZRisePerSecond = 0.0f;
	m_executeAnimationFades = 1;
}
