// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class BfmeGlobal_012f19e8
{
public:
	void bfmeCall_000290d2(void);
};

class BfmeAptScreenLanLobby;
extern BfmeAptScreenLanLobby *g_rva012F4998LanLobby;

// Retail global at 0x012F19E8; canonical mangled spelling is
// ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A.  The call target mangles
// against this TU-local view, so the global is cast to it at the use.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

class Rva00516A50
{
public:
	void wrap(int a);
};

void Rva00516A50::wrap(int)
{
	if (reinterpret_cast<void * &>(g_rva012F4998LanLobby))
		((BfmeGlobal_012f19e8 *)g_rva012F19E8WindowManager)->bfmeCall_000290d2();
}
