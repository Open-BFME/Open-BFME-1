struct BfmeSlotAAA
{
	void *m_bfmeWhat;
	unsigned char m_bfmeRest[0x14];
};

struct BfmeModeAAA
{
	unsigned char m_bfmeHead[0x1b4];
	int m_bfmeMode;
};

class BfmeSinkAAA
{
public:
	void bfmeSendAAA(void *what, bool flag, int more);
};

// Retail calls the ILT thunk at 0x00044409, owned by game/gen_small/thunks_032.cpp
// as ?j_00044409@@YAXXZ.  It is reached through a member-function pointer so the
// call keeps its thiscall shape; bfmeSendAAA is never referenced by name.
extern "C" void __cdecl __identifier("?j_00044409@@YAXXZ")();
typedef void (BfmeSinkAAA::*BfmeSendAAAThunk)(void *what, bool flag, int more);
union BfmeSendAAAThunkRef
{
	void *m_thunk;
	BfmeSendAAAThunk m_call;
};

// Retail global 0x012F19E8; canonical definition in GameClient/GUI/WindowManager.cpp.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

// Retail global 0x012F33F8; the canonical mangled spelling is
// ?TheControlBar@@3PAVControlBar@@A, so the pointee must be the real
// ControlBar and only the call needs the TU-local view of it.
class ControlBar;
extern ControlBar *TheControlBar;

class BfmeThingAAA
{
public:
	void bfmeGoAAA(int at);
	unsigned char m_bfmeHead[0x1c];
	BfmeSlotAAA m_bfmeSlots[12];
};

void BfmeThingAAA::bfmeGoAAA(int at)
{
	if (at < 0)
		return;
	if (at >= 0xc)
		return;
	void *what = m_bfmeSlots[at].m_bfmeWhat;
	if (what == 0)
		return;
	BfmeSendAAAThunkRef thunk;
	thunk.m_thunk = (void *)&__identifier("?j_00044409@@YAXXZ");
	(((BfmeSinkAAA *)TheControlBar)->*thunk.m_call)(what, ((BfmeModeAAA *)g_rva012F19E8WindowManager)->m_bfmeMode != 2, 0);
}
