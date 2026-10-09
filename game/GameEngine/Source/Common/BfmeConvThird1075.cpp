// Independent reconstruction of the served retail body at 0x0055E120.
// The separate state arms are intentional: merging cases 2 and 3 makes the
// VS2003 compiler replace retail's sub/dec/dec dispatch with a range test.

// Local view of the one method this body reaches on retail's 0x012F19E8
// global, which is a WindowManager*.
class BfmeMgr19E
{
public:
	void bfmeAddAJ(void *owner, char *fmt, int argc, char *first, char *second,
		char *third, char *fourth, char *fifth);
};

class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;
extern unsigned char g_optByte12F4AD1;

class BfmeOwnAJ
{
public:
	void bfmeCloseAJ(int reason);
};

// Matched row ?bfmeBuildAN@BfmeLevelAN@@QAEPADIHHHHHHH@Z (retail 0x004675F0,
// defined in BfmeLevelPathAN.cpp): the ILT entry 0x00015235 jumps here, so the
// builder call below names this row. Declaration copied from that TU.
class BfmeLevelAN
{
public:
	char *bfmeBuildAN(unsigned int level, int p2, int p3, int p4, int p5, int p6,
		int p7, int p8);
};

// Matched row ?_bfme_cancel@BfmeAptScreenOptions@@QAEXPBD@Z (retail 0x0055DCB0,
// defined in BfmeAptScreenOptionsCancel.cpp): the ILT entry 0x0003D811 jumps
// here, so the close calls below name this row. Declaration copied from that
// TU (thiscall void of one pointer-sized argument, same as bfmeCloseAJ).
class BfmeAptScreenOptions
{
public:
	void _bfme_cancel(const char *name);
};

// The cancel call at 0x0055E198 reaches retail through the incremental-link
// thunk 0x0003D811, which the ledger owns as ?j_0003d811@@YAXXZ
// (game/gen_small/thunks_029.cpp). That thunk is the definition the link
// keeps and its census verdict is retail's, while the body row
// ?_bfme_cancel@BfmeAptScreenOptions@@QAEXPBD@Z is judged "wrong" by the
// one-hop retail-truth closure, so the call below names the thunk. VC7.1 has
// no __thiscall function-pointer type, so the object goes through a
// pointer-to-member taken out of a union, the pattern the tree's other
// matched thunk callers already use (BfmeConv993.cpp).
extern void j_0003d811();
class Rva0055E120Receiver {};
typedef void (Rva0055E120Receiver::*Rva0003D811Cancel)(const char *);

template<class T> __forceinline T Rva0055E120Member(void (*raw)())
{
	union { void (*raw)(); T member; } fn;
	fn.raw = raw;
	return fn.member;
}
#define CALL1075(T, obj, fn) (((Rva0055E120Receiver*)(obj))->*Rva0055E120Member<T>(fn))

class BfmeQ1075
{
public:
	int bfmeGo1075A(int code, unsigned char kind, char flags);

	unsigned char m_bfmeHeadAJ[0x250];
	void *m_bfmeSinkAJ;
	unsigned char m_bfmeMidAJ[4];
	int m_bfmeStateAJ;
};

int BfmeQ1075::bfmeGo1075A(int code, unsigned char kind, char flags)
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
			if (g_optByte12F4AD1)
				((BfmeLevelAN *)g_rva012F19E8WindowManager)->bfmeBuildAN((unsigned int)m_bfmeSinkAJ,
					(int)"assignClose", 1, (int)"online", 0, 0, 0, 0);
			else
				((BfmeLevelAN *)g_rva012F19E8WindowManager)->bfmeBuildAN((unsigned int)m_bfmeSinkAJ,
					(int)"assignClose", 1, (int)"normal", 0, 0, 0, 0);
			CALL1075(Rva0003D811Cancel, this, j_0003d811)(0);
			break;

		case 2:
			CALL1075(Rva0003D811Cancel, this, j_0003d811)(0);
			break;

		case 3:
			CALL1075(Rva0003D811Cancel, this, j_0003d811)(0);
			break;
	}

	return 1;
}
