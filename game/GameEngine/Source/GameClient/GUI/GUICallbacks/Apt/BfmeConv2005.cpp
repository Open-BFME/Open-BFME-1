struct Rva00579160Manager { void fire(void* target, const char* name, int a, int b, int c, int d, int e, int f); };
// Retail global at 0x012F19E8; canonical mangled spelling is
// ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;
extern int g_aptPalantirWindow;

// The state argument at VA 0x01109918: retail .rdata holds "_hide" there.
extern "C" const char bfmeOffEAA[] = "_hide";
// Its paired "_show" state at VA 0x01109920 (read by bfmeFlashEAA 0x005640D0).
extern "C" const char bfmeOnEAA[] = "_show";

void bfmeAutoAbilityOffEAE(char index)
{
	char text[2];

	text[0] = (char)(index + 0x31);
	text[1] = 0;

	((Rva00579160Manager *)g_rva012F19E8WindowManager)->fire((void *)g_aptPalantirWindow,
		"SetCommandButtonAutoAbilityState", 2, (int)text,
		(int)bfmeOffEAA, 0, 0, 0);
}
