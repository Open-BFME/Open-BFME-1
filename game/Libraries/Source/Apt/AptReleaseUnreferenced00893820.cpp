// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// bfmeCall936F(int), retail 0x00893820 (314 bytes): walk the Apt
// character-instance registry at 0x01337814 from the back and drop every
// instance whose flags mark it as loaded with no external references
// (0x40000 of the 0xC0000 pair), unless it is still referenced and the caller
// does not force it. The instance leaves the registry (inline remove: shift
// the tail down, clear the vacated slot), its file handle at state+0x34 is
// marked state 4 and released, the GC root bits are cleared, the state object
// is deleted through its virtual destructor and the Apt dirty flag is set.
//
// The matched callers pass the int: BfmeConv936.cpp passes 0 and the Apt
// shutdown dup_00894A90 passes 1. The Open BFME 2 donor
// Code/Libraries/Source/Apt/rva006CE1C0Rva006CE1C0Farm.cpp (45afcff3) is the
// later version of the same sweep (it adds zombie warnings and an out-of-line
// remove). The unwind action of the empty handle temporary is the
// RefHandle008958D0 destructor at 0x00784A70 (identity_evidence
// 00784a70-refhandle008958d0-dtor.md).

class Rva00894D90Accessor
{
public:
	static unsigned decrement(unsigned *);
};
void bfmeDropA(void *);

class RefHandle008958D0
{
public:
	RefHandle008958D0() : m_value(0) {}
	~RefHandle008958D0()
	{
		if (m_value && Rva00894D90Accessor::decrement(m_value) == 0)
			bfmeDropA(m_value);
	}
	RefHandle008958D0 &operator=(const RefHandle008958D0 &other)
	{
		if (&other != this)
		{
			if (m_value && Rva00894D90Accessor::decrement(m_value) == 0)
				bfmeDropA(m_value);
			m_value = other.m_value;
		}
		return *this;
	}
	unsigned *m_value;
};

struct Rva00893820File
{
	int m_refs;
	int m_size;
	int m_state;
};

struct State008C3F10
{
	virtual void slot00();
	virtual ~State008C3F10();
	char m_gap04[0x30];
	RefHandle008958D0 m_file;			// +0x34
};

class Rva008C3F10Value
{
public:
	char m_gap00[4];
	unsigned field04;
	char m_gap08[0x48];
	State008C3F10 *field50;
	char m_gap54[0xc];
	unsigned field60;
};

extern "C" void *__cdecl memmove(void *, const void *, unsigned int);

struct Registry008C3F10
{
	int field00;
	int field04;
	Rva008C3F10Value **field08;

	void removeAt(int index)
	{
		int count = --field04;
		if (count != 0 && index != count)
			memmove(&field08[index], &field08[index + 1], (count - index) * sizeof(Rva008C3F10Value *));
		field08[field04] = 0;
	}
};

extern Registry008C3F10 *g_registry01337814;
extern unsigned char g_rva0133780C;

// ?bfmeCall936F@@YAXH@Z
void bfmeCall936F(int force)
{
	for (int i = g_registry01337814->field04 - 1; i >= 0; --i)
	{
		Rva008C3F10Value *value = g_registry01337814->field08[i];
		unsigned flags = value->field60;
		if ((flags & 0xc0000) == 0x40000 && ((unsigned char)force || !(flags & 0xffff)))
		{
			State008C3F10 *state = value->field50;
			g_registry01337814->removeAt(i);
			value->field60 &= 0xfff3ffff;
			((Rva00893820File *)state->m_file.m_value)->m_state = 4;
			state->m_file = RefHandle008958D0();
			value->field04 &= 0xffffc03f;
			delete value->field50;
			value->field50 = 0;
			g_rva0133780C = 1;
		}
	}
}
