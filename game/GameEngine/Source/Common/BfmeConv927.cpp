// Open-BFME5 conversions.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

void __cdecl operator delete(void *p);

// Retail calls these ILTs, whose ledger definitions retain their thunk names.
// Each target takes only this in ECX, also the one-argument fastcall ABI.
extern void j_0004278a(); // -> 0x0037DCA0, list clear
extern void j_00036e9e(); // -> 0x0048F3E0, BfmeObj927B destructor
extern void j_0003418f(); // -> 0x0053ADC0, virtual-base destructor
extern void j_0002987a(); // -> 0x005C7180, virtual-base destructor
extern void j_000414bb(); // -> 0x00538210, basic_ios<char> destructor

// The 0x012F12CC singleton is DisplayStringManager *TheDisplayStringManager,
// defined once in DisplayStringManager.cpp.  This TU keeps its own view of
// the vtable and casts at the use.
class DisplayStringManager;

class Rva0048EC80Manager
{
public:
	virtual void bfmeSlot00E927B();
	virtual void bfmeSlot01E927B();
	virtual void bfmeSlot02E927B();
	virtual void bfmeSlot03E927B();
	virtual void bfmeSlot04E927B();
	virtual void bfmeSlot05E927B();
	virtual void bfmeSlot06E927B();
	virtual void bfmeSlot07E927B();
	virtual void bfmeSlot08E927B();
	virtual void bfmeSlot09E927B();
	virtual void bfmeRelease927B(void *item);
};

extern DisplayStringManager *TheDisplayStringManager;
static inline Rva0048EC80Manager *theDisplayStringManagerView()
{
	return (Rva0048EC80Manager *)TheDisplayStringManager;
}

class BfmeSub927A
{
public:
	void *m_bfmeP;
};

class BfmeThing927A
{
public:
	void bfmeGo927A();
	int m_bfmePad;
	BfmeSub927A m_bfmeSub;
};

void BfmeThing927A::bfmeGo927A()
{
	BfmeSub927A *s = &m_bfmeSub;
	reinterpret_cast<void (__fastcall *)(BfmeSub927A *)>(j_0004278a)(s);
	void *p = s->m_bfmeP;
	if (p)
		operator delete(p);
}

class BfmeObj927BEntry
{
public:
	unsigned char m_bfmePad[4];
	void *m_bfmeDisplayString;
};

class BfmeObj927B
{
public:
	~BfmeObj927B();

private:
	_STL::vector<BfmeObj927BEntry *> m_bfmeEntries;
};

BfmeObj927B::~BfmeObj927B()
{
	for (unsigned int i = 0; i < m_bfmeEntries.size(); ++i)
	{
		BfmeObj927BEntry *entry = m_bfmeEntries[i];
		if (entry != 0)
		{
			if (entry->m_bfmeDisplayString != 0)
			{
				theDisplayStringManagerView()->bfmeRelease927B(entry->m_bfmeDisplayString);
				entry->m_bfmeDisplayString = 0;
			}

			operator delete(entry);
		}
	}

	m_bfmeEntries.clear();
}

void __stdcall bfmeGo927B(BfmeObj927B *p)
{
	if (p) {
		reinterpret_cast<void (__fastcall *)(BfmeObj927B *)>(j_00036e9e)(p);
		operator delete(p);
	}
}

class BfmeThing927C
{
public:
	void *bfmeGo927C(unsigned int flags);
};

void *BfmeThing927C::bfmeGo927C(unsigned int flags)
{
	char *base = (char *)this - 0x74;
	BfmeThing927C *self = (BfmeThing927C *)(base + 0x74);
	reinterpret_cast<void (__fastcall *)(BfmeThing927C *)>(j_0003418f)(self);
	reinterpret_cast<void (__fastcall *)(BfmeThing927C *)>(j_000414bb)(self);
	if (flags & 1)
		operator delete(base);
	return base;
}

class BfmeThing927D
{
public:
	void *bfmeGo927D(unsigned int flags);
};

void *BfmeThing927D::bfmeGo927D(unsigned int flags)
{
	char *base = (char *)this - 0x70;
	BfmeThing927D *self = (BfmeThing927D *)(base + 0x70);
	reinterpret_cast<void (__fastcall *)(BfmeThing927D *)>(j_0002987a)(self);
	reinterpret_cast<void (__fastcall *)(BfmeThing927D *)>(j_000414bb)(self);
	if (flags & 1)
		operator delete(base);
	return base;
}

struct BfmeVt927E
{
	char m_bfmePad[8];
	void (__stdcall *m_bfmeFn)(void *o);
};

struct BfmeSub927E
{
	BfmeVt927E *m_bfmeVt;
};

// Retail stores this vftable at 0x0113A56C; the defining mangled name is
// ??_7Rva0090C2F0Inner@@6B@, which C++ cannot spell, so take it verbatim.
extern "C" char __identifier("??_7Rva0090C2F0Inner@@6B@")[];

class BfmeThing927E
{
public:
	void *bfmeGo927E(unsigned int flags);
	char *m_bfmeVft;
	int m_bfmePad;
	BfmeSub927E *m_bfmeSub;
};

void *BfmeThing927E::bfmeGo927E(unsigned int flags)
{
	BfmeSub927E *s = m_bfmeSub;
	m_bfmeVft = __identifier("??_7Rva0090C2F0Inner@@6B@");
	if (s)
		s->m_bfmeVt->m_bfmeFn(s);
	if (flags & 1)
		operator delete(this);
	return this;
}
