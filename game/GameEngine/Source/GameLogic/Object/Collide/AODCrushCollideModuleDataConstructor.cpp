// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AODCrushCollideModuleData's constructor, retail 0x00215B90, 126
// bytes. The body carried only a machine byte-dump row; targets/game/reverse/reloc_names.csv
// holds the name with identity=real.
//
// The base leaves no call, only the derived vtable store, and it has a
// destructor -- the unwind state is written before anything is built, which is
// what covers it.
//
// Everything from +0x08 to +0x28 is set before the member at +0x2C is
// constructed, so those are initialiser-list entries; everything from +0x30 on
// is set after, so those are body assignments. Within the body the zeros keep
// source order and the two ones follow, which is the order the bytes have.

typedef int Int;

class RS_Member
{
public:
	RS_Member();						// ILT 0x0003747A
	~RS_Member();

private:
	void *m_bfmeData;
};

class BfmeCollideModuleDataBase
{
public:
	~BfmeCollideModuleDataBase();

	virtual void slot();

private:
	char m_bfmePad[0x08 - 0x04];
};

class AODCrushCollideModuleData : public BfmeCollideModuleDataBase
{
public:
	AODCrushCollideModuleData();

	virtual void slot();

private:
	Int m_bfme08;						// +0x08
	Int m_bfme0C;						// +0x0C
	Int m_bfme10;						// +0x10
	Int m_bfme14;						// +0x14
	Int m_bfme18;						// +0x18
	Int m_bfme1C;						// +0x1C
	Int m_bfme20;						// +0x20
	Int m_bfme24;						// +0x24
	Int m_bfme28;						// +0x28
	RS_Member m_bfmeMember;					// +0x2C
	Int m_bfme30;						// +0x30
	Int m_bfme34;						// +0x34
	Int m_bfme38;						// +0x38
	Int m_bfme3C;						// +0x3C
	Int m_bfme40;						// +0x40
	Int m_bfme44;						// +0x44
};

// ??0AODCrushCollideModuleData@@QAE@XZ
AODCrushCollideModuleData::AODCrushCollideModuleData() :
	m_bfme08(0),
	m_bfme0C(0),
	m_bfme10(0),
	m_bfme14(0),
	m_bfme18(0),
	m_bfme1C(0),
	m_bfme20(1),
	m_bfme24(0),
	m_bfme28(0)
{
	m_bfme34 = 0;
	m_bfme38 = 0;
	m_bfme40 = 0;
	m_bfme44 = 0;
	m_bfme30 = 1;
	m_bfme3C = 1;
}
