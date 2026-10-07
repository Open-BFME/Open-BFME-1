class BfmeMgr19E
{
public:
	void bfmeAddAI(void *owner, char *fmt, int argc, char *first, char *second,
		char *third, char *fourth, char *fifth);
};

// Retail global 0x012F19E8. EA's own name for this pointer; see
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp for the definition.
// This TU keeps its local view type BfmeMgr19E and casts at the use.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

// ILT 0x00011E14 -> 0x00559360, the matched pushStats@BfmePushStatsHost@@QAEXH@Z.
class BfmePushStatsHost
{
public:
	void pushStats(int reason);
};

class BfmeHostAI
{
public:
	unsigned char m_bfmeHeadAI[0x250];
	void *m_bfmeSinkAI;
};

class BfmeOwnAI
{
public:
	int bfmeHandleAI(void *unused, int code, unsigned char kind, int flags);

	unsigned char m_bfmeHeadAI[0x34];
	BfmeHostAI *m_bfmeHostAI;
	unsigned char m_bfmeMidAI[4];
	int m_bfmeStateAI;
};

int BfmeOwnAI::bfmeHandleAI(void *unused, int code, unsigned char kind, int flags)
{
	int kindValue = kind;

	if (code != 0x15)
		return 0;

	switch (kindValue)
	{
		case 1:
			break;

		default:
			return 0;
	}

	if ((flags & 1) == 0)
		return 0;

	int state = m_bfmeStateAI;

	if (state == 1)
	{
		((BfmeMgr19E *)g_rva012F19E8WindowManager)->bfmeAddAI(m_bfmeHostAI->m_bfmeSinkAI, "CallChild", state,
			"EscapeKeyPressed", 0, 0, 0, 0);
		reinterpret_cast<BfmePushStatsHost *>(this)->pushStats(0);

		return 1;
	}

	if (state == 3 || state == 2)
		return 1;

	return 0;
}
