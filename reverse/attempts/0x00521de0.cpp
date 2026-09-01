// ?d_00521de0@@YAXXZ
// partial score=0.96 date=2026-08-31
// cl: /O2 /Ob0 /Op /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

struct Rva00521DE0State
{
	unsigned char m_pad0[0x34];
	int m_mode;
	unsigned char m_pad38[0x0C];
	unsigned m_timeDelta;
};

extern Rva00521DE0State *g_rva00521de0State;

void Rva00521DE0Update(float time)
{
	if (!g_rva00521de0State || !g_rva00521de0State->m_mode || g_rva00521de0State->m_mode == 3)
		return;

	Rva00521DE0State *state = g_rva00521de0State;
	state->m_timeDelta = timeGetTime() - (int)(time + -1000.0f);
}
