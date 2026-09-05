// cl: /DNDEBUG /MD /EHsc
//
// Rva003C1A50Tick::tick, retail 0x003C03C0, 238 bytes.
//
// Same object as Rva003C1A50::run / Rva003BCA90::run / BfmeB1003: first-time
// report, +0x7C countdown (return while still positive), then +0xCC expiry.

extern const char g_bfmeEmptyAscii[];

class Glo012F706CType
{
public:
	unsigned char m_unmodelled_000[0x288];
	unsigned char m_flag;
};

extern Glo012F706CType *g_bfmeGameCW;

class Gen003C8A50Result;

class Gen003C8A50
{
public:
	Gen003C8A50Result *find(const char *key);
	void updateConqueredEffects003C7130(Gen003C8A50Result *found);
};

class Gen_003C63A0
{
public:
	int *bfmeField() const;
};

class BfmeThingAZB
{
public:
	void bfmeSetAZB(void *what);
};

class BfmeThingATB
{
public:
	void bfmeGoATB();
};

class BfmeOneCHF
{
public:
	void bfmeOneCHF();
};

class BfmeB1003
{
public:
	void bfmeClear1003();
	void bfmeFinish1003();
};

class Rva003BCA90
{
public:
	void run();
};

void __cdecl bfmeNamedAudio0046F1A0(const char *text);

#define TheThingAZB (*(BfmeThingAZB **)0x012F4B78)
#define TheThingATB (*(BfmeThingATB **)0x012F4B78)
#define TheLivingWorld (*(BfmeOneCHF **)0x012F1024)

class Rva003C1A50Tick
{
public:
	void tick();

private:
	char m_pad00[0x28];
	Gen003C8A50 *m_at28;
	char m_pad2C[4];
	char m_at30;
	char m_pad31[0x78 - 0x31];
	unsigned char m_at78;
	char m_pad79[0x7C - 0x79];
	int m_at7C;
	unsigned char m_at80;
	char m_pad81[0xC8 - 0x81];
	unsigned char m_atC8;
	char m_padC9[0xCC - 0xC9];
	int m_atCC;
};

static const char *nameOf(void **slot)
{
	void *data = *slot;
	if (data)
		return (const char *)data + 8;
	return g_bfmeEmptyAscii;
}

// ?tick@Rva003C1A50Tick@@QAEXXZ
void Rva003C1A50Tick::tick()
{
	if (!m_at78)
		return;

	if (m_atC8)
	{
		if (g_bfmeGameCW->m_flag)
			return;
		m_atC8 = 0;
		((Rva003BCA90 *)this)->run();
	}

	if (m_at7C > 0)
	{
		int left = m_at7C - 1;
		m_at7C = left;
		if (left > 0)
			return;
		Gen003C8A50Result *found = m_at28->find(&m_at30);
		TheThingAZB->bfmeSetAZB(found);
		bfmeNamedAudio0046F1A0(nameOf((void **)((Gen_003C63A0 *)m_at28)->bfmeField()));
	}

	if (m_atCC)
		--m_atCC;
	if (m_atCC)
		return;

	m_at78 = 0;
	Gen003C8A50Result *found = m_at28->find(&m_at30);
	if (found)
		m_at28->updateConqueredEffects003C7130(found);

	if (m_at80)
	{
		TheLivingWorld->bfmeOneCHF();
		((BfmeB1003 *)this)->bfmeClear1003();
	}

	((BfmeB1003 *)this)->bfmeFinish1003();
	TheThingATB->bfmeGoATB();
}
