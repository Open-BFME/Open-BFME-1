// cl: /O2 /Ob0

class Rva004C1040WindowManager
{
};

extern Rva004C1040WindowManager *TheWindowManager;
class Rva004C1040ControlBar
{
};
extern Rva004C1040ControlBar *TheControlBar;

void HideControlBar(int immediate);
void ShowControlBar(int immediate);
void j_00012f21(void);

void Rva004C1040(int unused)
{
	(void)unused;
	if (TheWindowManager != 0)
	{
		HideControlBar(1);
		int mode = ((int (__fastcall *)(Rva004C1040ControlBar *))j_00012f21)(TheControlBar);
		if (mode > 0 && mode <= 2)
			ShowControlBar(1);
	}
}
