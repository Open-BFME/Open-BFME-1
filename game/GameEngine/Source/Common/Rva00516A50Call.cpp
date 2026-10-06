// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// ILT 0x000290D2 -> 0x00465B80, matched ?apply@Rva00465B80@@QAEXXZ (sets the
// byte at +0x1AC to 1), called on the window manager at 0x012F19E8.
class Rva00465B80
{
public:
	void apply();
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
		((Rva00465B80 *)g_rva012F19E8WindowManager)->apply();
}
