// ?rva006EB500@W3DDisplay@@QAE_NI@Z
// partial score=0.46 date=2026-09-27
// cl: /O2 /Ob1 /EHsc
// BFME 0x006EB500: W3DDisplay render helper with a proven one-word ABI.

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

class CameraClass;
class W3DShroud
{
public:
	void render(CameraClass *camera);
};

class Rva00727E00
{
public:
	void update(CameraClass *camera);
};

class BfmeA1087
{
public:
	char m_pad2ff4[0x2ff4];
	void *m_terrainMap;
	char m_pad2ff8[0x24];
	float m_waterTransparency;
	char m_pad3020[0x98];
	W3DShroud *m_shroud;
	Rva00727E00 *m_taint;
};

extern BfmeA1087 *g_bfmeA1087;

class Rva00367E30Logic
{
public:
	char m_pad00[0x11d];
	UnsignedByte m_renderFlag;
	bool rva4a0de(void);
	bool rva22c96(void);
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class Rva006C9270GlobalData
{
public:
	char m_pad00[0xbb9];
	UnsignedByte m_letterBoxState;
	char m_padbba[0x51];
	UnsignedByte m_renderState;
	char m_padc0c[0x1b3];
	UnsignedByte m_movieState;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

class IDirect3DDevice8
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual long __stdcall TestCooperativeLevel(void);
};

namespace DX8Wrapper
{
	extern IDirect3DDevice8 *D3DDevice;
}

class ParticleSystemManager
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void update(void);
};

extern ParticleSystemManager *TheParticleSystemManager;

class GameWindowManager
{
public:
	char m_pad00[0x38];
	int m_renderLock;
};

extern GameWindowManager *TheWindowManager;

#define BFME_UI_VOID_SLOT(n) virtual void slot##n(void);
class InGameUI
{
public:
	BFME_UI_VOID_SLOT(00) BFME_UI_VOID_SLOT(04) BFME_UI_VOID_SLOT(08)
	BFME_UI_VOID_SLOT(0c) BFME_UI_VOID_SLOT(10) BFME_UI_VOID_SLOT(14)
	BFME_UI_VOID_SLOT(18)
	virtual void slot1c(void);
	BFME_UI_VOID_SLOT(20) BFME_UI_VOID_SLOT(24) BFME_UI_VOID_SLOT(28)
	BFME_UI_VOID_SLOT(2c) BFME_UI_VOID_SLOT(30) BFME_UI_VOID_SLOT(34)
	BFME_UI_VOID_SLOT(38) BFME_UI_VOID_SLOT(3c) BFME_UI_VOID_SLOT(40)
	BFME_UI_VOID_SLOT(44) BFME_UI_VOID_SLOT(48) BFME_UI_VOID_SLOT(4c)
	BFME_UI_VOID_SLOT(50) BFME_UI_VOID_SLOT(54) BFME_UI_VOID_SLOT(58)
	BFME_UI_VOID_SLOT(5c) BFME_UI_VOID_SLOT(60) BFME_UI_VOID_SLOT(64)
	BFME_UI_VOID_SLOT(68) BFME_UI_VOID_SLOT(6c) BFME_UI_VOID_SLOT(70)
	BFME_UI_VOID_SLOT(74) BFME_UI_VOID_SLOT(78) BFME_UI_VOID_SLOT(7c)
	BFME_UI_VOID_SLOT(80) BFME_UI_VOID_SLOT(84) BFME_UI_VOID_SLOT(88)
	BFME_UI_VOID_SLOT(8c) BFME_UI_VOID_SLOT(90) BFME_UI_VOID_SLOT(94)
	BFME_UI_VOID_SLOT(98) BFME_UI_VOID_SLOT(9c) BFME_UI_VOID_SLOT(a0)
	BFME_UI_VOID_SLOT(a4) BFME_UI_VOID_SLOT(a8) BFME_UI_VOID_SLOT(ac)
	BFME_UI_VOID_SLOT(b0) BFME_UI_VOID_SLOT(b4) BFME_UI_VOID_SLOT(b8)
	BFME_UI_VOID_SLOT(bc) BFME_UI_VOID_SLOT(c0) BFME_UI_VOID_SLOT(c4)
	BFME_UI_VOID_SLOT(c8) BFME_UI_VOID_SLOT(cc) BFME_UI_VOID_SLOT(d0)
	BFME_UI_VOID_SLOT(d4) BFME_UI_VOID_SLOT(d8) BFME_UI_VOID_SLOT(dc)
	BFME_UI_VOID_SLOT(e0) BFME_UI_VOID_SLOT(e4) BFME_UI_VOID_SLOT(e8)
	BFME_UI_VOID_SLOT(ec) BFME_UI_VOID_SLOT(f0) BFME_UI_VOID_SLOT(f4)
	BFME_UI_VOID_SLOT(f8) BFME_UI_VOID_SLOT(fc) BFME_UI_VOID_SLOT(100)
	BFME_UI_VOID_SLOT(104) BFME_UI_VOID_SLOT(108) BFME_UI_VOID_SLOT(10c)
	BFME_UI_VOID_SLOT(110) BFME_UI_VOID_SLOT(114) BFME_UI_VOID_SLOT(118)
	BFME_UI_VOID_SLOT(11c) BFME_UI_VOID_SLOT(120) BFME_UI_VOID_SLOT(124)
	BFME_UI_VOID_SLOT(128) BFME_UI_VOID_SLOT(12c)
	virtual void slot130(void);
	BFME_UI_VOID_SLOT(134) BFME_UI_VOID_SLOT(138) BFME_UI_VOID_SLOT(13c)
	BFME_UI_VOID_SLOT(140) BFME_UI_VOID_SLOT(144) BFME_UI_VOID_SLOT(148)
	BFME_UI_VOID_SLOT(14c) BFME_UI_VOID_SLOT(150)
	virtual bool slot154(void);
	void rva1f8f2(void);
};
#undef BFME_UI_VOID_SLOT

extern InGameUI *TheInGameUI;

class Rva00579160Manager
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
};

extern Rva00579160Manager *Rva00579160TheManager;

class Rva005A63D0Mouse
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
};

extern Rva005A63D0Mouse *TheMouse;

class Rva005A00B0Transition
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
};

extern Rva005A00B0Transition *TheTransitionHandler;

class Glo012F1028Type
{
public:
	bool rva0000bb81(void);
};

extern Glo012F1028Type *Glo012F1028;

class ScriptEngine
{
public:
	bool rva0003f23d(void);
	bool rva00003783(void);
	bool rva00027318(void);
};

extern ScriptEngine *TheScriptEngine;

class BfmeGlobPB
{
public:
	char m_pad00[0x868];
	void *m_field868;
};

extern BfmeGlobPB *g_bfmeGlobPB;

class BfmeThing923E
{
public:
	void bfmeGo923E(int first, void *second);
};

class Rva0081D520Owner
{
public:
	void broadcast(int value, float a, float b, float c, float d);
};

class Rva006EB500SubData
{
public:
	char m_pad00[0x18];
	void *m_field18;
};

#define BFME_SUB_VOID_SLOT(n) virtual void slot##n(void);
class Rva006EB500Sub
{
public:
	BFME_SUB_VOID_SLOT(00) BFME_SUB_VOID_SLOT(04) BFME_SUB_VOID_SLOT(08)
	BFME_SUB_VOID_SLOT(0c) BFME_SUB_VOID_SLOT(10) BFME_SUB_VOID_SLOT(14)
	BFME_SUB_VOID_SLOT(18) BFME_SUB_VOID_SLOT(1c) BFME_SUB_VOID_SLOT(20)
	BFME_SUB_VOID_SLOT(24) BFME_SUB_VOID_SLOT(28) BFME_SUB_VOID_SLOT(2c)
	BFME_SUB_VOID_SLOT(30) BFME_SUB_VOID_SLOT(34) BFME_SUB_VOID_SLOT(38)
	virtual int slot3c(int a, int b, int c, int d, int e);
	char m_pad04[4];
	Rva006EB500SubData *m_data;
};
#undef BFME_SUB_VOID_SLOT

class Rva006EB500Node
{
public:
	char m_pad00[4];
	int m_state;
	UnsignedByte m_enabled;
	void rva000371a0(void);
};

class Vector3
{
public:
	float x;
	float y;
	float z;
};

enum WW3DErrorType
{
	WW3D_ERROR_OK = 1
};

class WW3D
{
public:
	static WW3DErrorType Begin_Render(bool clear, bool clearz,
		const Vector3 &color, float alpha, void (*callback)(void));
	static WW3DErrorType End_Render(bool flipFrame);
};

namespace Debug_Statistics
{
	class ShaderClass;
	void End_Statistics(void);
	void Record_DX8_Polys_And_Vertices(int polygons, int vertices,
		const ShaderClass &shader);
}

extern int Rva00937260Get(void);
extern int Rva00937270Get(void);
extern const float BfmeZeroRange;
extern float g_bfmeUint32Scale;
extern void Rva00755C80(void);
extern void W3DRadarResetLock(void);
extern char bfmeUnlock1179(void);
extern void j_000218a0(void);
extern void j_0001a4c9(void);

class W3DDisplay;
class Rva006EB500Node;

#define W3D_VOID_SLOT(n) virtual void slot##n(void);
class __declspec(novtable) W3DDisplay
{
public:
	W3D_VOID_SLOT(00) W3D_VOID_SLOT(01) W3D_VOID_SLOT(02)
	W3D_VOID_SLOT(03) W3D_VOID_SLOT(04) W3D_VOID_SLOT(05)
	W3D_VOID_SLOT(06) W3D_VOID_SLOT(07) W3D_VOID_SLOT(08)
	W3D_VOID_SLOT(09) W3D_VOID_SLOT(10)
	virtual unsigned int slot2c(void);
	virtual unsigned int slot30(void);
	W3D_VOID_SLOT(34) W3D_VOID_SLOT(38) W3D_VOID_SLOT(3c)
	W3D_VOID_SLOT(40) W3D_VOID_SLOT(44) W3D_VOID_SLOT(48)
	W3D_VOID_SLOT(4c) W3D_VOID_SLOT(50) W3D_VOID_SLOT(54)
	W3D_VOID_SLOT(58) W3D_VOID_SLOT(5c) W3D_VOID_SLOT(60)
	W3D_VOID_SLOT(64) W3D_VOID_SLOT(68) W3D_VOID_SLOT(6c)
	W3D_VOID_SLOT(70)
	virtual CameraClass *getFirstView(void);
	virtual void slot78(void);
	virtual void drawViews(void);
	virtual void updateViews(void);
	W3D_VOID_SLOT(84) W3D_VOID_SLOT(88) W3D_VOID_SLOT(8c)
	W3D_VOID_SLOT(90) W3D_VOID_SLOT(94) W3D_VOID_SLOT(98)
	W3D_VOID_SLOT(9c) W3D_VOID_SLOT(a0) W3D_VOID_SLOT(a4)
	W3D_VOID_SLOT(a8) W3D_VOID_SLOT(ac) W3D_VOID_SLOT(b0)
	W3D_VOID_SLOT(b4) W3D_VOID_SLOT(b8) W3D_VOID_SLOT(bc)
	W3D_VOID_SLOT(c0) W3D_VOID_SLOT(c4) W3D_VOID_SLOT(c8)
	W3D_VOID_SLOT(cc) W3D_VOID_SLOT(d0) W3D_VOID_SLOT(d4)
	W3D_VOID_SLOT(d8) W3D_VOID_SLOT(dc)
	virtual void slotE0(int value);
	W3D_VOID_SLOT(e4) W3D_VOID_SLOT(e8) W3D_VOID_SLOT(ec)
	W3D_VOID_SLOT(f0) W3D_VOID_SLOT(f4) W3D_VOID_SLOT(f8)
	W3D_VOID_SLOT(fc) W3D_VOID_SLOT(100) W3D_VOID_SLOT(104)
	W3D_VOID_SLOT(108) W3D_VOID_SLOT(10c) W3D_VOID_SLOT(110)
	W3D_VOID_SLOT(114) W3D_VOID_SLOT(118) W3D_VOID_SLOT(11c)
	W3D_VOID_SLOT(120) W3D_VOID_SLOT(124) W3D_VOID_SLOT(128)
	W3D_VOID_SLOT(12c) W3D_VOID_SLOT(130) W3D_VOID_SLOT(134)
	W3D_VOID_SLOT(138) W3D_VOID_SLOT(13c) W3D_VOID_SLOT(140)
	W3D_VOID_SLOT(144) W3D_VOID_SLOT(148) W3D_VOID_SLOT(14c)
	W3D_VOID_SLOT(150) W3D_VOID_SLOT(154) W3D_VOID_SLOT(158)
	W3D_VOID_SLOT(15c) W3D_VOID_SLOT(160) W3D_VOID_SLOT(164)
	virtual void slot168(void);

	char m_pad04[0x28];
	void *m_callback2c;
	char m_pad30[4];
	Rva006EB500Sub *m_field34;
	char m_pad38[0x98];
	float m_letterBoxFadeLevel;
	char m_padd4[0x24];
	int m_fieldf8;
	int m_fieldfc;
	int m_field100;
	int m_field104;
	char m_pad108[0x34];
	UnsignedByte m_field13c;
	char m_pad13d[0x43];
	Rva006EB500Node *m_field180;

	void renderLetterBox(UnsignedInt currentTime);
	bool rva006EB500(UnsignedInt currentTime);
	void rva0002126a(void);
	void rva0003fa80(void);
	void rva0004b592(void);
};
#undef W3D_VOID_SLOT

class W3DDisplayRadarResetGuard
{
public:
	W3DDisplayRadarResetGuard(void) { W3DRadarResetLock(); }
	~W3DDisplayRadarResetGuard(void) { bfmeUnlock1179(); }
};

#pragma comment(linker, "/alternatename:?rva4a0de@Rva00367E30Logic@@QAE_NXZ=?j_0004a0de@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva22c96@Rva00367E30Logic@@QAE_NXZ=?j_00022c96@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0000bb81@Glo012F1028Type@@QAE_NXZ=?j_0000bb81@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0003f23d@ScriptEngine@@QAE_NXZ=?j_0003f23d@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00003783@ScriptEngine@@QAE_NXZ=?j_00003783@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00027318@ScriptEngine@@QAE_NXZ=?j_00027318@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva1f8f2@InGameUI@@QAEXXZ=?j_0001f8f2@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0002126a@W3DDisplay@@QAEXXZ=?j_0002126a@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0003fa80@W3DDisplay@@QAEXXZ=?j_0003fa80@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0004b592@W3DDisplay@@QAEXXZ=?j_0004b592@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000371a0@Rva006EB500Node@@QAEXXZ=?j_000371a0@@YAXXZ")

bool W3DDisplay::rva006EB500(UnsignedInt currentTime)
{
	W3DDisplayRadarResetGuard guard;
	int renderTargetPolygons;
	int renderTargetVertices;
	bool fadeActive;
	UnsignedInt waterTransparency;
	CameraClass *primaryView;

	if (DX8Wrapper::D3DDevice != 0 &&
		DX8Wrapper::D3DDevice->TestCooperativeLevel() == 0)
	{
		if (TheBfmeGameLogic->m_renderFlag == 0)
		{
			updateViews();
			Rva00755C80();
		}
		TheParticleSystemManager->update();
	}

	Debug_Statistics::End_Statistics();
	renderTargetPolygons = Rva00937260Get();
	renderTargetVertices = Rva00937270Get();

	if (g_bfmeA1087 != 0 && g_bfmeA1087->m_terrainMap != 0)
	{
		primaryView = getFirstView();
		if (g_bfmeA1087->m_shroud != 0)
			g_bfmeA1087->m_shroud->render(
				*reinterpret_cast<CameraClass **>(reinterpret_cast<char *>(primaryView) + 0x104));
		if (g_bfmeA1087->m_taint != 0)
			g_bfmeA1087->m_taint->update(
				*reinterpret_cast<CameraClass **>(reinterpret_cast<char *>(primaryView) + 0x104));
	}

	if (TheWritableGlobalData->m_movieState != 0 ||
		TheWritableGlobalData->m_renderState != 0)
		goto finish_render;

	waterTransparency = *reinterpret_cast<UnsignedInt *>(&g_bfmeA1087->m_waterTransparency);
	if (WW3D::Begin_Render(true, true,
		*reinterpret_cast<const Vector3 *>(reinterpret_cast<const char *>(this) + 0x1c),
		*reinterpret_cast<float *>(&waterTransparency), 0) != WW3D_ERROR_OK)
		goto finish_render;

	if (TheWritableGlobalData->m_letterBoxState == 1)
	{
		TheWindowManager->m_renderLock = 1;
		TheInGameUI->slot1c();
		Rva00579160TheManager->slot1c();
		TheWindowManager->m_renderLock = -1;
		if (TheMouse != 0)
			TheMouse->slot1c();
		WW3D::End_Render(true);
		return true;
	}

	*reinterpret_cast<UnsignedByte *>(0x012BAA54) = 1;
	if (renderTargetPolygons == 0 && renderTargetVertices != 0)
	{
		Debug_Statistics::Record_DX8_Polys_And_Vertices(
			renderTargetPolygons, renderTargetVertices,
			*reinterpret_cast<const Debug_Statistics::ShaderClass *>(0x012D6E08));
	}

	fadeActive = m_letterBoxFadeLevel != BfmeZeroRange;
	if (m_field180 != 0 && m_field180->m_enabled != 0)
	{
		m_field180->rva000371a0();
		if (m_field180->m_state == 2)
			goto after_ui;

		TheWindowManager->m_renderLock = 1;
		TheInGameUI->slot1c();
		if (!fadeActive)
		{
			TheInGameUI->slot130();
			Rva00579160TheManager->slot1c();
			TheWindowManager->m_renderLock = 0;
		}
		goto after_transition;
	}

	drawViews();
	reinterpret_cast<BfmeThing923E *>(this)->bfmeGo923E(0, reinterpret_cast<void *>(2));
	reinterpret_cast<BfmeThing923E *>(this)->bfmeGo923E(1, reinterpret_cast<void *>(2));
	reinterpret_cast<BfmeThing923E *>(this)->bfmeGo923E(2, reinterpret_cast<void *>(2));
	if (m_field34 == 0)
	{
		rva0003fa80();
	}
	else
	{
		TheWindowManager->m_renderLock = 1;
		TheInGameUI->slot1c();
		if (!fadeActive)
		{
			TheInGameUI->slot130();
			Rva00579160TheManager->slot1c();
			TheWindowManager->m_renderLock = 0;
		}
		TheInGameUI->slot1c();
		TheWindowManager->m_renderLock = -1;
		TheInGameUI->rva1f8f2();
		if (TheMouse != 0)
			TheMouse->slot1c();
	}

	if (m_field34 != 0)
	{
		reinterpret_cast<BfmeThing923E *>(this)->bfmeGo923E(0, reinterpret_cast<void *>(1));
		reinterpret_cast<BfmeThing923E *>(this)->bfmeGo923E(1, reinterpret_cast<void *>(1));
		if (m_field34->m_data != 0)
		{
			int value = m_field34->slot3c(m_fieldf8, m_fieldfc, m_field100, m_field104, -1);
			slotE0(value);
			reinterpret_cast<BfmeThing923E *>(this)->bfmeGo923E(2, reinterpret_cast<void *>(1));
			rva0003fa80();
			rva0004b592();
			Rva0081D520Owner *owner =
				reinterpret_cast<Rva0081D520Owner *>(m_field34->m_data->m_field18);
			if (owner != 0)
			{
				float first = static_cast<float>(slot30());
				float second = static_cast<float>(slot2c());
				owner->broadcast(0, 0.0f, 0.0f, second, first);
			}
		}
	}

	renderLetterBox(waterTransparency);

	if (fadeActive)
	{
		TheInGameUI->slot130();
		if (TheInGameUI->slot154() != 0)
			goto finish_render;
	}
	else
	{
		if (TheInGameUI->slot154() != 0)
			goto finish_render;
		if (Glo012F1028->rva0000bb81())
			goto finish_render;
		if (!TheBfmeGameLogic->rva4a0de())
			goto finish_render;
		if (m_field13c != 0)
		{
			slot168();
			j_0001a4c9();
		}
		TheTransitionHandler->slot1c();
		if (m_callback2c != 0)
			rva0002126a();
	}

after_transition:
	WW3D::End_Render(true);

after_ui:
	if (*reinterpret_cast<UnsignedByte *>(0x012BAA54) != 0)
	{
		*reinterpret_cast<UnsignedByte *>(0x012BAA54) = 0;
		if (TheScriptEngine->rva0003f23d())
			goto failed;
		if (TheScriptEngine->rva00003783())
			goto failed;
		if (TheScriptEngine->rva00027318())
			goto failed;
		if (TheBfmeGameLogic->rva22c96())
			goto failed;
	}

	return true;

finish_render:
	if (*reinterpret_cast<UnsignedByte *>(0x012BAA54) != 0)
	{
		*reinterpret_cast<UnsignedByte *>(0x012BAA54) = 0;
		if (TheScriptEngine->rva0003f23d())
			goto failed;
		if (TheScriptEngine->rva00003783())
			goto failed;
		if (TheScriptEngine->rva00027318())
			goto failed;
		if (TheBfmeGameLogic->rva22c96())
			goto failed;
	}
	return true;

failed:
	return false;
}
