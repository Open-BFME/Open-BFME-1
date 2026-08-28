void bfmeSendATB(int what);

extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buffer,
	int count, const char *format, ...);

int AptLivingWorldWindowIndex(int low, int high);

class WindowManager
{
public:
	void unidentified_00015235(int movie, const char *function, int argumentCount,
		const void *argument, int unused1, int unused2, int unused3, int unused4);
};

extern WindowManager *g_theWindowManager;

void bfmeSendATB(int what)
{
	char text[16];
	_snprintf(text, 16, "%d", what);

	g_theWindowManager->unidentified_00015235(
		AptLivingWorldWindowIndex(*(int *)0x012F49A8, *(int *)0x012F49A8),
		"CloseRegionConqueredNotice", 1, text, 0, 0, 0, 0);
}

class BfmeThingATB
{
public:
	void bfmeGoATB();
	unsigned char m_bfmeHead[8];
	void *m_bfmeWhat;
	bool m_bfmeReady;
	bool m_bfmeDone;
};

void BfmeThingATB::bfmeGoATB()
{
	if (m_bfmeWhat != 0 && !m_bfmeDone)
	{
		if (m_bfmeReady)
		{
			bfmeSendATB(0);
			m_bfmeDone = true;
			return;
		}
		m_bfmeWhat = 0;
	}
}
