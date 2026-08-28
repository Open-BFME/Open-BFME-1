// cl: /DNDEBUG /MD /EHsc
// DamageInfoInput::operator=, retail 0x0014FDC0, 127 bytes.
//
// The compiler-generated memberwise copy for a POD struct: DamageInfoAssignThunk.cpp
// already proves this+0 is untouched (skipped, 4 bytes) and the field at +0x50 of the
// enclosing DamageInfo is this+4c end. Field sizes/offsets read straight off the
// retail instruction widths (dword/word/byte moves), not yet given real names.
//
// +0x2c is a 12-byte nested struct, not three plain ints: retail copies it through a
// pointer pair (lea+mov, push esi/edi) rather than three direct [ecx+off]/[eax+off]
// moves, and only spelling it as a nested aggregate here reproduces that shape.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfoInput
{
public:
	char m_00[4];		// +0x00, untouched by operator=
	int m_04;		// +0x04
	short m_08;		// +0x08
	char m_0a[2];		// +0x0a .. +0x0b, untouched padding
	int m_0c;		// +0x0c
	int m_10;		// +0x10
	int m_14;		// +0x14
	int m_18;		// +0x18
	char m_1c;		// +0x1c
	char m_1d;		// +0x1d
	char m_1e[2];		// +0x1e .. +0x1f, untouched padding
	int m_20;		// +0x20
	int m_24;		// +0x24
	int m_28;		// +0x28
	struct { int a, b, c; } m_2c;	// +0x2c .. +0x37
	int m_38;		// +0x38
	int m_3c;		// +0x3c
	int m_40;		// +0x40
	int m_44;		// +0x44
	char m_48[4];		// +0x48 .. +0x4b, untouched tail padding

	DamageInfoInput &operator=(const DamageInfoInput &other);
};

// ??4DamageInfoInput@@QAEAAV0@ABV0@@Z
DamageInfoInput &DamageInfoInput::operator=(const DamageInfoInput &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0c = other.m_0c;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1c = other.m_1c;
	m_1d = other.m_1d;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_28 = other.m_28;
	m_2c = other.m_2c;
	m_38 = other.m_38;
	m_3c = other.m_3c;
	m_40 = other.m_40;
	m_44 = other.m_44;
	return *this;
}
