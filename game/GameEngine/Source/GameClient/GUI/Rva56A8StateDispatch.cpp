// cl: /DNDEBUG /MD /EHsc

class BfmeH1065
{
};

int bfmeAptLevel00465CE0(BfmeH1065 *window);

class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;

// ILT 0x00015235 -> 0x004675F0, the matched 206-byte
// ?bfmeBuildAN@BfmeLevelAN@@QAEPADIHHHHHHH@Z (BfmeLevelPathAN.cpp): the
// eight-dword scripted-UI dispatcher, called on the window manager.
class BfmeLevelAN
{
public:
	char *bfmeBuildAN(unsigned int movie, int function, int argumentCount,
		int p1, int p2, int p3, int p4, int p5);
};

class AptSaveLoad;
class BfmeAptScreenSaveLoad;
extern BfmeAptScreenSaveLoad *TheAptSaveLoad;

// ILT 0x000290D2 -> 0x00465B80, matched ?apply@Rva00465B80@@QAEXXZ (sets the
// byte at +0x1AC to 1), called on the window manager at 0x012F19E8.
class Rva00465B80
{
public:
	void apply();
};

class Rva56A8StateOwner
{
public:
	void dispatchState(int state);

private:
	char m_pad0[0x258];
	int m_state;
	char m_pad25c[0x20];
	int m_auxiliaryState;
};

void Rva56A8StateOwner::dispatchState(int state)
{
	switch (state)
	{
	case 3:
	{
		int currentState = m_state;
		if (currentState == 8)
		{
			reinterpret_cast<BfmeLevelAN *>(g_rva012F19E8WindowManager)->bfmeBuildAN(
				bfmeAptLevel00465CE0((BfmeH1065 *)this),
				(int)"closeDelayed", 1,
				(int)"OnClosed", 0, 0, 0, 0);
			m_state = 9;
			if (reinterpret_cast<AptSaveLoad * &>(TheAptSaveLoad) != 0)
				reinterpret_cast<Rva00465B80 *>(g_rva012F19E8WindowManager)->apply();
		}
		else if (currentState == 0x12)
			m_state = 1;
		break;
	}

	case 1:
		if (m_state == 7)
			m_state = 6;
		break;
	}
}
