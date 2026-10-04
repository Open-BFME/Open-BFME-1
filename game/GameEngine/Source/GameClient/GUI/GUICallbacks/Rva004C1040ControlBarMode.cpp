// cl: /O2 /Ob0

// The two globals are EA's canonical singletons -- `GameWindowManager
// *TheWindowManager` at 0x012F1B40 and `ControlBar *TheControlBar` at
// 0x012F33F8 (symbols.csv) -- and the letterbox helpers are the `bool`
// overloads at 0x004C0C80 / 0x004C0E10, reached here through ILT 0x00002847 /
// 0x00024848. Only the pointer values and the pushed immediates matter to the
// bytes, so the canonical spellings cost nothing.
class GameWindowManager;
extern GameWindowManager *TheWindowManager;

class ControlBar;
extern ControlBar *TheControlBar;

void HideControlBar(bool immediate);
void ShowControlBar(bool immediate);
void j_00012f21(void);

void Rva004C1040(int unused)
{
	(void)unused;
	if (TheWindowManager != 0)
	{
		HideControlBar(1);
		int mode = ((int (__fastcall *)(ControlBar *))j_00012f21)(TheControlBar);
		if (mode > 0 && mode <= 2)
			ShowControlBar(1);
	}
}
