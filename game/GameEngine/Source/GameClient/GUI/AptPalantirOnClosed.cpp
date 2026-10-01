class PalantirAptWindow
{
public:
	void close( int window );
};

// Retail global at 0x012F19E8; canonical mangled spelling is
// ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A.  The close() callee mangles
// against this TU-local view, so the global is cast to it at the use.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

extern int g_bfmeMsg1020;
extern char g_bfmeC1020;
extern char g_bfmeD1020;

// ?aptPalantirOnClosed@@YAXXZ
void aptPalantirOnClosed()
{
	((PalantirAptWindow *)g_rva012F19E8WindowManager)->close( g_bfmeMsg1020 );
	g_bfmeC1020 = 1;
	g_bfmeD1020 = 0;
}
