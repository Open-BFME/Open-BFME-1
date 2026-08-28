// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: BloodthirstyUpdateModuleData's constructor, retail 0x00286EC0,
// 119 bytes. The body carried only a machine byte-dump row;
// reverse/reloc_names.csv holds the name with identity=real.
//
// The base leaves no call, only the derived vtable store. Three members follow
// in declaration order: the four-byte one at +0x08 through the same constructor
// Made001E6170 uses, then two 0x70-byte ones at +0x10 and +0x80, each built
// from the global AsciiString at 0x01336E50 -- the one the UnitCrateCollide
// module data also assigns from -- and a zero. The word at +0x0C is set to one
// afterwards, in the body.
//
// The unwind slot counts 0, 1, 2, and the first of those is written before the
// first member is even built: that state covers the base, so the base has a
// destructor of its own. Without one the count starts a step late.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	char *m_bfmeData;
};

extern AsciiString TheBfmeCrateNameDefault;			// 0x01336E50

class RS_Member
{
public:
	RS_Member();						// ILT 0x0003747A
	~RS_Member();

private:
	void *m_bfmeData;
};

class BfmeNamedSlot
{
public:
	BfmeNamedSlot(const AsciiString &name, Int flags);	// ILT 0x00025306
	~BfmeNamedSlot();

private:
	char m_bfmeBody[0x70];
};

class BfmeUpdateModuleDataBase
{
public:
	~BfmeUpdateModuleDataBase();

	virtual void slot();

private:
	char m_bfmePad[0x08 - 0x04];
};

class BloodthirstyUpdateModuleData : public BfmeUpdateModuleDataBase
{
public:
	BloodthirstyUpdateModuleData();

	virtual void slot();

private:
	RS_Member m_bfmeMember;					// +0x08
	Int m_bfme0C;						// +0x0C
	BfmeNamedSlot m_bfmeFirst;				// +0x10
	BfmeNamedSlot m_bfmeSecond;				// +0x80
};

// ??0BloodthirstyUpdateModuleData@@QAE@XZ
BloodthirstyUpdateModuleData::BloodthirstyUpdateModuleData() :
	m_bfmeFirst(TheBfmeCrateNameDefault, 0),
	m_bfmeSecond(TheBfmeCrateNameDefault, 0)
{
	m_bfme0C = 1;
}
