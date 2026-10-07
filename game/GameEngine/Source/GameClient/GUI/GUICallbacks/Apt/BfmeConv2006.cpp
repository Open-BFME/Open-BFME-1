struct Rva00579160Manager { void fire(void* target, const char* name, int a, int b, int c, int d, int e, int f); };
// Retail global 0x012F19E8; canonical definition in GameClient/GUI/WindowManager.cpp.
class WindowManager;
extern WindowManager* g_rva012F19E8WindowManager;
extern int g_aptPalantirWindow;

// Retail .rdata VA 0x011098B0: button-state suffix names (7 pointers).
extern "C" const char *const bfmeTabEAC[7] = {
	"_unused", "_disabled", "_cantAfford", "_static", "_notReady", "_up", "_visuallyEnabled"
};

void bfmeButtonStateEAF(char index, int state)
{
	char text[2];

	text[0] = (char)(index + 0x31);
	text[1] = 0;

	((Rva00579160Manager*)g_rva012F19E8WindowManager)->fire((void *)g_aptPalantirWindow,
		"SetCommandButtonState", 2, (int)text,
		(int)bfmeTabEAC[state], 0, 0, 0);
}
