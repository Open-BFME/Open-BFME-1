struct BfmeObj947C
{
	unsigned char m_bfmeHeadEAH[0x254];
	char m_bfmeBusyEAH;
	unsigned char m_bfmePadEAH[7];
	void *m_bfmeParamEAH;
};

// Retail global 0x012F4B58 is EA's shell singleton, defined once under the
// canonical spelling (Shell *TheShell); this is the TU's view of the pointee.
class Shell
{
public:
	unsigned char m_bfmeHeadEAH[0x50];
	char m_bfmeFlagEAH;
};

// Retail 0x00569150 tail-jumps to ILT 0x290D2 -> matched 0x00465B80.
class Rva00465B80
{
public:
	void apply();
};

struct Rva00579160Manager
{
	__forceinline void bfmeRunEAH() { ((Rva00465B80 *)this)->apply(); }
};

class BfmeAptScreenQuitMenu;
extern BfmeAptScreenQuitMenu *g_obj12F4B40;
extern Shell *TheShell;
// Retail global 0x012F19E8; canonical definition in GameClient/GUI/WindowManager.cpp.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

void bfmeOpenEAH(void *param)
{
	BfmeObj947C *obj = reinterpret_cast<BfmeObj947C * &>(g_obj12F4B40);

	if (obj == 0)
		return;

	if (obj->m_bfmeBusyEAH != 0)
		return;

	obj->m_bfmeBusyEAH = 1;

	reinterpret_cast<BfmeObj947C * &>(g_obj12F4B40)->m_bfmeParamEAH = param;

	TheShell->m_bfmeFlagEAH = 1;

	((Rva00579160Manager *)g_rva012F19E8WindowManager)->bfmeRunEAH();
}
