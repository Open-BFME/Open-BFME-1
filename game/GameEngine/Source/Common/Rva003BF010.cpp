// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Rva003BF540::run, retail 0x003BF010, 303 bytes.
//
// d_003b8450: disabled/anyReady early-out; +0x4C hold path decrements +0x48
// from 15 then notifyTarget on Glo012F4B98; else isOpen+allowed then hold
// the arg at +0xC4 until count 0x2D and a non-empty name at arg+0x34.

#include "string_base.h"

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other)
		: StringBase<char>(other)
	{
	}
	~AsciiString() {}
	bool isEmpty() const;
};

class Gen_00609320
{
public:
	int bfmeDisabled() const;
};

// Retail 0x012F7048 is ?g_rva012F7048LivingWorld@@3PAVRva006092D0State@@A (data_rows.csv,
// GameClient/LivingWorld.cpp); g_bfmeStateDF was only a pin.
class Rva006092D0State;
extern Rva006092D0State *g_rva012F7048LivingWorld;
#define g_bfmeStateDF ( *(Gen_00609320 **)&g_rva012F7048LivingWorld )

// Native entries reached through ILTs 0x000371C3 and 0x00043E4B.
class Rva00589620
{
public:
	void notifyTarget();
};

class Rva00592D60Owner
{
public:
	void update(int value, int state);
};

class AptPalantir;
extern AptPalantir *TheAptPalantir;

// The singleton at 0x012F706C is retail's ?g_bfmeGameCW@@3PAVBfmeGameCW@@A
// (dir32_addresses.csv). Preserve the global declaration and use the native
// campaign predicate view for the call through ILT 0x000485D1.
class BfmeGameCW;

class Rva0060D480CampaignGate
{
public:
	bool isOpen() const;
};

// Retail 0x012F706C is ?TheLivingWorldManager@@3PAVLivingWorldManager@@A (data_rows.csv,
// LivingWorld/LivingWorldManager.cpp); g_bfmeGameCW was only a pin.
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
#define g_bfmeGameCW ( *(BfmeGameCW **)&TheLivingWorldManager )

class Rva003BF010Arg
{
public:
	char m_pad[0x34];
	AsciiString m_name;
};

// ILT 0x00025A77 targets the ledger-owned 0x003BED00 predicate.
class Rva003BDEC0
{
public:
	bool allowed();
};

// ILT 0x0000EA7F targets the native readiness scan at 0x003BD830.
class Rva003BD830Owner
{
public:
	bool anyReady() const;
};

class Rva003BF540
{
public:
	void run(Rva003BF010Arg *arg);

private:
	char m_pad00[0x48];
	int m_at48;
	unsigned char m_at4C;
	unsigned char m_at4D;
	char m_pad4E[0xC4 - 0x4E];
	Rva003BF010Arg *m_atC4;
};

void Rva003BF540::run(Rva003BF010Arg *arg)
{
	if (static_cast<unsigned char>(g_bfmeStateDF->bfmeDisabled()))
		return;
	if (reinterpret_cast<Rva003BD830Owner *>(this)->anyReady())
		return;

	if (m_at4C)
	{
		if (arg == m_atC4)
		{
			m_at4D = 0;
			return;
		}
		if (!m_at4D)
		{
			m_at48 = 15;
			m_at4D = 1;
		}
		if (--m_at48 > 0)
			return;
	}
	else if (reinterpret_cast<Rva0060D480CampaignGate *>(g_bfmeGameCW)->isOpen() && reinterpret_cast<Rva003BDEC0 *>(this)->allowed())
	{
		if (!arg)
			return;
		if (m_atC4 != arg)
		{
			m_at48 = 0;
			m_at4C = 0;
			m_at4D = 0;
			m_atC4 = arg;
		}
		if (++m_at48 <= 0x2D)
			return;
		{
			AsciiString copy(arg->m_name);
			if (!copy.isEmpty())
				reinterpret_cast<Rva00592D60Owner *>(TheAptPalantir)->update(reinterpret_cast<int>(&arg->m_name), 0);
			m_at4C = 1;
		}
		return;
	}
	else
		goto zero_fields;

	reinterpret_cast<Rva00589620 *>(TheAptPalantir)->notifyTarget();
zero_fields:
	m_atC4 = 0;
	m_at48 = 0;
	m_at4C = 0;
	m_at4D = 0;
}
