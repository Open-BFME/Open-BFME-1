// ?testHardwareSupport@W3DSmudgeManager@@QAE_NXZ
// partial score=0.55 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

// W3DSmudgeManager::testHardwareSupport, retail 0x00722640, 1098 bytes.
// GeneralsMD W3DSmudge.cpp adapted to BFME: D3D9 DrawPrimitiveUP/SetVertexShader
// slots, copyRect, render-texture getter, TheDisplay getWidth/getHeight.

#include <string.h>

#define UNIQUE_COLOR (0x12345678)
#define BLOCK_SIZE 8

typedef int Int;
typedef int Bool;
#define FALSE 0
#define TRUE 1
typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef long HRESULT;

struct Vector4
{
	float x, y, z, w;
};

struct IDirect3DTexture8;

struct IDirect3DDevice9
{
	virtual HRESULT __stdcall unused00() = 0;
	virtual HRESULT __stdcall unused01() = 0;
	virtual HRESULT __stdcall unused02() = 0;
	virtual HRESULT __stdcall unused03() = 0;
	virtual HRESULT __stdcall unused04() = 0;
	virtual HRESULT __stdcall unused05() = 0;
	virtual HRESULT __stdcall unused06() = 0;
	virtual HRESULT __stdcall unused07() = 0;
	virtual HRESULT __stdcall unused08() = 0;
	virtual HRESULT __stdcall unused09() = 0;
	virtual HRESULT __stdcall unused10() = 0;
	virtual HRESULT __stdcall unused11() = 0;
	virtual HRESULT __stdcall unused12() = 0;
	virtual HRESULT __stdcall unused13() = 0;
	virtual HRESULT __stdcall unused14() = 0;
	virtual HRESULT __stdcall unused15() = 0;
	virtual HRESULT __stdcall unused16() = 0;
	virtual HRESULT __stdcall unused17() = 0;
	virtual HRESULT __stdcall unused18() = 0;
	virtual HRESULT __stdcall unused19() = 0;
	virtual HRESULT __stdcall unused20() = 0;
	virtual HRESULT __stdcall unused21() = 0;
	virtual HRESULT __stdcall unused22() = 0;
	virtual HRESULT __stdcall unused23() = 0;
	virtual HRESULT __stdcall unused24() = 0;
	virtual HRESULT __stdcall unused25() = 0;
	virtual HRESULT __stdcall unused26() = 0;
	virtual HRESULT __stdcall unused27() = 0;
	virtual HRESULT __stdcall unused28() = 0;
	virtual HRESULT __stdcall unused29() = 0;
	virtual HRESULT __stdcall unused30() = 0;
	virtual HRESULT __stdcall unused31() = 0;
	virtual HRESULT __stdcall unused32() = 0;
	virtual HRESULT __stdcall unused33() = 0;
	virtual HRESULT __stdcall unused34() = 0;
	virtual HRESULT __stdcall unused35() = 0;
	virtual HRESULT __stdcall unused36() = 0;
	virtual HRESULT __stdcall unused37() = 0;
	virtual HRESULT __stdcall unused38() = 0;
	virtual HRESULT __stdcall unused39() = 0;
	virtual HRESULT __stdcall unused40() = 0;
	virtual HRESULT __stdcall unused41() = 0;
	virtual HRESULT __stdcall unused42() = 0;
	virtual HRESULT __stdcall unused43() = 0;
	virtual HRESULT __stdcall unused44() = 0;
	virtual HRESULT __stdcall unused45() = 0;
	virtual HRESULT __stdcall unused46() = 0;
	virtual HRESULT __stdcall unused47() = 0;
	virtual HRESULT __stdcall unused48() = 0;
	virtual HRESULT __stdcall unused49() = 0;
	virtual HRESULT __stdcall unused50() = 0;
	virtual HRESULT __stdcall unused51() = 0;
	virtual HRESULT __stdcall unused52() = 0;
	virtual HRESULT __stdcall unused53() = 0;
	virtual HRESULT __stdcall unused54() = 0;
	virtual HRESULT __stdcall unused55() = 0;
	virtual HRESULT __stdcall unused56() = 0;
	virtual HRESULT __stdcall unused57() = 0;
	virtual HRESULT __stdcall unused58() = 0;
	virtual HRESULT __stdcall unused59() = 0;
	virtual HRESULT __stdcall unused60() = 0;
	virtual HRESULT __stdcall unused61() = 0;
	virtual HRESULT __stdcall unused62() = 0;
	virtual HRESULT __stdcall unused63() = 0;
	virtual HRESULT __stdcall unused64() = 0;
	virtual HRESULT __stdcall SetTexture(DWORD, IDirect3DTexture8 *) = 0;
	virtual HRESULT __stdcall unused66() = 0;
	virtual HRESULT __stdcall unused67() = 0;
	virtual HRESULT __stdcall unused68() = 0;
	virtual HRESULT __stdcall unused69() = 0;
	virtual HRESULT __stdcall unused70() = 0;
	virtual HRESULT __stdcall unused71() = 0;
	virtual HRESULT __stdcall unused72() = 0;
	virtual HRESULT __stdcall unused73() = 0;
	virtual HRESULT __stdcall unused74() = 0;
	virtual HRESULT __stdcall unused75() = 0;
	virtual HRESULT __stdcall unused76() = 0;
	virtual HRESULT __stdcall unused77() = 0;
	virtual HRESULT __stdcall unused78() = 0;
	virtual HRESULT __stdcall unused79() = 0;
	virtual HRESULT __stdcall unused80() = 0;
	virtual HRESULT __stdcall unused81() = 0;
	virtual HRESULT __stdcall unused82() = 0;
	virtual HRESULT __stdcall DrawPrimitiveUP(unsigned PrimitiveType, UINT PrimitiveCount,
		const void *pVertexStreamZeroData, UINT VertexStreamZeroStride) = 0;
	virtual HRESULT __stdcall unused84() = 0;
	virtual HRESULT __stdcall unused85() = 0;
	virtual HRESULT __stdcall unused86() = 0;
	virtual HRESULT __stdcall unused87() = 0;
	virtual HRESULT __stdcall unused88() = 0;
	virtual HRESULT __stdcall SetVertexShader(DWORD) = 0;
};

extern IDirect3DDevice9 *g_d3dDevice;
extern unsigned char g_renderingToTexture;
int Rva007175A0Get(void);

class VertexMaterialClass
{
public:
	enum PresetType { PRELIT_DIFFUSE = 0 };
	static VertexMaterialClass *Get_Preset(PresetType type);
	virtual void Delete_This(void);
	unsigned short m_refCount;
};

extern VertexMaterialClass *g_currentMaterial;
extern unsigned g_renderStateChanged;

class Display
{
public:
	virtual void u00(); virtual void u01(); virtual void u02(); virtual void u03();
	virtual void u04(); virtual void u05(); virtual void u06(); virtual void u07();
	virtual void u08(); virtual void u09(); virtual void u10();
	virtual int getWidth(void);
	virtual int getHeight(void);
};

extern Display *TheDisplay;

class TextureBaseClass;
void BoxSetTexture(unsigned index, TextureBaseClass *&tex);
void Apply_Render_State_Changes(void);

Int copyRect(unsigned char *buf, Int bufSize, int oX, int oY, int width, int height);

class SmudgeManager
{
public:
	virtual ~SmudgeManager();
	virtual void init(void);
	virtual void reset(void);
	virtual void ReleaseResources(void);
	virtual void ReAcquireResources(void);

	enum HardwareSmudgeSupport { SMUDGE_SUPPORT_UNKNOWN = 0, SMUDGE_SUPPORT_NO = 1, SMUDGE_SUPPORT_YES = 2 };

	HardwareSmudgeSupport m_hardwareSupportStatus;
	char m_pad[0x1C];
};

class W3DSmudgeManager : public SmudgeManager
{
public:
	bool testHardwareSupport(void);
};

bool W3DSmudgeManager::testHardwareSupport(void)
{
	if (m_hardwareSupportStatus == SMUDGE_SUPPORT_UNKNOWN)
	{
		IDirect3DTexture8 *backTexture = (IDirect3DTexture8 *)Rva007175A0Get();
		if (!backTexture)
		{
			m_hardwareSupportStatus = SMUDGE_SUPPORT_NO;
			return false;
		}

		if (!g_renderingToTexture)
			return false;

		VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		if (vmat)
			++vmat->m_refCount;
		if (g_currentMaterial)
		{
			if (--g_currentMaterial->m_refCount == 0)
				g_currentMaterial->Delete_This();
		}
		g_currentMaterial = vmat;
		g_renderStateChanged |= 0x4000;
		if (vmat)
		{
			if (--vmat->m_refCount == 0)
				vmat->Delete_This();
		}

		TextureBaseClass *none = 0;
		BoxSetTexture(0, none);
		Apply_Render_State_Changes();

		struct _TRANS_LIT_TEX_VERTEX {
			Vector4 p;
			DWORD color;
			float u;
			float v;
		} v[4];

		float invW = (float)BLOCK_SIZE / (float)TheDisplay->getWidth();
		float invH = (float)BLOCK_SIZE / (float)TheDisplay->getHeight();

		v[0].p.x = (float)BLOCK_SIZE - 0.5f; v[0].p.y = (float)BLOCK_SIZE - 0.5f; v[0].p.z = 0.0f; v[0].p.w = 1.0f;
		v[0].u = invW; v[0].v = invH;
		v[1].p.x = (float)BLOCK_SIZE - 0.5f; v[1].p.y = 0.0f - 0.5f; v[1].p.z = 0.0f; v[1].p.w = 1.0f;
		v[1].u = invW; v[1].v = 0;
		v[2].p.x = 0.0f - 0.5f; v[2].p.y = (float)BLOCK_SIZE - 0.5f; v[2].p.z = 0.0f; v[2].p.w = 1.0f;
		v[2].u = 0; v[2].v = invH;
		v[3].p.x = 0.0f - 0.5f; v[3].p.y = 0.0f - 0.5f; v[3].p.z = 0.0f; v[3].p.w = 1.0f;
		v[3].u = 0; v[3].v = 0;

		v[0].color = UNIQUE_COLOR;
		v[1].color = UNIQUE_COLOR;
		v[2].color = UNIQUE_COLOR;
		v[3].color = UNIQUE_COLOR;

		IDirect3DDevice9 *pDev = g_d3dDevice;
		pDev->SetVertexShader(0x144);
		pDev->DrawPrimitiveUP(5, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));

		DWORD refData[BLOCK_SIZE * BLOCK_SIZE];
		memset(refData, 0, sizeof(refData));
		Int bufSize = copyRect((unsigned char *)refData, sizeof(refData), 0, 0, BLOCK_SIZE, BLOCK_SIZE);
		if (!bufSize)
		{
			m_hardwareSupportStatus = SMUDGE_SUPPORT_NO;
			return false;
		}

		pDev->SetTexture(0, backTexture);

		DWORD testData[BLOCK_SIZE * BLOCK_SIZE];
		memset(testData, 0xff, sizeof(testData));

		v[0].color = 0xffffffff;
		v[1].color = 0xffffffff;
		v[2].color = 0xffffffff;
		v[3].color = 0xffffffff;

		pDev->DrawPrimitiveUP(5, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));
		bufSize = copyRect((unsigned char *)testData, sizeof(testData), 0, 0, BLOCK_SIZE, BLOCK_SIZE);

		if (!bufSize)
		{
			m_hardwareSupportStatus = SMUDGE_SUPPORT_NO;
			return false;
		}

		if (memcmp(testData, refData, (unsigned)bufSize) == 0)
		{
			m_hardwareSupportStatus = SMUDGE_SUPPORT_YES;
			return true;
		}
		m_hardwareSupportStatus = SMUDGE_SUPPORT_NO;
	}

	return m_hardwareSupportStatus == SMUDGE_SUPPORT_YES;
}
