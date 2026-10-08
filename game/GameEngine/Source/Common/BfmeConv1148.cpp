// Open-BFME5 conversions.

struct BfmeG1148
{
	char m_bfmePad0[0x18];
	char m_bfme18;
	char m_bfme19;
	char m_bfme1a;
	char m_bfme1b;
	char m_bfme1c;
	char m_bfmePad1[2];
	char m_bfme1f;
	char m_bfmePad2[8];
	char m_bfme28;
	char m_bfmePad3[0xf];
	char m_bfme38;
	char m_bfmePad4[0xb];
	char m_bfme44;
	char m_bfmePad5[2];
	char m_bfme47;
	char m_bfmePad6[0x10];
	char m_bfme58;
	char m_bfmePad7[0xb];
	char m_bfme64;
	char m_bfme65;
	char m_bfmePad8[2];
	int m_bfme68;
	char m_bfmePad9[4];
	char m_bfme70;
	char m_bfmePad10[0x1b];
	char m_bfme8c;
	char m_bfmePad11[0xaff];
	int m_bfmeb8c;
};

class BfmeS1148;

// The fourteen getters are the matched OptionPreferences rows (retail 0x00090D90..
// 0x000915E0, each reached through its ILT thunk); the parameter keeps its
// established BfmeS1148 spelling and is viewed as OptionPreferences.
class OptionPreferences
{
public:
	int getTextureReduction(void);
	int getParticleCap(void);
	unsigned char get3DShadows(void);
	unsigned char get2DShadows(void);
	bool getUsePixelShader(void);
	bool getBuildingOcclusionEnabled(void);
	bool getDynamicLODEnabled(void);
	unsigned char getTerrainLighting(void);
	unsigned char getAnisotropicTextureFiltering(void);
	unsigned char getSmoothWaterBorder(void);
	bool getExtraAnimationsDisabled(void);
	unsigned char getGrassDrawSkip(void);
	unsigned char getUseHighQualityVideo(void);
	unsigned char getShowProps(void);
};

class GlobalData;

// Retail [0x012ED5C8] is EA's writable GlobalData, defined by Common/GlobalData.cpp;
// this file views the same object through BfmeG1148 so the field offsets stay local.
extern GlobalData *TheWritableGlobalData;

void bfmeGo1148(BfmeS1148 *s)
{
	int n = 2 - (int)(((OptionPreferences *)s)->getTextureReduction() * 3 * 0.01f);

	if (n < 0)
		n = 0;
	else if (n > 2)
		n = 2;

	((BfmeG1148 *)TheWritableGlobalData)->m_bfme68 = n;
	((BfmeG1148 *)TheWritableGlobalData)->m_bfmeb8c = ((OptionPreferences *)s)->getParticleCap() * 0x1d + 0x64;
	((BfmeG1148 *)TheWritableGlobalData)->m_bfme64 = ((OptionPreferences *)s)->get3DShadows();
	((BfmeG1148 *)TheWritableGlobalData)->m_bfme65 = ((OptionPreferences *)s)->get2DShadows();
	((BfmeG1148 *)TheWritableGlobalData)->m_bfme28 = (char)(((OptionPreferences *)s)->getUsePixelShader() == 0);
	((BfmeG1148 *)TheWritableGlobalData)->m_bfme70 = ((OptionPreferences *)s)->getBuildingOcclusionEnabled();
	((BfmeG1148 *)TheWritableGlobalData)->m_bfme58 = ((OptionPreferences *)s)->getDynamicLODEnabled();
	((BfmeG1148 *)TheWritableGlobalData)->m_bfme44 = ((OptionPreferences *)s)->getTerrainLighting();
	((BfmeG1148 *)TheWritableGlobalData)->m_bfme38 = ((OptionPreferences *)s)->getTerrainLighting();
	((BfmeG1148 *)TheWritableGlobalData)->m_bfme47 = ((OptionPreferences *)s)->getAnisotropicTextureFiltering();
	((BfmeG1148 *)TheWritableGlobalData)->m_bfme8c = ((OptionPreferences *)s)->getSmoothWaterBorder();
	((BfmeG1148 *)TheWritableGlobalData)->m_bfme1c = ((OptionPreferences *)s)->getExtraAnimationsDisabled();
	BfmeG1148 *g = (BfmeG1148 *)TheWritableGlobalData;

	g->m_bfme1a = (char)(g->m_bfme1c == 0);
	((BfmeG1148 *)TheWritableGlobalData)->m_bfme1b = ((OptionPreferences *)s)->getGrassDrawSkip();
	((BfmeG1148 *)TheWritableGlobalData)->m_bfme1f = ((OptionPreferences *)s)->getUseHighQualityVideo();
	((BfmeG1148 *)TheWritableGlobalData)->m_bfme18 = ((OptionPreferences *)s)->getShowProps();
}
