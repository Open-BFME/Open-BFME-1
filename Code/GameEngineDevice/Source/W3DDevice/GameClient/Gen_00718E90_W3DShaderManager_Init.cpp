// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME retail 0x00718E90: W3DShaderManager::init.

typedef int Int;
typedef unsigned long Dword;
typedef unsigned short Word;
typedef unsigned char Byte;

class BfmeChipsetDetector
{
public:
	static void detect(void);
};

// The retail call is through the ILT at 0x0000CF8B, whose body is the
// shader-manager reset implementation at 0x00716770.
extern void j_0000cf8b(void);

class W3DShaderInterface
{
public:
	virtual Int slot0(void);
	virtual Int slot4(void);
	virtual Int init(void);
};

class W3DFilterInterface
{
public:
	virtual Int init(void);
};

typedef W3DShaderInterface **BfmeMasterShaderEntry;
typedef W3DFilterInterface **BfmeMasterFilterEntry;
typedef BfmeMasterShaderEntry BfmeMasterShaderList[100];
typedef BfmeMasterFilterEntry BfmeMasterFilterList[100];

struct BfmeShaderManagerStatics
{
	Dword pad00[5];
	Dword glowPixelShader;
	Dword glowVertexShader;
	Dword pad1c[2];
	Dword glowVertexDeclaration;
};

#define BfmeMasterShaderListAtRetail (*(BfmeMasterShaderList *)0x012BAE40)
#define BfmeMasterFilterListAtRetail (*(BfmeMasterFilterList *)0x012BAE60)
#define BfmeShaderManagerAtRetail (*(BfmeShaderManagerStatics *)0x012F9D00)
#define BfmeGlowVertexDeclaration BfmeShaderManagerAtRetail.glowVertexDeclaration
#define BfmeGlowVertexShader BfmeShaderManagerAtRetail.glowVertexShader
#define BfmeGlowPixelShader BfmeShaderManagerAtRetail.glowPixelShader

extern BfmeShaderManagerStatics g_bfmeShaderManager;


class BfmeVertexShaderLoader
{
public:
	static long LoadAndCreateD3DShader(const char *filename, Dword *shader);
};

class BfmeShaderLoader
{
public:
	static long LoadAndCreateD3DShader(const char *filename, Dword *shader);
};

class W3DShaderManager
{
public:
	static void init(void);
};

struct BfmeVertexElement
{
	Word stream;
	Word offset;
	Byte type;
	Byte method;
	Byte usage;
	Byte usageIndex;
};

class BfmeD3DDevice
{
public:
	virtual void slot00(void); virtual void slot04(void); virtual void slot08(void); virtual void slot0c(void);
	virtual void slot10(void); virtual void slot14(void); virtual void slot18(void); virtual void slot1c(void);
	virtual void slot20(void); virtual void slot24(void); virtual void slot28(void); virtual void slot2c(void);
	virtual void slot30(void); virtual void slot34(void); virtual void slot38(void); virtual void slot3c(void);
	virtual void slot40(void); virtual void slot44(void); virtual void slot48(void); virtual void slot4c(void);
	virtual void slot50(void); virtual void slot54(void); virtual void slot58(void); virtual void slot5c(void);
	virtual void slot60(void); virtual void slot64(void); virtual void slot68(void); virtual void slot6c(void);
	virtual void slot70(void); virtual void slot74(void); virtual void slot78(void); virtual void slot7c(void);
	virtual void slot80(void); virtual void slot84(void); virtual void slot88(void); virtual void slot8c(void);
	virtual void slot90(void); virtual void slot94(void); virtual void slot98(void); virtual void slot9c(void);
	virtual void slota0(void); virtual void slota4(void); virtual void slota8(void); virtual void slotac(void);
	virtual void slotb0(void); virtual void slotb4(void); virtual void slotb8(void); virtual void slotbc(void);
	virtual void slotc0(void); virtual void slotc4(void); virtual void slotc8(void); virtual void slotcc(void);
	virtual void slotd0(void); virtual void slotd4(void); virtual void slotd8(void); virtual void slotdc(void);
	virtual void slote0(void); virtual void slote4(void); virtual void slote8(void); virtual void slotec(void);
	virtual void slotf0(void); virtual void slotf4(void); virtual void slotf8(void); virtual void slotfc(void);
	virtual void slot100(void); virtual void slot104(void); virtual void slot108(void); virtual void slot10c(void);
	virtual void slot110(void); virtual void slot114(void); virtual void slot118(void); virtual void slot11c(void);
	virtual void slot120(void); virtual void slot124(void); virtual void slot128(void); virtual void slot12c(void);
	virtual void slot130(void); virtual void slot134(void); virtual void slot138(void); virtual void slot13c(void);
	virtual void slot140(void); virtual void slot144(void); virtual void slot148(void); virtual void slot14c(void);
	virtual void slot150(void); virtual void slot154(void);
	virtual Int __stdcall CreateVertexShader(const BfmeVertexElement *declaration, Dword *shader);
};

void W3DShaderManager::init(void)
{
	BfmeChipsetDetector::detect();
	j_0000cf8b();

	W3DShaderInterface **shaders;
	for (Int i = 0; BfmeMasterShaderListAtRetail[i] != 0; ++i) {
		shaders = BfmeMasterShaderListAtRetail[i];
		for (Int j = 0; shaders[j] != 0; ++j) {
			if (shaders[j]->init())
				break;
		}
	}

	W3DFilterInterface **filters;
	for (Int i = 0; BfmeMasterFilterListAtRetail[i] != 0; ++i) {
		filters = BfmeMasterFilterListAtRetail[i];
		for (Int j = 0; filters[j] != 0; ++j) {
			if (filters[j]->init())
				break;
		}
	}

	if (*(Byte *)((char *)*(void **)0x012ED5C8 + 0x28) == 0 &&
		*(Int *)0x012F9CF8 >= 3) {
		BfmeVertexElement declaration[] = {
			{ 0, 0, 3, 0, 0, 0 },
			{ 0, 0x10, 4, 0, 0x0a, 0 },
			{ 0, 0x14, 1, 0, 5, 0 },
			{ 0xff, 0, 0x11, 0, 0, 0 }
		};
		if (g_bfmeShaderManager.glowVertexDeclaration == 0) {
			BfmeD3DDevice *device = *(BfmeD3DDevice **)0x01340534;
			if (device->CreateVertexShader(declaration, &g_bfmeShaderManager.glowVertexDeclaration) < 0)
				g_bfmeShaderManager.glowVertexDeclaration = 0;
		}

		if (BfmeVertexShaderLoader::LoadAndCreateD3DShader("shaders\\Glow.vso", &BfmeGlowVertexShader) < 0)
			BfmeGlowVertexShader = 0;

		if (BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\Glow.pso", &BfmeGlowPixelShader) < 0)
			BfmeGlowPixelShader = 0;
	}
}
