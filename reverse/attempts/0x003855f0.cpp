// ?reset_003855F0@Rva003855F0Owner@@QAEXXZ
// partial score=0.98 date=2026-09-24
// cl: /DNDEBUG /DWIN32 /MD
// Retail 0x003855F0: transition called from GameLogic::logicMessageDispatcher.
// The original member name is unknown, so the owner and method keep the RVA.
// See reverse/identity_evidence/0x003855f0-transition-call-routes.md.
class Rva00361D10Sub
{
public:
	void clear_00361D10();
	void sync_00365DF0(int value);
};
class BfmeLivingWorldManager
{
public:
	bool isCampaignVictorious();
};
class BfmeGameCW;
// This names only the ILT call route. The target is the matched free helper
// rva00612070Post, whose body does not use the incoming ECX receiver.
class Rva00048068Dispatch
{
public:
	void invoke();
};
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
	sub->clear_00361D10();
	sub->sync_00365DF0(m_atA8);
	if (reinterpret_cast<BfmeLivingWorldManager *>(g_bfmeGameCW)->isCampaignVictorious() && !g_bfmeStateDF->m_flag)
		return reinterpret_cast<Rva00048068Dispatch *>(g_bfmeGameCW)->invoke();
	reinterpret_cast<GameLogic *>(this)->clearGameData(true, false);
	reinterpret_cast<BfmeSubBZF *>(sub)->bfmeOneBZF();
	reinterpret_cast<Rva003BDC50 *>(Glo012F1028)->run();
	reinterpret_cast<Rva003BFAB0 *>(Glo012F1028)->run(false);
}
