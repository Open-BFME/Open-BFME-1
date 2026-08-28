// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DamageInfo::operator=, retail 0x00150620.
//
// It confirms the +0x04 offset of the embedded input block independently of
// DamageInfoDestructorThunk.cpp: it hands DamageInfoInput::operator= the
// address `this+4`, and separately InactiveBody::estimateDamage at 0x00213B90
// reads m_damageType at +0xc of a DamageInfoInput where InactiveBody.cpp's
// DamageInfo spelling has the same field at +0x10.
//
// The output block is copied inline and field by field -- two dword moves and
// a byte move at 0x50, 0x54, 0x58 -- which fixes both its start and its shape:
// two Reals and a Bool. Whether the source said `out = other.out` or spelled
// the three assignments out is not observable, but a whole-struct assignment
// compiles to a twelve-byte move that copies the Bool's padding as a dword, so
// the fields are assigned individually here to keep the byte move.
//
// One thing this body says that the destructor does not: it never touches
// this+0. An implicit operator= would copy any base data member there, and
// never copies a vtable pointer -- so either those four bytes ARE a vptr, or
// this operator= is user-written and skips the base on purpose. The
// destructor's reading is the first of those two, argued from the absence of a
// vptr store; the two are not yet reconciled, so the four bytes are left
// unnamed here rather than committed either way.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfoInput
{
public:
	// ??4DamageInfoInput@@QAEAAV0@ABV0@@Z, ILT 0x0000617C
	DamageInfoInput &operator=(const DamageInfoInput &other);

private:
	char m_unreconstructed_00[0x4c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfoOutput
{
public:
	float m_actualDamageDealt;						///< retail DamageInfo+0x50
	float m_actualDamageClipped;					///< retail DamageInfo+0x54
	bool m_noEffect;								///< retail DamageInfo+0x58
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
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
