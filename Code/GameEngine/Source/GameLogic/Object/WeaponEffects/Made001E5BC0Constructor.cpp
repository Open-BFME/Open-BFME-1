// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Made001E5BC0's constructor, retail 0x002DE130, 36 bytes. The body
// carried only a machine byte-dump row; reverse/reloc_names.csv holds the name
// with identity=real, and WeaponNuggetParse.cpp is where the class it belongs to
// is declared -- one of the objects the 157-byte make-notify-and-link family
// allocates.
//
// The base constructor runs, the derived vtable goes over the base one, and the
// four words of tail are set: zero at +0x58, +0x5C and +0x64 and pi at +0x60.
// The four are assignments in the constructor body, not a tail member with its
// own constructor: with a member the vptr store stays pinned ahead of them,
// while here the compiler is free to group the three zeros around one register
// and to leave the vtable with pi among the immediates, which is the order
// retail records.

typedef int Int;
typedef float Real;

class WeaponTemplate;

class GenBase002DF2B0
{
public:
	GenBase002DF2B0();					// retail 0x002DF2B0
	virtual void slot();

	char m_gap04[0x34 - 4];
	WeaponTemplate *m_owner;
	char m_gap38[0x54 - 0x38];
	char m_flag;
	char m_tail55[3];
};

class Made001E5BC0 : public GenBase002DF2B0
{
public:
	__declspec(noinline) Made001E5BC0();
	virtual void slot();

private:
	Int m_58, m_5c;
	Real m_60;
	Int m_64;
};

// ??0Made001E5BC0@@QAE@XZ
Made001E5BC0::Made001E5BC0()
{
	m_58 = 0;
	m_5c = 0;
	m_60 = 3.14159274f;
	m_64 = 0;
}
