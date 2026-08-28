// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: WaterTransparencySetting::operator=, retail 0x000C3660, 113
// bytes. The body carried only a machine byte-dump row;
// reverse/reloc_names.csv holds the name with identity=real.
//
// Memberwise, and the same base assignment CommandSet and CrateTemplate use:
// two words at +0x0C and +0x10 copied straight, then twelve bytes at +0x14 and
// another twelve at +0x20 copied through a base pointer at each end, a byte at
// +0x2C, the AsciiString at +0x30 through its own assignment, and three more
// words from +0x34.
//
// The two twelve-byte runs are nested structs rather than three members each:
// written as members the compiler folds the offsets onto the objects and drops
// the leas, which is what CrateTemplate::operator= at 0x0037A1A0 already showed.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);	// retail 0x00887C90

private:
	char *m_bfmeData;
};

class ScienceInfoBase
{
public:
	ScienceInfoBase &operator=(const ScienceInfoBase &other); // ILT 0x00048725

private:
	char m_bfmeHead[0x0C];
};

struct BfmeWaterTriple
{
	Int m_bfmeA, m_bfmeB, m_bfmeC;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Water.h
class WaterTransparencySetting : public ScienceInfoBase
{
public:
	WaterTransparencySetting &operator=(const WaterTransparencySetting &other);

private:
	Int m_bfme0C;						// +0x0C
	Int m_bfme10;						// +0x10
	BfmeWaterTriple m_bfme14;				// +0x14
	BfmeWaterTriple m_bfme20;				// +0x20
	char m_bfme2C;						// +0x2C
	char m_bfmePad2D[3];
	AsciiString m_bfmeName;					// +0x30
	Int m_bfme34;						// +0x34
	Int m_bfme38;						// +0x38
	Int m_bfme3C;						// +0x3C
};

// ??4WaterTransparencySetting@@QAEAAV0@ABV0@@Z
WaterTransparencySetting &WaterTransparencySetting::operator=(
		const WaterTransparencySetting &other)
{
	ScienceInfoBase::operator=(other);

	m_bfme0C = other.m_bfme0C;
	m_bfme10 = other.m_bfme10;
	m_bfme14 = other.m_bfme14;
	m_bfme20 = other.m_bfme20;
	m_bfme2C = other.m_bfme2C;
	m_bfmeName = other.m_bfmeName;
	m_bfme34 = other.m_bfme34;
	m_bfme38 = other.m_bfme38;
	m_bfme3C = other.m_bfme3C;

	return *this;
}
