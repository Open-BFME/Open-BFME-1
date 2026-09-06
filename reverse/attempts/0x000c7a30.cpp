// ?bfmeNewMap@BfmePlayerMapState@@QAEXH_N@Z
// partial score=0.92 date=2026-09-06
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

typedef int Int;
typedef bool Bool;

class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getNthPlayer(Int i);
	int unidentified_000df510(Bool includeFields);
};

extern PlayerList *g_rva005655C0PlayerList;

class GameLogicShim
{
public:
	Bool unidentified_0001e0ab(void);
};

extern GameLogicShim *TheBfmeGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_unreconstructed_00[1];
};

extern GlobalData *TheWritableGlobalData;

class Glo012F1028Type;

extern Glo012F1028Type *Glo012F1028;

void d_003bdd60(void);

static inline int gd_at(int offset)
{
	return *(int *)((char *)TheWritableGlobalData + offset);
}

typedef int (Glo012F1028Type::*NakedMemberFn)();

static int callD003bdd60(Glo012F1028Type *receiver)
{
	void *addr = (void *)&d_003bdd60;
	NakedMemberFn mfn;
	*(void **)&mfn = addr;
	return (receiver->*mfn)();
}

class BfmePlayerMapState
{
public:
	void bfmeNewMap(Int field, Bool flag);

private:
	unsigned char m_pad0[4];
	int m_at4;
	unsigned char m_pad8[4];
	int m_atc;
	int m_at10;
	int m_at14;
};

void BfmePlayerMapState::bfmeNewMap(Int field, Bool flag)
{
	if (field < 0 || field >= 32 || !g_rva005655C0PlayerList || !TheBfmeGameLogic)
		return;

	m_atc = field;

	if (TheBfmeGameLogic->unidentified_0001e0ab())
	{
		int count = g_rva005655C0PlayerList->unidentified_000df510(true);
		int x, y;
		if (count >= 7)
		{
			x = gd_at(0xeac);
			y = gd_at(0xea8);
		}
		else if (count >= 5)
		{
			x = gd_at(0xea4);
			y = gd_at(0xea0);
		}
		else if (count == 4)
		{
			x = gd_at(0xe9c);
			y = gd_at(0xe98);
		}
		else if (count == 3)
		{
			x = gd_at(0xe94);
			y = gd_at(0xe90);
		}
		else
		{
			x = gd_at(0xe8c);
			y = gd_at(0xe88);
		}

		if (flag)
			m_at4 = x;
		else
			m_at4 = y;
		int termX = m_at14 * x;
		int termY = m_at10 * y;
		m_at4 += termX + termY;
		return;
	}

	Player *p = g_rva005655C0PlayerList->getNthPlayer(m_atc);
	if (!p)
		return;

	void *rel = *(void **)((char *)p + 0x2c);
	if (!rel)
	{
		if (flag)
			m_at4 = gd_at(0xe74);
		else
			m_at4 = gd_at(0xe70);

		if (Glo012F1028)
		{
			int add = callD003bdd60(Glo012F1028);
			m_at4 += add;
		}
		return;
	}

	if (flag)
		m_at4 = gd_at(0xe84);
	else
		m_at4 = gd_at(0xe80);
}
