// ?reset_003855F0@Rva003855F0Owner@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /MD
// Retail 0x003855F0: transition called from GameLogic::logicMessageDispatcher.
// The original member name is unknown, so the owner and method keep the RVA.
// Calls through the existing ILT thunk symbols preserve each physical route.
// See reverse/identity_evidence/0x003855f0-transition-call-routes.md.
extern void j_0002c8f9();
extern void j_00031313();
extern void j_00048068();

class Rva00361D10Sub {};
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
extern BfmeGameCW *g_bfmeGameCW;
extern Gen_00609320 *g_bfmeStateDF;
extern Glo012F1028Type *Glo012F1028;

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
