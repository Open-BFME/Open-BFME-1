// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Rva003C1A50Tick::tick, retail 0x003C03C0, 238 bytes.
//
// Same object as Rva003C1A50::run / Rva003BCA90::run / BfmeB1003: first-time
// report, +0x7C countdown (return while still positive), then +0xCC expiry.

extern const char g_bfmeEmptyAscii[];

// The singleton at 0x012F706C is retail's ?g_bfmeGameCW@@3PAVBfmeGameCW@@A
// (dir32_addresses.csv). This TU only reads the +0x288 flag, so the class
// itself carries the defining name and no member is spelled here.
class BfmeGameCW
{
public:
	unsigned char m_unmodelled_000[0x288];
	unsigned char m_flag;
};

extern BfmeGameCW *g_bfmeGameCW;

#include "ascii_string.h"

class LivingWorldRegion;

class LivingWorldRegionManager
{
public:
	LivingWorldRegion *rva003C8A50(const AsciiString &key);
};

class Gen003C8A50Result;

class Gen003C8A50
{
public:
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

class Gen00587600;
class Gen00587600;
extern Gen00587600 *g_bfmeSubsystem012F4B78;
static inline BfmeThingATB *TheThingATBView() { return (BfmeThingATB *)g_bfmeSubsystem012F4B78; }
static inline BfmeThingAZB *TheThingAZBView() { return (BfmeThingAZB *)g_bfmeSubsystem012F4B78; }
class BfmeLivingWorldCampaignManager;
extern BfmeLivingWorldCampaignManager *TheLivingWorldCampaignManager;
static inline BfmeOneCHF *TheLivingWorldView() { return (BfmeOneCHF *)TheLivingWorldCampaignManager; }


class Rva003C1A50Tick
{
public:
	void tick();

private:
	char m_pad00[0x28];
	LivingWorldRegionManager *m_at28;
	char m_pad2C[4];
	AsciiString m_at30;
	char m_pad34[0x78 - 0x34];
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
		LivingWorldRegion *found = m_at28->rva003C8A50(m_at30);
		TheThingAZBView()->bfmeSetAZB(found);
		bfmeNamedAudio0046F1A0(nameOf((void **)((Gen_003C63A0 *)m_at28)->bfmeField()));
	}

	if (m_atCC)
		--m_atCC;
	if (m_atCC)
		return;

	m_at78 = 0;
	LivingWorldRegion *found = m_at28->rva003C8A50(m_at30);
	if (found)
		((Gen003C8A50 *)m_at28)->updateConqueredEffects003C7130(
			(Gen003C8A50Result *)found);

	if (m_at80)
	{
		TheLivingWorldView()->bfmeOneCHF();
		((BfmeB1003 *)this)->bfmeClear1003();
	}

	((BfmeB1003 *)this)->bfmeFinish1003();
	TheThingATBView()->bfmeGoATB();
}
