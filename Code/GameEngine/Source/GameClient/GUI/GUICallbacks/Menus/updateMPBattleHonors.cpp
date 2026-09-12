// cl: /DNDEBUG /MD /EHsc
// stlport
//
// 0x004E59E0 is the ScoreScreen-local updateMPBattleHonors helper.  The
// populatePlayerInfo caller at 0x004E75F1 passes PSPlayerStats in EAX and the
// honors reference on the stack; the static caller below keeps that private
// convention visible to the compiler.  The Player/PlayerList/GameLogic views
// name only fields proven by the retail accesses: PlayerList::m_local +0x0c,
// Player::m_side +0x28, Player::m_scoreKeeper +0x348, and GameLogic::m_frame
// +0x3c.  BfmeV1112 is the already byte-matched data-bearing ScoreKeeper map
// view whose 0x000EA260 body is reached by retail ILT 0x00013485.

typedef int Int;
typedef unsigned int UnsignedInt;

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <bitset>

class AsciiString
{
public:
	Int compare(const char *text) const;

private:
	char *m_data;
};

enum
{
	KINDOF_VEHICLE = 9,
	KINDOF_AIRCRAFT = 12
};

struct BfmeA1112
{
	public:
		enum BogusInitType { kInit = 0 };
		BfmeA1112() {}
		BfmeA1112(BogusInitType, Int bit) { m_bits.set(bit); }
		void clear() { m_bits.reset(); }
		void set(Int bit) { m_bits.set(bit); }

	private:
		_STL::bitset<192> m_bits;
};

struct BfmeB1112
{
	public:
		enum BogusInitType { kInit = 0 };
		BfmeB1112() {}
		BfmeB1112(BogusInitType, Int bit) { m_bits.set(bit); }
		void clear() { m_bits.reset(); }
		void set(Int bit) { m_bits.set(bit); }

	private:
		_STL::bitset<192> m_bits;
};

class BfmeV1112
{
public:
	Int bfmeGo1112A(BfmeA1112 validMask, BfmeB1112 invalidMask);

private:
	char m_pad[0x144];
	void *m_map;
	char m_tail[0x88];
};

class Player
{
public:
	char m_pad00[0x28];
	AsciiString m_side;
	char m_pad2c[0x31c];
	BfmeV1112 m_scoreKeeper;
};

class PlayerList
{
public:
	char m_pad00[0x0c];
	Player *m_local;
};

class GameLogic
{
public:
	char m_pad00[0x3c];
	UnsignedInt m_frame;
};

class PSPlayerStats
{
public:
	char m_pad00[0x17c];
	Int gamesInRowWithLastGeneral;
	char m_pad180[8];
	Int winsInARow;
};

extern PlayerList *ThePlayerList;
extern GameLogic *TheGameLogic;

static __declspec(noinline) void updateMPBattleHonors(Int &honors, PSPlayerStats &stats)
{
	Player *localPlayer = ThePlayerList->m_local;
	BfmeV1112 *s = &localPlayer->m_scoreKeeper;

	if (stats.winsInARow >= 3)
		honors |= 2;
	if (stats.winsInARow >= 10)
		honors |= 8;
	if (stats.winsInARow >= 25)
		honors |= 0x10;

	if (stats.gamesInRowWithLastGeneral >= 20 && localPlayer->m_side.compare("America") == 0)
		honors |= 0x20;
	if (stats.gamesInRowWithLastGeneral >= 20 && localPlayer->m_side.compare("China") == 0)
		honors |= 0x40;
	if (stats.gamesInRowWithLastGeneral >= 20 && localPlayer->m_side.compare("GLA") == 0)
		honors |= 0x200;

	BfmeA1112 validMask(BfmeA1112::kInit, KINDOF_VEHICLE);
	BfmeB1112 invalidMask(BfmeB1112::kInit, KINDOF_AIRCRAFT);
	if (s->bfmeGo1112A(validMask, invalidMask) >= 50)
		honors |= 0x80;

	validMask.clear();
	validMask.set(KINDOF_AIRCRAFT);
	invalidMask.clear();
	if (s->bfmeGo1112A(validMask, invalidMask) >= 20)
		honors |= 0x100;

	if (TheGameLogic->m_frame / 5 / 60 < 5)
		honors |= 0x4000;
	if (TheGameLogic->m_frame / 5 / 60 < 10)
		honors |= 0x8000;
}

// The retail caller is in ScoreScreen.cpp.  Keeping a TU-local call site here
// is enough for MSVC's internal-linkage register convention; this symbol is
// only a compile anchor and is not a second ledger claim.
void rva004E59E0ProbeCaller(Int &honors, PSPlayerStats &stats)
{
	updateMPBattleHonors(honors, stats);
}
