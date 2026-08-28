// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: EvacuateDamageModuleData's constructor, retail 0x00250C20, 101
// bytes. The body carried only a machine byte-dump row; reverse/reloc_names.csv
// holds the name with identity=real.
//
// The base leaves no call of its own, only the derived vtable store. The
// AsciiString at +0x08 is constructed -- its null -- and then cleared, which is
// an explicit call in the body: both land on the same address, and the unwind
// slot separates them, standing at 0 while only the base is up and stepping to
// 1 once the string is.
//
// Three fields follow: three at +0x0C, 0.1f at +0x10 and six at +0x14.

typedef int Int;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() { m_bfmeData = 0; }
	~AsciiString();						// retail 0x00887940

	void clear();						// same body

private:
	char *m_bfmeData;
};

class BfmeDamageModuleDataBase
{
public:
	~BfmeDamageModuleDataBase();

	virtual void slot();

private:
	char m_bfmePad[0x08 - 0x04];
};

class EvacuateDamageModuleData : public BfmeDamageModuleDataBase
{
public:
	EvacuateDamageModuleData();

	virtual void slot();

private:
	AsciiString m_bfmeName;					// +0x08
	Int m_bfme0C;						// +0x0C
	Real m_bfme10;						// +0x10
	Int m_bfme14;						// +0x14
};

// ??0EvacuateDamageModuleData@@QAE@XZ
EvacuateDamageModuleData::EvacuateDamageModuleData()
{
	m_bfmeName.clear();

	m_bfme0C = 3;
	m_bfme10 = 0.1f;
	m_bfme14 = 6;
}
