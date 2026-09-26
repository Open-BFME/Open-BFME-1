// ?d_00539d40@@YAXXZ
// partial score=0.97 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Retail 0x00539D40: custom-match event dispatch for state-dependent actions.
struct BfmeOwner995C
{
	char m_pad[0x250];
	int m_id;
};

class BfmeLog995
{
public:
	void bfmeLog995(int id, char *fmt, int count, char *text, int a, int b, int c, int d);
};
extern BfmeLog995 *g_bfmeLog995;
extern char g_bfmeFmt1057[];
extern char g_bfmeEscAI[];

class BfmeAptScreenOnlineCustomMatch
{
public:
	void leaveStagingRoom(int unused);
};

class BfmeC995
{
public:
	int rva00539D40HandleEvent(int unused, int event, unsigned char action, int flags);
	void bfmeGo995C(int unused);

	char m_pad[0x34];
	BfmeOwner995C *m_owner;
	char m_pad2[0x150];
	int m_state;
	char m_pad3[0x28];
	unsigned char m_flag;
	char m_pad4[0x1d0 - 0x1b5];
	int m_count;
};

int BfmeC995::rva00539D40HandleEvent(int unused, int event, unsigned char action, int flags)
{
	if (event != 21 || static_cast<int>(action) - 1 || !(flags & 1))
		return 0;
	if (m_count > 0)
		goto handled;
	switch (m_state)
	{
	case 10:
		bfmeGo995C(0);
		return 1;
	case 3:
		{
			BfmeOwner995C *owner = m_owner;
			int id = owner->m_id;
			g_bfmeLog995->bfmeLog995(id, g_bfmeFmt1057, 1, g_bfmeEscAI, 0, 0, 0, 0);
			m_state = 1;
			m_flag = 0;
			return 1;
		}
	case 6:
	case 12:
		reinterpret_cast<BfmeAptScreenOnlineCustomMatch *>(this)->leaveStagingRoom(0);
		break;
	case 2:
		return 0;
	default:
		break;
	}
handled:
	return 1;
}
