// cl: /O2 /Ob0
// BFME retail 1.03 RVA 0x008BDD70 (172 bytes).
// Walks a singly linked list of entries owned by a table object. Entries that
// have bit 15 of their flags set are unregistered from their owner's lookup
// when the lookup still maps their name back to them, and then released. When
// the flag argument is set the entry also loses flags 0x3fc0 and is cleaned up.
// The idle hook steps once per entry while no stack is active. The pin
// bfmeReset1046 names this address and the matched callers
// BfmeD1046::bfmeGo1046D and bfmeGo1046E call it with a zero argument.

struct BfmeStringData3AF0;
extern BfmeStringData3AF0 g_bfmeDefaultString1284;

struct BfmeKey1279
{
	void *m_data;
};

class BfmeLookup1279
{
public:
	void bfmeErase1279(BfmeKey1279 &key);
};

class BfmeTab1024
{
public:
	int bfmeFind1024(int key);
};

class BfmeObj4310
{
public:
	void bfmeDrop(void);
};

class Rva008C3F10Value
{
public:
	void cleanup(char mode);
};

class BfmeG1211
{
public:
	void bfmeStep1211C(void);
};

// Local view of the pool global's layout at 0x01337810; the canonical
// declaration of that global is `struct Rva00899560Pool *g_rva01337810GcRoots`
// (defined once in game/Libraries/Source/Apt/Apt.cpp), so only the view lives
// here and every use casts.
struct Rva008BDD70IdleHookView
{
	char m_pad00[4];
	int m_at04;
};

struct Rva00899560Pool;

struct Rva008AE770Stack
{
	int m_at00;
};

extern Rva00899560Pool *g_rva01337810GcRoots;
extern Rva008AE770Stack Rva008AE770TheStack;

class Rva008BDD70Owner
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0C(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual BfmeTab1024 *table(void);
};

struct Rva008BDD70Entry
{
	char m_pad00[4];
	unsigned int m_flags;
	char m_pad08[4];
	BfmeKey1279 m_name;
	char m_pad10[0x3c];
	Rva008BDD70Owner *m_owner;
	char m_pad50[8];
	Rva008BDD70Entry *m_next;
};

struct Rva008BDD70List
{
	char m_pad00[0x58];
	Rva008BDD70Entry *m_head;
};

struct Rva008BDD70Holder
{
	Rva008BDD70List *m_list;
};

class BfmeD1046
{
public:
	void bfmeReset1046(int n);

	Rva008BDD70Holder *m_holder;
};

void BfmeD1046::bfmeReset1046(int n)
{
	if (m_holder == 0)
		return;

	Rva008BDD70Entry *entry = m_holder->m_list->m_head;
	while (entry != 0)
	{
		Rva008BDD70Entry *next = entry->m_next;
		unsigned char bit = (unsigned char)(entry->m_flags >> 15);
		bit = (unsigned char)~bit;
		if ((bit & 1) == 0)
		{
			if (entry->m_owner != 0)
			{
				BfmeTab1024 *tab = entry->m_owner->table();
				if (entry->m_name.m_data != &g_bfmeDefaultString1284 && tab != 0)
				{
					if ((Rva008BDD70Entry *)tab->bfmeFind1024((int)&entry->m_name) == entry)
						((BfmeLookup1279 *)tab)->bfmeErase1279(entry->m_name);
				}
			}
			((BfmeObj4310 *)entry)->bfmeDrop();
		}
		if ((char)n != 0)
		{
			entry->m_flags &= 0xffffc03f;
			((Rva008C3F10Value *)entry)->cleanup(1);
		}
		if (((Rva008BDD70IdleHookView *)g_rva01337810GcRoots)->m_at04 != 0 && Rva008AE770TheStack.m_at00 == 0)
			((BfmeG1211 *)g_rva01337810GcRoots)->bfmeStep1211C();
		entry = next;
	}
}
