// ?reset_003855F0@Rva003855F0Owner@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /MD
// Retail 0x003855F0: transition called from GameLogic::logicMessageDispatcher.
// The original member name is unknown, so the owner and method keep the RVA.
// Calls through the existing ILT thunk symbols preserve each physical route.
// See targets/game/reverse/identity_evidence/0x003855f0-transition-call-routes.md.
extern void j_0002c8f9();
extern void j_00031313();
extern void j_00048068();

typedef int Int;

class BfmeSharedString
{
public:
	BfmeSharedString(const BfmeSharedString &other);
	~BfmeSharedString();
	void *m_data;
};

class Rva00361960
{
public:
	BfmeSharedString copyString();
	unsigned char m_bfmeBody[0x58];
};

class Rva00361D10Vector
{
public:
	int size() const { return m_end - m_begin; }
	Rva00361960 *begin() const { return m_begin; }

	Rva00361960 *m_begin;
	Rva00361960 *m_end;
};

class Rva003C0350
{
public:
	void run(void *key, void *src);
	void run(const BfmeSharedString &key, void *src)
	{
		run((void *)&key, src);
	}
};

class Rva00361D10Sub
{
public:
	void method_00361D10() const;

private:
	unsigned char m_bfmeHead[0x18];
	Rva00361D10Vector m_bfmeVectorTwo;
};
class BfmeLivingWorldManager
{
public:
	bool isCampaignVictorious();
};
class BfmeGameCW;
class Gen_00609320
{
public:
	char m_pad[8];
	bool m_flag;
};
class GameLogic
{
public:
	void clearGameData(const bool first, bool second);
};
class BfmeSubBZF
{
public:
	void bfmeOneBZF();
};
class Rva003BDC50
{
public:
	void run();
};
class Rva003BFAB0
{
public:
	void run(bool flag);
};
class Glo012F1028Type;
// Retail 0x012F706C is ?TheLivingWorldManager@@3PAVLivingWorldManager@@A (data_rows.csv,
// LivingWorld/LivingWorldManager.cpp); g_bfmeGameCW was only a pin.
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
#define g_bfmeGameCW ( *(BfmeGameCW **)&TheLivingWorldManager )
// Retail 0x012F7048 is ?g_rva012F7048LivingWorld@@3PAVRva006092D0State@@A (data_rows.csv,
// GameClient/LivingWorld.cpp); g_bfmeStateDF was only a pin.
class Rva006092D0State;
extern Rva006092D0State *g_rva012F7048LivingWorld;
#define g_bfmeStateDF ( *(Gen_00609320 **)&g_rva012F7048LivingWorld )
// Retail 0x012F1028 is EA's TheLivingWorldLogic (data_rows.csv owns
// ?TheLivingWorldLogic@@3PAVLivingWorldLogic@@A, LivingWorldLogic.cpp); the
// Glo012F1028 spelling is only a pin nothing defines.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#define Glo012F1028 ( reinterpret_cast<Glo012F1028Type *>( TheLivingWorldLogic ) )

class Rva003855F0Owner
{
public:
	void reset_003855F0();
private:
	char m_pad[0xA8];
	int m_atA8;
};

void Rva003855F0Owner::reset_003855F0()
{
	Rva00361D10Sub *sub = reinterpret_cast<Rva00361D10Sub *>(reinterpret_cast<char *>(this) + 0x170);
	((void (__fastcall *)(Rva00361D10Sub *))j_0002c8f9)(sub);
	// The one-argument callee uses thiscall.  A member pointer retains ECX
	// and the stack argument while keeping the direct ILT relocation.
	union { void (*raw)(); void (Rva00361D10Sub::*member)(int); } route;
	route.raw = j_00031313;
	(sub->*route.member)(m_atA8);
	if (reinterpret_cast<BfmeLivingWorldManager *>(g_bfmeGameCW)->isCampaignVictorious() && !g_bfmeStateDF->m_flag)
		return ((void (__fastcall *)(BfmeGameCW *))j_00048068)(g_bfmeGameCW);
	reinterpret_cast<GameLogic *>(this)->clearGameData(true, false);
	reinterpret_cast<BfmeSubBZF *>(sub)->bfmeOneBZF();
	reinterpret_cast<Rva003BDC50 *>(Glo012F1028)->run();
	reinterpret_cast<Rva003BFAB0 *>(Glo012F1028)->run(false);
}

void Rva00361D10Sub::method_00361D10() const
{
	Int matchCount = 0;
	unsigned int i = 0;
	if (m_bfmeVectorTwo.size() != 0)
	{
		Int offset = 0;
		do
		{
			Rva00361960 *elem = (Rva00361960 *)((char *)m_bfmeVectorTwo.begin() + offset);
			int type = *(int *)((char *)elem + 0x20);
			if (type == 3 || (type == 4 && *(unsigned char *)((char *)elem + 8) == 0))
			{
				reinterpret_cast<Rva003C0350 *>(Glo012F1028)->run(elem->copyString(), (void *)matchCount), ++matchCount;
			}
			++i;
			offset += sizeof(Rva00361960);
		} while (i < m_bfmeVectorTwo.size());
	}
}
