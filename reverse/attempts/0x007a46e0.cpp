// ??0WaterRenderObjClass@@QAE@XZ
// partial score=0.65 date=2026-09-09
// cl: /O2 /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// stlport

// Open-BFME5: WaterRenderObjClass::WaterRenderObjClass(void) at retail
// 0x007A46E0, 750 bytes. Counterpart of the already-matched destructor
// (WaterRenderObjDestructor.cpp, retail 0x0079EFD0) and the already-matched
// nested Setting destructor (WaterRenderSettingDestructor.cpp, retail
// 0x007A03F0). Layout evidence: the 9-state /EHsc unwind map (FuncInfo VA
// 0x12417a8) gives every destructible sub-object in declaration order --
// RenderObjClass base @+4, three BfmeHandleCX handles @+0xe4/+0x24c/+0x2a8
// (all sharing ??1BfmeHandleCX@@QAE@XZ), an inlined STL list sentinel
// @+0x2ac, a single AsciiString @+0x2c8, a 5-element UnicodeString array
// @+0x2cc (elements .set() from the global ?Rva01336E50Str@@3URva002E5FF0Str@@A
// string right after construction) and a 6-element WaterRenderObjClass::Setting
// array @+0x2e0 (cleanup reuses the already-matched ??1Setting dtor). The
// three vftable stores (own @+0, RenderObjClass override @+4, the
// MultiListObjectClass override folded into RenderObjClass's own multiple
// inheritance @+0xc) are compiler-generated and masked by verification --
// only the base/derivation shape (BfmeBaseVUQ, then RenderObjClass) matters.

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ() { }
};

// --- RenderObjClass, copied layout from
// Code/Libraries/Source/WWVegas/WW3D2/RenderObjClassCtor_Thunk.cpp (already
// matched ??0RenderObjClass@@QAE@XZ @0x9204B0) -- declaration only here, the
// constructor body is not redefined, just called through the pinned symbol.

class Vector3
{
public:
	float X, Y, Z;
};

class Vector4
{
public:
	float X, Y, Z, W;
};

class Matrix3D
{
public:
	Vector4 Row[3];
};

class SphereClass
{
public:
	Vector3 Center;
	float	Radius;
};

class AABoxClass
{
public:
	Vector3 Center;
	Vector3 Extent;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	virtual void Delete_This(void);

	int NumRefs;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass(void);

	void * ListNode;
};

class SceneClass;
class RenderHookClass;

class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
public:
	RenderObjClass(void);

	virtual int Class_ID(void) const;

	mutable unsigned long		Bits;					// +0x10
	unsigned long				_bfme_unk_14;			// +0x14
	Matrix3D					Transform;				// +0x18
	float						ObjectScale;			// +0x48
	unsigned int				ObjectColor;			// +0x4c
	mutable SphereClass			CachedBoundingSphere;	// +0x50
	mutable AABoxClass			CachedBoundingBox;	// +0x60
	float						NativeScreenSize;		// +0x78
	mutable bool				IsTransformIdentity;	// +0x7c
	SceneClass *				Scene;					// +0x80
	RenderObjClass *			Container;				// +0x84
	void *						User_Data;				// +0x88
	float						_bfme_unk_8c;			// +0x8c
	unsigned long				_bfme_unk_90;			// +0x90
	int							_bfme_unk_94;			// +0x94
	float						_bfme_unk_98;			// +0x98
	RenderHookClass *			RenderHook;				// +0x9c
	int							_bfme_unk_a0;			// +0xa0
	bool						_bfme_unk_a4;			// +0xa4
	char						_bfme_pad_a5[0x1f];		// +0xa5
	bool						_bfme_unk_c4;			// +0xc4
	char						_bfme_pad_c5[3];		// keeps sizeof at 0xc8
};

// Members touched by other Water* files, pointer-only here (never dereferenced
// by this constructor -- every one of them is just zero-initialised).
class WaterGridRef;
class WaterComRef;
class SkyBoxRenderObject;

// Shared handle wrapper: three separate instances of it live in
// WaterRenderObjClass (at +0xe4, +0x24c and +0x2a8), each zero-initialised
// inline (no ctor call -- the store folds into the flat zero run) but each
// individually destroyed on the /EHsc unwind path through the same already
// matched ??1BfmeHandleCX@@QAE@XZ (retail 0x00030652).
class BfmeHandleCX
{
public:
	BfmeHandleCX(void) : m_handle(0) { }
	~BfmeHandleCX(void);

private:
	void *m_handle;
};

#include <wchar.h>
#include "../../../../../../reference/shims/stringbaseunicode/Common/UnicodeString.h"
#include <list>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/ascii_string.h
// (already matched ??0BFMERetailAsciiString@@QAE@PBD@Z @0x888BC0 and
// ??1BFMERetailAsciiString@@QAE@XZ, both declared only here.)
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *s);
	~BFMERetailAsciiString(void);

private:
	void releaseBuffer();
	void *m_data;
};

// Retail 0x01336E50 -- already pinned under two other type tags
// (Rva0036CA00Str / Rva002E5FF0Str) by other converted bodies; this file
// reuses the same address as a real UnicodeString, matching the ?set@UnicodeString@@
// call retail makes with it as the argument.
extern UnicodeString Rva01336E50Str;

// Sub-object grouping to pin the store-scheduling boundary between a run of
// zero dwords and the following distinct float constant (see docs/lessons.md
// "MSVC regroups plain stores by feeding register").
struct ZeroQuad4
{
	ZeroQuad4(void) : a(0), b(0), c(0), d(0) { }
	unsigned long a, b, c, d;
};

class SkyBoxRenderObject;

struct ZeroBlock250
{
	ZeroBlock250(void) : d250(0), skyBox(0), d258(0), d25c(0), b260(0), b261(0) { }
	unsigned long d250;
	SkyBoxRenderObject *skyBox;
	unsigned long d258;
	unsigned long d25c;
	unsigned char b260;
	unsigned char b261;
};

// Single-member sub-object boundary: each instance is its own trivial ctor
// call, which pins its store as a hard sequence point the scheduler cannot
// merge into a neighbouring same-register run.
template <typename T>
struct Boxed
{
	Boxed(T v) : value(v) { }
	T value;
};

struct ZeroSix29c
{
	ZeroSix29c(void) : d284(0), d288(0), d28c(0), d290(0), d294(0), d298(0), f29c(10.0f) { }
	unsigned long d284, d288, d28c, d290, d294, d298;
	float f29c;
};

struct Pair128
{
	Pair128(int v) : a(v), b(v) { }
	int a, b;
};

class WaterRenderObjClass : public BfmeBaseVUQ, public RenderObjClass
{
public:
	// Open-BFME5: matched destructor, retail 0x007A03F0.
	struct Setting
	{
		Setting(void) : skyTexture(), waterTexture() { }
		~Setting(void);

		class TextureRefLocal
		{
		public:
			TextureRefLocal(void) : m_texture(0) { }
		private:
			void *m_texture;
		};

		TextureRefLocal skyTexture;		// +0x00
		TextureRefLocal waterTexture;		// +0x04
		unsigned char m_pad[0x30 - 8];		// +0x08 .. +0x30, untouched by this ctor
	};

	WaterRenderObjClass(void);

	WaterGridRef *				m_gridRef;			// +0xcc
	unsigned long				m_d0;				// +0xd0
	unsigned long				m_d4;				// +0xd4
	unsigned long				m_d8;				// +0xd8
	unsigned long				m_dc;				// +0xdc
	unsigned long				m_e0;				// +0xe0
	BfmeHandleCX				m_e4Handle;			// +0xe4
	ZeroQuad4					m_e8Block;			// +0xe8 .. +0xf8
	float						m_f8;				// +0xf8
	unsigned long				m_fc;				// +0xfc
	unsigned long				m_100;				// +0x100
	unsigned long				m_104;				// +0x104
	unsigned long				m_108;				// +0x108
	unsigned long				m_10c;				// +0x10c
	unsigned long				m_110;				// +0x110
	unsigned long				m_114;				// +0x114
	unsigned char				m_118;				// +0x118
	unsigned long				m_11c;				// +0x11c
	unsigned long				m_120;				// +0x120
	WaterComRef *				m_vertexBuffer;		// +0x124
	WaterComRef *				m_indexBuffer;		// +0x128
	unsigned long				m_12c;				// +0x12c
	WaterComRef *				m_bumpTexture0;		// +0x130
	WaterComRef *				m_bumpTexture1;		// +0x134
	WaterComRef *				m_bumpTexture2;		// +0x138
	unsigned long				m_13c;				// +0x13c
	unsigned long				m_140;				// +0x140
	unsigned char				m_zeroBlock1[0x100];	// +0x144 .. +0x244
	unsigned long				m_244;				// +0x244
	unsigned long				m_248;				// +0x248
	BfmeHandleCX				m_reflectionHandle;	// +0x24c
	ZeroBlock250				m_250Block;			// +0x250 .. +0x264
	Boxed<float>				m_264;				// +0x264
	Boxed<unsigned long>		m_268;				// +0x268
	Boxed<float>				m_26c;				// +0x26c
	Boxed<unsigned long>		m_270;				// +0x270
	Boxed<unsigned long>		m_274;				// +0x274
	Boxed<unsigned long>		m_278;				// +0x278
	Boxed<float>				m_27c;				// +0x27c
	Boxed<float>				m_280;				// +0x280
	ZeroSix29c					m_284Block;			// +0x284 .. +0x2a0
	Pair128						m_2a0Pair;			// +0x2a0 .. +0x2a8
	BfmeHandleCX				m_2a8Handle;		// +0x2a8
	_STL::list<UnicodeString>	m_at2ac;			// +0x2ac
	WaterComRef *				m_waterTexture0;	// +0x2b0
	WaterComRef *				m_waterTexture1;	// +0x2b4
	WaterComRef *				m_waterTexture2;	// +0x2b8
	unsigned long				m_2bc;				// +0x2bc
	unsigned long				m_2c0;				// +0x2c0
	unsigned char				m_2c4;				// +0x2c4
	unsigned char				m_2c5;				// +0x2c5
	BFMERetailAsciiString		m_sky;				// +0x2c8
	UnicodeString				m_names[5];			// +0x2cc
	Setting						m_settings[6];		// +0x2e0
	int							m_400;				// +0x400
	unsigned char				m_zeroBlock2[0x11c];	// +0x404 .. +0x520
};

// ??0WaterRenderObjClass@@QAE@XZ
WaterRenderObjClass::WaterRenderObjClass(void) :
	m_gridRef(0),
	m_d0(0),
	m_d4(0x10441b),
	m_d8(0), m_dc(0), m_e0(0),
	m_e4Handle(),
	m_e8Block(),
	m_f8(1.0f),
	m_fc(0), m_100(0), m_104(0), m_108(0), m_10c(0), m_110(0), m_114(0),
	m_118(0),
	m_11c(0), m_120(0),
	m_vertexBuffer(0), m_indexBuffer(0),
	m_12c(0),
	m_bumpTexture0(0), m_bumpTexture1(0), m_bumpTexture2(0),
	m_13c(0), m_140(0),
	m_zeroBlock1(),
	m_244(0), m_248(0),
	m_reflectionHandle(),
	m_250Block(),
	m_264(1.0f),
	m_268(0),
	m_26c(1.0f),
	m_270(0), m_274(0), m_278(0),
	m_27c(1280.0f), m_280(1280.0f),
	m_284Block(),
	m_2a0Pair(128),
	m_2a8Handle(),
	m_at2ac(),
	m_waterTexture0(0), m_waterTexture1(0), m_waterTexture2(0),
	m_2bc(0), m_2c0(0),
	m_2c4(0), m_2c5(0),
	m_sky("DefaultSky"),
	m_400(2),
	m_zeroBlock2()
{
	for (int i = 0; i < 5; i++)
		m_names[i].set(Rva01336E50Str);

	m_at2ac.clear();
}
