// ??0Gen006EF850@@QAE@XZ
// partial score=0.82 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob1 /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2
//
// Retail 0x006EF850 is the complete 753-byte default constructor for the
// 0x2A8 object allocated by make006FB520.  The factory's address-derived
// Gen006EF850 spelling is retained: its constructor installs the proven
// W3DDisplay vtable at 0x0111EDD0, but the existing W3DDisplay constructor
// thunk at 0x00002432 routes elsewhere and is not renamed here.
//
// The 0x006EF850 body calls the matched Display base constructor through ILT
// 0x0003198F, clears the three W3DDisplay scene globals, and initializes the
// two light arrays, Render2D pointer, clipping region, display-string arrays,
// and the renderer state tail.  The final allocation is the BFME pointer form
// of TextureCategoryList at 0x012F7FEC; the authentic dx8list/multilist ABI
// supplies its existing 0x006D18D0 constructor through ILT 0x0000A943.

typedef unsigned int UnsignedInt;

// Existing retail ILT rows: Display() and the texture-category list default
// constructor.  These are callee-owned, matched bodies rather than new
// wrappers or guessed aliases.
extern void j_0003198f(void);

// The retail new-expression calls the existing incremental-link thunk rather
// than inlining the authentic MultiListClass constructor.  This TU-local
// specialization keeps the observed 0x18-byte allocation while the additive
// pin below selects the matched constructor's ILT 0x0000A943 at this call site.
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

// The first scene pointer has a recovered symbol; the other two addresses
// are retained as raw static slots because their source-level names are not
// proven by this constructor.
class BfmeGlobPB;
class RTS2DScene;
class RTS3DInterfaceScene;
extern BfmeGlobPB *g_bfmeGlobPB;

#define RVA006EF850_PTR(type, address) (*reinterpret_cast<type **>(address))
#define RVA006EF850_DWORD(address) (*reinterpret_cast<UnsignedInt *>(address))

class Gen006EF850
{
public:
	Gen006EF850(void);

private:
	// This is an ABI view of the retail object, not a semantic replacement for
	// the generated class.  The observed stores establish every boundary below.
	unsigned char m_base[0x140];
	volatile unsigned char m_initialized;
	unsigned char m_pad141[3];
	void *m_myLight[4];
	void *m_secondLight[4];
	void * volatile m_2DRender;
	UnsignedInt m_clipRegion[4];
	volatile unsigned char m_isClippedEnabled;
	unsigned char m_pad179[3];
	volatile float m_averageFPS;
	void * volatile m_nativeDebugDisplay;
	void * volatile m_field184;
	void * volatile m_field188;
	void *m_displayStrings0[15];
	void *m_displayStrings1[25];
	void *m_displayStrings2[17];
	void * volatile m_field270;
	void * volatile m_field274;
	volatile UnsignedInt m_field278;
	volatile UnsignedInt m_field27c;
	void * volatile m_field280;
	volatile float m_field284;
	volatile float m_field288;
	volatile float m_field28c;
	volatile float m_field290;
	volatile float m_field294;
	volatile float m_field298;
	volatile UnsignedInt m_field29c;
	volatile UnsignedInt m_field2a0;
	volatile UnsignedInt m_field2a4;
};

typedef char Rva006EF850SizeCheck[(sizeof(Gen006EF850) == 0x2A8) ? 1 : -1];

// ??0Gen006EF850@@QAE@XZ
Gen006EF850::Gen006EF850(void)
{
	// The retail call enters the Display base with this in ECX.  This TU-local
	// class has no emitted vftable, so the inherited base call is stated through
	// the already matched ILT and the retail table is installed explicitly below.
	j_0003198f();
	*reinterpret_cast<volatile UnsignedInt *>(this) = 0x0111EDD0;

	m_nativeDebugDisplay = 0;
	m_field290 = 1.0f;
	m_field294 = 1.0f;
	m_field298 = 1.0f;
	m_field284 = 1.0f;
	m_field288 = 1.0f;
	m_field28c = 1.0f;
	m_field27c = 0;
	m_field278 = 1;
	m_field280 = 0;
	m_field29c = 0;
	m_field2a0 = 0;
	m_field2a4 = 0;
	m_field184 = 0;
	m_field188 = 0;
	m_initialized = 0;

	g_bfmeGlobPB = 0;
	RVA006EF850_DWORD(0x012F805C) = 0;
	RVA006EF850_DWORD(0x012F8060) = 0;

	m_averageFPS = (float)TheWritableGlobalData->m_framesPerSecondLimit;

	for (int i = 0; i < 4; ++i) {
		m_myLight[i] = 0;
		m_secondLight[i] = 0;
	}
	m_2DRender = 0;
	m_isClippedEnabled = 0;
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
	TextureCategoryList *textureCategories = new TextureCategoryList;
	RVA006EF850_PTR(TextureCategoryList, 0x012F7FEC) =
		textureCategories;

	// The retail constructor repeats this state after the list allocation.
	m_field290 = 1.0f;
	m_field294 = 1.0f;
	m_field298 = 1.0f;
	m_field284 = 1.0f;
	m_field288 = 1.0f;
	m_field28c = 1.0f;
	m_field27c = 0;
	m_field280 = 0;
	m_field278 = 1;
}
