class BfmeMgr19E
{
public:
	void bfmeRunAG(void);
};

// Retail global 0x012F19E8; canonical definition in GameClient/GUI/WindowManager.cpp.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;
class BfmeAptScreenSaveLoad;
extern BfmeAptScreenSaveLoad *TheAptSaveLoad;

class BfmeOwnAG
{
public:
	int bfmeHandleAG(int code, unsigned char kind, int flags);

	unsigned char m_bfmeHeadAG[0x258];
	int m_bfmeBusyAG;
};

int BfmeOwnAG::bfmeHandleAG(int code, unsigned char kind, int flags)
{
	int kindValue = kind;

	if (code != 0x15)
		return 0;

	switch (kindValue)
	{
		case 1:
			break;

		default:
			return 0;
	}

	if ((flags & 1) && m_bfmeBusyAG == 0 && reinterpret_cast<void * &>(TheAptSaveLoad))
		((BfmeMgr19E *)g_rva012F19E8WindowManager)->bfmeRunAG();

	return 1;
}
