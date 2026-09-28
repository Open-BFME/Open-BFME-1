// ?rva006EB500@W3DDisplay@@QAE_NI@Z
// partial score=0.96 date=2026-09-28
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x006EB500 (1215 B, ret 4): the per-frame render pass of BFME's
// W3DDisplay::draw.  Its only caller is W3DDisplay::draw (0x006F3FC0, vtable
// 0x0111EDD0 slot 7), which calls it twice through ILT 0x0001EF7B with the
// frame time.  The body is Zero Hour W3DDisplay::draw's loop body with the
// loop pulled out: the load-screen `continue` becomes `return true`, and the
// closing freeze test (isTimeFrozenDebug / script freeze / isGamePaused)
// becomes `return false`.  BFME adds the render lock held for the whole pass
// (W3DRadarResetLock ... bfmeUnlock1179), the shroud and taint camera
// updates, the scene-render object at +0x180 and the video panel at +0x34.
// No caller or string names the helper, so it keeps the address token.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;
typedef unsigned char UnsignedByte;

class CameraClass;

class Vector3
{
public:
	Real X;
	Real Y;
	Real Z;
};

enum WW3DErrorType
{
	WW3D_ERROR_OK = 1
};

class WW3D
{
public:
	static bool Begin_Render(bool clear, bool clearz, const Vector3 &color,
		float dest_alpha, void (*callback)(void));
	static bool End_Render(bool flip_frame);
};

class ShaderClass;

namespace Debug_Statistics
{
	void End_Statistics(void);
	void Record_DX8_Polys_And_Vertices(int polys, int vertices, const ShaderClass &shader);
}

extern const ShaderClass g_presetOpaqueShader012D6E08;

// Debug_Statistics polygon / vertex getters (address-derived ledger names).
Int Rva00937260Get(void);
Int Rva00937270Get(void);

void W3DRadarResetLock(void);
char bfmeUnlock1179(void);
void Rva00755C80(void);
void bfmeGoKA(void);

// Render lock held for the whole pass; retail unwinds through bfmeUnlock1179.
class Rva006EB500RenderLock
{
public:
	Rva006EB500RenderLock(void) { W3DRadarResetLock(); }
	~Rva006EB500RenderLock(void) { bfmeUnlock1179(); }
};

struct IDirect3DDevice8
{
	virtual long __stdcall QueryInterface(void);
	virtual unsigned long __stdcall AddRef(void);
	virtual unsigned long __stdcall Release(void);
	virtual long __stdcall TestCooperativeLevel(void);
};

class DX8Wrapper
{
protected:
	static IDirect3DDevice8 *D3DDevice;

public:
	static IDirect3DDevice8 *_Get_D3D_Device8(void) { return D3DDevice; }
};

class ParticleSystemManager
{
public:
	virtual void slot000(void);
	virtual void slot004(void);
	virtual void slot008(void);
	virtual void slot00C(void);
	virtual void slot010(void);
	virtual void update(void);
};
extern ParticleSystemManager *TheParticleSystemManager;

class GameWindowManager
{
public:
	char m_pad00[0x38];
	Int m_renderLock;
};
extern GameWindowManager *TheWindowManager;

class InGameUI
{
public:
	virtual void slot000(void);
	virtual void slot004(void);
	virtual void slot008(void);
	virtual void slot00C(void);
	virtual void slot010(void);
	virtual void slot014(void);
	virtual void slot018(void);
	virtual void slot01C(void);
	virtual void slot020(void);
	virtual void slot024(void);
	virtual void slot028(void);
	virtual void slot02C(void);
	virtual void slot030(void);
	virtual void slot034(void);
	virtual void slot038(void);
	virtual void slot03C(void);
	virtual void slot040(void);
	virtual void slot044(void);
	virtual void slot048(void);
	virtual void slot04C(void);
	virtual void slot050(void);
	virtual void slot054(void);
	virtual void slot058(void);
	virtual void slot05C(void);
	virtual void slot060(void);
	virtual void slot064(void);
	virtual void slot068(void);
	virtual void slot06C(void);
	virtual void slot070(void);
	virtual void slot074(void);
	virtual void slot078(void);
	virtual void slot07C(void);
	virtual void slot080(void);
	virtual void slot084(void);
	virtual void slot088(void);
	virtual void slot08C(void);
	virtual void slot090(void);
	virtual void slot094(void);
	virtual void slot098(void);
	virtual void slot09C(void);
	virtual void slot0A0(void);
	virtual void slot0A4(void);
	virtual void slot0A8(void);
	virtual void slot0AC(void);
	virtual void slot0B0(void);
	virtual void slot0B4(void);
	virtual void slot0B8(void);
	virtual void slot0BC(void);
	virtual void slot0C0(void);
	virtual void slot0C4(void);
	virtual void slot0C8(void);
	virtual void slot0CC(void);
	virtual void slot0D0(void);
	virtual void slot0D4(void);
	virtual void slot0D8(void);
	virtual void slot0DC(void);
	virtual void slot0E0(void);
	virtual void slot0E4(void);
	virtual void slot0E8(void);
	virtual void slot0EC(void);
	virtual void slot0F0(void);
	virtual void slot0F4(void);
	virtual void slot0F8(void);
	virtual void slot0FC(void);
	virtual void slot100(void);
	virtual void slot104(void);
	virtual void slot108(void);
	virtual void slot10C(void);
	virtual void slot110(void);
	virtual void slot114(void);
	virtual void slot118(void);
	virtual void slot11C(void);
	virtual void slot120(void);
	virtual void slot124(void);
	virtual void slot128(void);
	virtual void slot12C(void);
	virtual void slot130(void);
	virtual void slot134(void);
	virtual void slot138(void);
	virtual void slot13C(void);
	virtual void slot140(void);
	virtual void slot144(void);
	virtual void slot148(void);
	virtual void slot14C(void);
	virtual void slot150(void);
	virtual Bool slot154(void);
	void rva1f8f2(void);
};
extern InGameUI *TheInGameUI;

struct Rva00579160Manager
{
	virtual void slot000(void);
	virtual void slot004(void);
	virtual void slot008(void);
	virtual void slot00C(void);
	virtual void slot010(void);
	virtual void slot014(void);
	virtual void slot018(void);
	virtual void slot01C(void);
};
extern Rva00579160Manager *Rva00579160TheManager;

struct Rva005A63D0Mouse
{
	virtual void slot000(void);
	virtual void slot004(void);
	virtual void slot008(void);
	virtual void slot00C(void);
	virtual void slot010(void);
	virtual void slot014(void);
	virtual void slot018(void);
	virtual void slot01C(void);
};
extern Rva005A63D0Mouse *TheMouse;

struct Rva005A00B0Transition
{
	virtual void slot000(void);
	virtual void slot004(void);
	virtual void slot008(void);
	virtual void slot00C(void);
	virtual void slot010(void);
	virtual void slot014(void);
	virtual void slot018(void);
	virtual void slot01C(void);
};
extern Rva005A00B0Transition *TheTransitionHandler;

// GlobalData flags; Zero Hour's twin reads m_breakTheMovie, m_disableRender
// and m_loadScreenRender at these points.
struct Rva006C9270GlobalData
{
	char m_pad000[0xbb9];
	Bool m_bb9;
	char m_padbba[0xc0b - 0xbba];
	Bool m_c0b;
	char m_padc0c[0xdbf - 0xc0c];
	Bool m_dbf;
};
extern Rva006C9270GlobalData *TheWritableGlobalData;

struct Rva00367E30Logic
{
	char m_pad000[0x11d];
	Bool m_renderFlag;
};
extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeGameLogicPause { public: Bool isGamePaused(void); };
class GameLogic { public: Bool rva000652A0(void) const; };

class ScriptEngine
{
public:
	Bool isTimeFrozenDebug(void);
	Bool _bfme_isClientFrameFrozen(void);
	// Inlined pair: retail keeps this in esi across both calls.
	Bool frozenPair006EB500(void) { return isTimeFrozenDebug() || _bfme_isClientFrameFrozen(); }
};
class Rva00336EF0ByteField { public: UnsignedByte get(void) const; };
extern ScriptEngine *TheScriptEngine;

class Rva003968A0 { public: Bool test(void); };
class Glo012F1028Type;
extern Glo012F1028Type *Glo012F1028;

class BfmeGlobPB
{
public:
	char m_pad000[0x868];
	Int m_868;
};
extern BfmeGlobPB *g_bfmeGlobPB;

class W3DShroud { public: void render(CameraClass *camera); };
class Rva00727E00 { public: void update(CameraClass *camera); };

class BfmeA1087
{
public:
	Real getWaterTransparency(void) const { return m_waterTransparency; }

	char m_pad0000[0x2ff4];
	void *m_terrainMap;
	char m_pad2ff8[0x301c - 0x2ff8];
	Real m_waterTransparency;
	char m_pad3020[0x30b8 - 0x3020];
	W3DShroud *m_shroud;
	Rva00727E00 *m_taint;
};
extern BfmeA1087 *g_bfmeA1087;

class View
{
public:
	char m_pad000[0x104];
	CameraClass *m_3DCamera;
};

class Rva0081D520Owner { public: void broadcast(Int value, Real a, Real b, Real c, Real d); };

struct Rva006EB500PanelData
{
	char m_pad00[0x18];
	Rva0081D520Owner *m_18;
};

class Rva006EB500Panel
{
public:
	virtual void slot000(void);
	virtual void slot004(void);
	virtual void slot008(void);
	virtual void slot00C(void);
	virtual void slot010(void);
	virtual void slot014(void);
	virtual void slot018(void);
	virtual void slot01C(void);
	virtual Int slot020(void);
	virtual void slot024(void);
	virtual void slot028(void);
	virtual void slot02C(void);
	virtual void slot030(void);
	virtual void slot034(void);
	virtual void slot038(void);
	virtual Int slot03C(Int a, Int b, Int c, Int d, Int e);
	void *m_04;
	Rva006EB500PanelData *m_data;
};

class Rva006FDE50SceneRender
{
public:
	void render(void);

	void *m_00;
	Int m_state;
	Bool m_enabled;
};

class BfmeThing923E { public: void bfmeGo923E(Int pass, void *mode); };
class Gen_0040e1f0 { public: void m(void); };

class W3DDisplay
{
public:
	virtual void slot000(void);
	virtual void slot004(void);
	virtual void slot008(void);
	virtual void slot00C(void);
	virtual void slot010(void);
	virtual void slot014(void);
	virtual void slot018(void);
	virtual void slot01C(void);
	virtual void slot020(void);
	virtual void slot024(void);
	virtual void slot028(void);
	virtual UnsignedInt getWidth(void);
	virtual UnsignedInt getHeight(void);
	virtual void slot034(void);
	virtual void slot038(void);
	virtual void slot03C(void);
	virtual void slot040(void);
	virtual void slot044(void);
	virtual void slot048(void);
	virtual void slot04C(void);
	virtual void slot050(void);
	virtual void slot054(void);
	virtual void slot058(void);
	virtual void slot05C(void);
	virtual void slot060(void);
	virtual void slot064(void);
	virtual void slot068(void);
	virtual void slot06C(void);
	virtual void slot070(void);
	virtual View *getFirstView(void);
	virtual void slot078(void);
	virtual void drawViews(void);
	virtual void updateViews(void);
	virtual void slot084(void);
	virtual void slot088(void);
	virtual void slot08C(void);
	virtual void slot090(void);
	virtual void slot094(void);
	virtual void slot098(void);
	virtual void slot09C(void);
	virtual void slot0A0(void);
	virtual void slot0A4(void);
	virtual void slot0A8(void);
	virtual void slot0AC(void);
	virtual void slot0B0(void);
	virtual void slot0B4(void);
	virtual void slot0B8(void);
	virtual void slot0BC(void);
	virtual void slot0C0(void);
	virtual void slot0C4(void);
	virtual void slot0C8(void);
	virtual void slot0CC(void);
	virtual void slot0D0(void);
	virtual void slot0D4(void);
	virtual void slot0D8(void);
	virtual void slot0DC(void);
	virtual void slot0E0(Int value);
	virtual void slot0E4(void);
	virtual void slot0E8(void);
	virtual void slot0EC(void);
	virtual void slot0F0(void);
	virtual void slot0F4(void);
	virtual void slot0F8(void);
	virtual void slot0FC(void);
	virtual void slot100(void);
	virtual void slot104(void);
	virtual void slot108(void);
	virtual void slot10C(void);
	virtual void slot110(void);
	virtual void slot114(void);
	virtual void slot118(void);
	virtual void slot11C(void);
	virtual void slot120(void);
	virtual void slot124(void);
	virtual void slot128(void);
	virtual void slot12C(void);
	virtual void slot130(void);
	virtual void slot134(void);
	virtual void slot138(void);
	virtual void slot13C(void);
	virtual void slot140(void);
	virtual void slot144(void);
	virtual void slot148(void);
	virtual void slot14C(void);
	virtual void slot150(void);
	virtual void slot154(void);
	virtual void slot158(void);
	virtual void slot15C(void);
	virtual void slot160(void);
	virtual void slot164(void);
	virtual void slot168(void);

	Bool rva006EB500(UnsignedInt now);
	void rva0040EE90(void);

protected:
	void drawCurrentDebugDisplay(void);
	void renderLetterBox(UnsignedInt time);

	char m_pad004[0x1c - 4];
	Vector3 m_1c;
	char m_pad028[4];
	void *m_debugDisplayCallback;
	char m_pad030[4];
	Rva006EB500Panel *m_34;
	char m_pad038[0xd0 - 0x38];
	Real m_letterBoxFadeLevel;
	char m_pad0d4[0xf8 - 0xd4];
	Int m_f8;
	Int m_fc;
	Int m_100;
	Int m_104;
	char m_pad108[0x13c - 0x108];
	Bool m_13c;
	char m_pad13d[0x180 - 0x13d];
	Rva006FDE50SceneRender *m_180;
};

extern Bool g_couldRender012BAA54;

Bool W3DDisplay::rva006EB500(UnsignedInt now)
{
	Rva006EB500RenderLock lock;

	if (DX8Wrapper::_Get_D3D_Device8() && DX8Wrapper::_Get_D3D_Device8()->TestCooperativeLevel() == 0)
	{
		if (!TheBfmeGameLogic->m_renderFlag)
		{
			updateViews();
			Rva00755C80();
		}
		TheParticleSystemManager->update();
	}

	Debug_Statistics::End_Statistics();

	Int numRenderTargetPolygons = Rva00937260Get();
	Int numRenderTargetVertices = Rva00937270Get();

	if (g_bfmeA1087 && g_bfmeA1087->m_terrainMap)
	{
		View *view = getFirstView();
		if (g_bfmeA1087->m_shroud)
		{
			CameraClass *camera = view->m_3DCamera;
			g_bfmeA1087->m_shroud->render(camera);
		}
		if (g_bfmeA1087->m_taint)
		{
			CameraClass *camera = view->m_3DCamera;
			g_bfmeA1087->m_taint->update(camera);
		}
	}

	if (!TheWritableGlobalData->m_dbf && !TheWritableGlobalData->m_c0b &&
		WW3D::Begin_Render(true, true, m_1c, g_bfmeA1087->getWaterTransparency(), 0) == WW3D_ERROR_OK)
	{
		if (TheWritableGlobalData->m_bb9 == 1)
		{
			TheWindowManager->m_renderLock = 1;
			TheInGameUI->slot01C();
			Rva00579160TheManager->slot01C();
			TheWindowManager->m_renderLock = -1;
			if (TheMouse)
				TheMouse->slot01C();
			WW3D::End_Render(true);
			return true;
		}

		g_couldRender012BAA54 = true;
		if (numRenderTargetPolygons || numRenderTargetVertices)
			Debug_Statistics::Record_DX8_Polys_And_Vertices(numRenderTargetPolygons,
				numRenderTargetVertices, g_presetOpaqueShader012D6E08);
		g_bfmeGlobPB->m_868 = 0;

		Bool fading = m_letterBoxFadeLevel > 0.0f;
		if (m_180 && m_180->m_enabled)
		{
			m_180->render();
			Int state = m_180->m_state;
			if (state != 2)
			{
				TheWindowManager->m_renderLock = 1;
				TheInGameUI->slot01C();
				if (!fading)
					TheInGameUI->slot130();
				Rva00579160TheManager->slot01C();
				TheWindowManager->m_renderLock = 0;
				TheInGameUI->slot01C();
				TheWindowManager->m_renderLock = -1;
			}
		}
		else
		{
			drawViews();
			((BfmeThing923E *)this)->bfmeGo923E(0, (void *)2);
			((BfmeThing923E *)this)->bfmeGo923E(1, (void *)2);
			((BfmeThing923E *)this)->bfmeGo923E(2, (void *)2);
			if (!m_34)
				rva0040EE90();
			TheWindowManager->m_renderLock = 1;
			TheInGameUI->slot01C();
			if (!fading)
				TheInGameUI->slot130();
			Rva00579160TheManager->slot01C();
			TheWindowManager->m_renderLock = 0;
			TheInGameUI->slot01C();
			TheWindowManager->m_renderLock = -1;
		}
		TheInGameUI->rva1f8f2();
		if (TheMouse)
			TheMouse->slot01C();

		if (m_34)
		{
			((BfmeThing923E *)this)->bfmeGo923E(0, (void *)1);
			((BfmeThing923E *)this)->bfmeGo923E(1, (void *)1);
			slot0E0(m_34->slot03C(m_f8, m_fc, m_100, m_104, -1));
			((BfmeThing923E *)this)->bfmeGo923E(2, (void *)1);
			rva0040EE90();
			((Gen_0040e1f0 *)this)->m();
			Rva0081D520Owner *owner = m_34->m_data->m_18;
			if (owner)
				owner->broadcast(m_34->slot020(), 0.0f, 0.0f, (Real)getWidth(), (Real)getHeight());
		}

		renderLetterBox(now);

		if (fading)
			TheInGameUI->slot130();
		if (!TheInGameUI->slot154())
		{
			if (((Rva003968A0 *)Glo012F1028)->test() || ((GameLogic *)TheBfmeGameLogic)->rva000652A0())
			{
				if (m_13c)
				{
					slot168();
					bfmeGoKA();
				}
			}
		}
		TheTransitionHandler->slot01C();
		if (m_debugDisplayCallback)
			drawCurrentDebugDisplay();
		WW3D::End_Render(true);
	}
	else
	{
		if (g_couldRender012BAA54)
			g_couldRender012BAA54 = false;
	}

	if (TheScriptEngine->frozenPair006EB500() ||
		((Rva00336EF0ByteField *)TheScriptEngine)->get() || ((BfmeGameLogicPause *)TheBfmeGameLogic)->isGamePaused())
		return false;
	return true;
}
