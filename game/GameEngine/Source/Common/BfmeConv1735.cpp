// ILT 0x000290D2 -> 0x00465B80, the matched byte-field setter ?apply@Rva00465B80@@QAEXXZ.
class Rva00465B80
{
public:
	void apply(void);
};

class BfmeMgr19E
{
public:
	void bfmeRunAG(void) { reinterpret_cast<Rva00465B80 *>(this)->apply(); }
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
