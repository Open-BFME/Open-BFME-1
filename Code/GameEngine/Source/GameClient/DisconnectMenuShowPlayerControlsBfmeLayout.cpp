// BFME layout reconstruction of DisconnectMenu::_bfme_showPlayerControls.
// The BFME menu stores its movie at +0x250 and the per-slot visibility bytes
// at +0x262; the published ZH menu has a different layout.

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer,
	const char *format, ...);

class WindowManager
{
public:
	void unidentified_00015235(int movie, const char *function, int argumentCount,
		const void *argument, int unused1, int unused2, int unused3, int unused4);
};

extern WindowManager *g_theWindowManager;

class DisconnectMenu
{
public:
	void _bfme_showPlayerControls(int slot, bool show);

private:
	char m_bfmeHead[0x250];
	int m_bfmeMovie;
	char m_bfmeGap[0x0e];
	bool m_bfmeControls[8];
};

void DisconnectMenu::_bfme_showPlayerControls(int slot, bool show)
{
	char slotText[32];
	sprintf(slotText, "%d", slot);

	const char *function = show ? "ShowKickButton" : "HideKickButton";
	g_theWindowManager->unidentified_00015235(
		m_bfmeMovie, function, 1, slotText, 0, 0, 0, 0);
	m_bfmeControls[slot] = show;
}
