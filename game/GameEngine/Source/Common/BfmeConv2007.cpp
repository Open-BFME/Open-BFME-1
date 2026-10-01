struct BfmeObj947C
{
	unsigned char m_bfmeHeadEAH[0x254];
	char m_bfmeBusyEAH;
	unsigned char m_bfmePadEAH[7];
	void *m_bfmeParamEAH;
};

class Shell40D9
{
public:
	unsigned char m_bfmeHeadEAH[0x50];
	char m_bfmeFlagEAH;
};

struct Rva00579160Manager
{
	void bfmeRunEAH();
};

extern BfmeObj947C *g_bfme947ObjC;
extern Shell40D9 *TheShell;
// Retail global 0x012F19E8; canonical definition in GameClient/GUI/WindowManager.cpp.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

void bfmeOpenEAH(void *param)
{
	BfmeObj947C *obj = g_bfme947ObjC;

	if (obj == 0)
		return;

	if (obj->m_bfmeBusyEAH != 0)
		return;

	obj->m_bfmeBusyEAH = 1;

	g_bfme947ObjC->m_bfmeParamEAH = param;

	TheShell->m_bfmeFlagEAH = 1;

	((Rva00579160Manager *)g_rva012F19E8WindowManager)->bfmeRunEAH();
}
