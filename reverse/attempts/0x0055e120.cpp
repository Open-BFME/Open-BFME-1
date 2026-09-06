// ?bfmeHandleAJ@BfmeOwnAJ@@QAEHHEH@Z (identity unknown)
// partial score=0.8 date=2026-09-06
// 123/134. Everything through the first two guards is byte-exact (the byte
// parameter is a two-case switch -- see the landed siblings 0x0056BF40,
// 0x0054BAD0 and 0x005597B0), and the reporter block, the "online"/"normal"
// ternary and the trailing close call are all modelled.
// The blocker is the state switch lowering: retail emits the subtract chain
//   sub eax,2 / je L / dec / je L / dec / jne default
// while MSVC emits a range test (cmp 2 / jl, cmp 3 / jle, cmp 4 / jne),
// which is 11 bytes shorter. Tried: case 4 falling through into a shared
// 2/3 body, an explicit default returning 1, cases 2/3 first with a shared
// close after the switch, and a named state local. All range-test.
// Literals: fmt "assignClose" at 0x011090FC, "online" at 0x011090F4,
// "normal" at 0x010F7734, the selector byte g_bfmeD1072 at 0x012F4AD1.
class BfmeMgr19E
{
public:
	void bfmeAddAJ(void *owner, char *fmt, int argc, char *first, char *second,
		char *third, char *fourth, char *fifth);
};

extern BfmeMgr19E *g_mgr12F19E8;
extern char g_bfmeFmtAJ[];
extern char g_bfmeLitA1072[];
extern char g_bfmeLitB1072[];
extern char g_bfmeD1072;

class BfmeOwnAJ
{
public:
	int bfmeHandleAJ(int code, unsigned char kind, int flags);
	void bfmeCloseAJ(int reason);

	unsigned char m_bfmeHeadAJ[0x250];
	void *m_bfmeSinkAJ;
	unsigned char m_bfmeMidAJ[4];
	int m_bfmeStateAJ;
};

int BfmeOwnAJ::bfmeHandleAJ(int code, unsigned char kind, int flags)
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
		return 1;

	switch (m_bfmeStateAJ)
	{
		case 4:
			g_mgr12F19E8->bfmeAddAJ(m_bfmeSinkAJ, g_bfmeFmtAJ, 1,
				g_bfmeD1072 ? g_bfmeLitA1072 : g_bfmeLitB1072, 0, 0, 0, 0);

		case 2:
		case 3:
			bfmeCloseAJ(0);
			break;
	}

	return 1;
}
