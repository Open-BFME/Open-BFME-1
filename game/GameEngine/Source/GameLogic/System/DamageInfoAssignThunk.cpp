// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DamageInfo::operator=, retail 0x00150620.
//
// It confirms the +0x04 offset of the embedded input block: it hands
// DamageInfoInput::operator= the address this+4. Independently, the matched
// constructor at 0x000ED430 places output at +0x4C, and InactiveBody's damage
// estimate reads the same input field offsets. The old 0x000C3410 destructor
// attribution was disproved: that body destroys a 28-byte Video record.
//
// The output block is copied inline and field by field -- two dword moves and
// a byte move at 0x50, 0x54, 0x58 -- which fixes both its start and its shape:
// two Reals and a Bool. Whether the source said `out = other.out` or spelled
// the three assignments out is not observable, but a whole-struct assignment
// compiles to a twelve-byte move that copies the Bool's padding as a dword, so
// the fields are assigned individually here to keep the byte move.
//
// This assignment does not touch this+0. The constructor independently
// establishes a vptr there; no destructor-layout inference is needed.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfoInput
{
public:
	// ??4DamageInfoInput@@QAEAAV0@ABV0@@Z, ILT 0x0000617C
	DamageInfoInput &operator=(const DamageInfoInput &other);

private:
	char m_unreconstructed_00[0x4c];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfoOutput
{
public:
	float m_actualDamageDealt;						///< retail DamageInfo+0x50
	float m_actualDamageClipped;					///< retail DamageInfo+0x54
	bool m_noEffect;								///< retail DamageInfo+0x58
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfo
{
public:
	DamageInfo &operator=(const DamageInfo &other);

private:
	char m_unreconstructed_00[4];					///< untouched by this body
	DamageInfoInput in;								///< retail this+0x04
	DamageInfoOutput out;							///< retail this+0x50
};

// ??4DamageInfo@@QAEAAV0@ABV0@@Z
DamageInfo &DamageInfo::operator=(const DamageInfo &other)
{
	in = other.in;
	out.m_actualDamageDealt = other.out.m_actualDamageDealt;
	out.m_actualDamageClipped = other.out.m_actualDamageClipped;
	out.m_noEffect = other.out.m_noEffect;
	return *this;
}
