// ??0RankPoints@@QAE@XZ
// partial score=0.9 date=2026-09-14
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: RankPoints::RankPoints, retail 0x004DAFA0, 206 bytes.
// Converted from gen-dump d_004dafa0. SetUpGameSpy names this body via
// `TheRankPointValues = NEW RankPoints`. The 1394B ??0RankPoints@@ emit at
// 0x004D9DF0 is a different function. BFME fills ranks 0..9 then only
// m_winMultiplier=3 (retail writes 0x40400000, ZH source agrees) and
// m_lostMultiplier=1 (ZH also wrote hour/campaign/disc).
//
// BLOCKER (2026-09-14): body compiles to 171B vs retail 206B — retail carries a
// bare SEH/EH frame: `mov eax,fs:[0]; push -1; push eh_00C2AD50; push eax;
// mov fs:[0],esp` up front and `mov fs:[0],ecx; add esp,0xC` in the epilogue.
// Its FuncInfo at RVA 0xE1B278 is degenerate: maxState=1, single unwind entry
// {toState:-1, action:NULL}, dwTryCount=0 — a frame that guards NOTHING. There
// are no EH state stores and no `this` spill. Tested and ruled out: member with
// nontrivial dtor (emits real funclet + state stores), function-try-block and
// body try/catch (emit ebp frame + state stores), class-level ~R() (no frame),
// user-defined inline-empty member ctor (no frame), member-init-list calls,
// -EHa/-EHs flag variants. Next hypothesis: an inlined callee whose dead local
// left the registration behind, or a ctor-initializer emitting the frame before
// the first member store.

typedef int Int;

class GameSpyConfigInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual Int getPointsForRank( Int rank );
};

extern GameSpyConfigInterface *TheGameSpyConfig;

enum
{
	RANK_PRIVATE = 0,
	RANK_CORPORAL,
	RANK_SERGEANT,
	RANK_LIEUTENANT,
	RANK_CAPTAIN,
	RANK_MAJOR,
	RANK_COLONEL,
	RANK_BRIGADIER_GENERAL,
	RANK_GENERAL,
	RANK_COMMANDER_IN_CHIEF,
	MAX_RANKS
};

class RankPoints
{
public:
	RankPoints();

	Int m_ranks[ MAX_RANKS ];
	float m_winMultiplier;
	float m_lostMultiplier;
};

// ??0RankPoints@@QAE@XZ
RankPoints::RankPoints()
{
	m_ranks[ RANK_PRIVATE ] = 0;
	m_ranks[ RANK_CORPORAL ] = TheGameSpyConfig->getPointsForRank( RANK_CORPORAL );
	m_ranks[ RANK_SERGEANT ] = TheGameSpyConfig->getPointsForRank( RANK_SERGEANT );
	m_ranks[ RANK_LIEUTENANT ] = TheGameSpyConfig->getPointsForRank( RANK_LIEUTENANT );
	m_ranks[ RANK_CAPTAIN ] = TheGameSpyConfig->getPointsForRank( RANK_CAPTAIN );
	m_ranks[ RANK_MAJOR ] = TheGameSpyConfig->getPointsForRank( RANK_MAJOR );
	m_ranks[ RANK_COLONEL ] = TheGameSpyConfig->getPointsForRank( RANK_COLONEL );
	m_ranks[ RANK_BRIGADIER_GENERAL ] = TheGameSpyConfig->getPointsForRank( RANK_BRIGADIER_GENERAL );
	m_ranks[ RANK_GENERAL ] = TheGameSpyConfig->getPointsForRank( RANK_GENERAL );
	m_ranks[ RANK_COMMANDER_IN_CHIEF ] = TheGameSpyConfig->getPointsForRank( RANK_COMMANDER_IN_CHIEF );
	m_winMultiplier = 3.0f;
	m_lostMultiplier = 1.0f;
}
