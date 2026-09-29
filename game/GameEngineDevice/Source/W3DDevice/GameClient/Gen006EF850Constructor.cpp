// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Default constructor 0x006EF850 of the W3DDisplay-vtable object built by make006FB520.

#include <vector>

typedef unsigned int UnsignedInt;

// Callee 0x006D18D0 (ILT 0x0000A943) is the matched MultiListClass<DX8TextureCategoryClass> ctor.
class DX8TextureCategoryClass;
template <class T> class MultiListClass;
template <> class MultiListClass<DX8TextureCategoryClass>
{
public:
	MultiListClass(void);

private:
	unsigned char m_storage[0x18];
};

typedef MultiListClass<DX8TextureCategoryClass> TextureCategoryList;

class GlobalData
{
private:
	unsigned char m_padding00[0x24];

public:
	int m_framesPerSecondLimit;
};

extern GlobalData *TheWritableGlobalData;

class BfmeGlobPB;
class RTS2DScene;
class RTS3DInterfaceScene;
extern BfmeGlobPB *g_bfmeGlobPB;

// Declared as an object by camerashakesystem.cpp; BFME holds a pointer at its first dword.
class CameraShakeSystemClass;
extern CameraShakeSystemClass CameraShakerSystem;

#define RVA006EF850_PTR(type, address) (*reinterpret_cast<type **>(address))

// Display base: ctor 0x0040F260 (ILT 0x0003198F) and dtor 0x0040F6D0 install the same vtable.
class BfmeObjEE
{
public:
	BfmeObjEE(void);
	virtual ~BfmeObjEE(void);

protected:
	unsigned char m_base[0x140 - 0x004];
};

// Renderer state at +0x278; its inline reset runs in the ctor and again after the list allocation.
struct Rva006EF850RenderState
{
	// ??0Rva006EF850RenderState@@QAE@XZ absent-from-retail
	Rva006EF850RenderState(void) { reset(); }

	// ?reset@Rva006EF850RenderState@@QAEXXZ absent-from-retail
	void reset(void)
	{
		m_field290 = 1.0f;
		m_field294 = 1.0f;
		m_field298 = 1.0f;
		m_field284 = 1.0f;
		m_field288 = 1.0f;
		m_field28c = 1.0f;
		m_field27c = 0;
		m_field278 = 1;
		m_field280 = 0;
	}

	UnsignedInt m_field278;
	UnsignedInt m_field27c;
	void *m_field280;
	float m_field284;
	float m_field288;
	float m_field28c;
	float m_field290;
	float m_field294;
	float m_field298;
};

class Gen006EF850 : public BfmeObjEE
{
public:
	Gen006EF850(void);
	virtual ~Gen006EF850(void);

	static RTS2DScene *m_2DScene;
	static RTS3DInterfaceScene *m_3DInterfaceScene;

private:
	bool m_initialized;
	void *m_myLight[4];
	void *m_secondLight[4];
	void *m_2DRender;
	UnsignedInt m_clipRegion[4];
	bool m_isClippedEnabled;
	float m_averageFPS;
	void *m_nativeDebugDisplay;
	void *m_field184;
	void *m_field188;
	void *m_displayStrings0[15];
	void *m_displayStrings1[25];
	void *m_displayStrings2[17];
	void *m_field270;
	void *m_field274;
	Rva006EF850RenderState m_renderState;
	std::vector<int> m_textureCategories;
};

typedef char Rva006EF850SizeCheck[(sizeof(Gen006EF850) == 0x2A8) ? 1 : -1];

// ??0Gen006EF850@@QAE@XZ
Gen006EF850::Gen006EF850(void) :
	m_nativeDebugDisplay(0)
{
	m_field184 = 0;
	m_field188 = 0;
	m_initialized = false;

	g_bfmeGlobPB = 0;
	m_2DScene = 0;
	m_3DInterfaceScene = 0;

	m_averageFPS = (float)TheWritableGlobalData->m_framesPerSecondLimit;

	for (int i = 0; i < 4; ++i) {
		m_myLight[i] = 0;
		m_secondLight[i] = 0;
	}
	m_2DRender = 0;
	m_isClippedEnabled = false;
	for (int i = 0; i < 4; ++i)
		m_clipRegion[i] = 0;

	for (int i = 0; i < 15; ++i)
		m_displayStrings0[i] = 0;
	for (int i = 0; i < 25; ++i)
		m_displayStrings1[i] = 0;
	for (int i = 0; i < 17; ++i)
		m_displayStrings2[i] = 0;

	m_field270 = 0;
	m_field274 = 0;
	RVA006EF850_PTR(TextureCategoryList, &CameraShakerSystem) = new TextureCategoryList;

	m_renderState.reset();
}
