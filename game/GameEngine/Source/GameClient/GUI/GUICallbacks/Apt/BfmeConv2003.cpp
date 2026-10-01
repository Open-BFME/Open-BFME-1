struct Rva00579160Manager { void fire(void* target, const char* name, int a, int b, int c, int d, int e, int f); };
// Retail global 0x012F19E8; canonical definition in GameClient/GUI/WindowManager.cpp.
class WindowManager;
extern WindowManager* g_rva012F19E8WindowManager;
extern int g_aptPalantirWindow;

extern "C" const char bfmeOnEAA[];
extern "C" const char bfmeOffEAA[];

void bfmeFlashEAA(char index, char on)
{
	char text[2];

	text[0] = (char)(index + 0x31);
	text[1] = 0;

	((Rva00579160Manager*)g_rva012F19E8WindowManager)->fire((void *)g_aptPalantirWindow,
		"SetCommandButtonFlashEffectState", 2, (int)text,
		(int)(on ? bfmeOnEAA : bfmeOffEAA), 0, 0, 0);
}
