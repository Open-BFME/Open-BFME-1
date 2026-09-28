struct Rva00579160Manager { void fire(void* target, const char* name, int a, int b, int c, int d, int e, int f); };
extern Rva00579160Manager* Rva00579160TheManager;
extern int g_aptPalantirWindow;

extern "C" const char *bfmeTabEAC[];

void bfmeButtonStateEAF(char index, int state)
{
	char text[2];

	text[0] = (char)(index + 0x31);
	text[1] = 0;

	Rva00579160TheManager->fire((void *)g_aptPalantirWindow,
		"SetCommandButtonState", 2, (int)text,
		(int)bfmeTabEAC[state], 0, 0, 0);
}
