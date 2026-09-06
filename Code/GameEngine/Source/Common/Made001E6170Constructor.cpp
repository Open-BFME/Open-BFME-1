// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Made001E6170's constructor, retail 0x002DE930, 86 bytes. The body
// carried only a machine byte-dump row; reverse/reloc_names.csv holds the name
// with identity=real, and WeaponNuggetParse.cpp already declares the class -- one
// of the objects the 157-byte make-notify-and-link family allocates, and the one
// that file sizes at 0x6C.
//
// The base constructor runs, the derived vtable goes over the base one, the
// member at +0x58 is constructed through its own constructor, and the four words
// from +0x5C to +0x68 are cleared through the register that carried the zero.
//
// That member constructor is the only thing here that can throw, which is what
// gives the body an unwind frame at all: the state is written once, for the base,
// just before the call. Its sibling at 0x002DE130 has no such call and no frame.

typedef int Int;

class WeaponTemplate;

class GenBase002DF2B0
{
public:
	GenBase002DF2B0();					// retail 0x002DF2B0
	~GenBase002DF2B0();
	virtual void slot();

	char m_gap04[0x34 - 4];
	WeaponTemplate *m_owner;
	char m_gap38[0x54 - 0x38];
	char m_flag;
	char m_tail55[3];
};

class RS_Member
{
public:
	RS_Member();						// ILT 0x0003747A

private:
	void *m_bfmeData;
};

class Made001E6170 : public GenBase002DF2B0
{
public:
	__declspec(noinline) Made001E6170();
	virtual void slot();

private:
	RS_Member m_bfmeMember;					// +0x58
	Int m_bfme5C;						// +0x5C
	Int m_bfme60;						// +0x60
	Int m_bfme64;						// +0x64
	Int m_bfme68;						// +0x68
};

// ??0Made001E6170@@QAE@XZ
Made001E6170::Made001E6170()
{
	m_bfme5C = 0;
	m_bfme60 = 0;
	m_bfme64 = 0;
	m_bfme68 = 0;
}
