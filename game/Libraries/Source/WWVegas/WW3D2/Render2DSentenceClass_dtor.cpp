// cl: /DNDEBUG /MD /EHsc
// ??1Render2DSentenceClass@@UAE@XZ, retail 0x009409F0 (334 bytes).
//
// BFME Render2DSentenceClass destructor. Identity evidence:
// - The body installs vtable 0x0113CEAC whose slot 0 is
//   ?Reset@Render2DSentenceClass@@UAEXXZ, then calls that Reset directly.
// - It destroys three 0x18-byte DynamicVectorClass members whose inline
//   teardown (element sizes 0x24/0x1C/8, vtables 0x0113CE0C/0x0113CE74/
//   0x0113CE24) matches the landed vector dtors 0x009409A0/0x00940810.
// - Callers are W3DDisplayString::~W3DDisplayString x2 (its m_textRenderer /
//   m_textRendererHotKey members), User and GameWindowHost member dtors.
// - The Word-perfect ZH dtor (REF_PTR_RELEASE(Font); Reset();) is the prefix
//   of this body; BFME adds a device-reset lock pair, a renderers Clear, a
//   texture-holder release and an embedded surface member.
// The ?releaseBuffer@UnicodeString@@IAEXXZ lift row that used to claim this
// address is a misnomer (the real wide-string release lives at 0x008881D0);
// this TU replaces it under the proven name.
//
// TU-local types mirror game/Libraries/Source/WWVegas/WW3D2/
// Render2DSentenceClass_ctor.cpp: zero includes, so nothing here can perturb
// another TU. Virtuals other than the destructor and Clear carry minimal
// bodies; the strong out-of-line definitions (parameter.cpp, mixfile.cpp,
// render2dsentence.cpp, TextureStatisticsVectorWide.cpp) win at link.

void operator delete[](void *block);

void W3DRadarResetLock();
char bfmeUnlock1179();

// REF_PTR_RELEASE, copied from WWLib/refcount.h (NULL spelled 0: identical
// codegen, keeps this TU include-free).
#define REF_PTR_RELEASE(x) { if (x) { x->Release_Ref(); x = 0; } }

// Minimal RefCountClass: vtable slot 0 is Delete_This, NumRefs sits at +0x04.
// Release_Ref inlines to dec/test/Delete_This; the virtual Delete_This call
// itself is never inlined, which is exactly the retail shape. Neither virtual
// is defined here and none is ever ODR-used, so this TU emits no symbols.
class RefCountClass
{
public:
	void Release_Ref() { m_refs--; if (m_refs == 0) { Delete_This(); } }
	virtual void Delete_This();

protected:
	virtual ~RefCountClass();

private:
	int m_refs;
};

class FontCharsClass : public RefCountClass
{
public:
	virtual ~FontCharsClass();
};

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();				// retail 0x008FC5B0

private:
	void *m_surface;
};

class TextureClass
{
public:
	void Release_Ref();						// retail 0x009EB7A0 (non-virtual)
};

// +0xB8 texture holder. Retail destroys it inline (new EH state, no null
// store after the Release_Ref call), so the destructor must be visible here.
// Only its shape is proven: a 4-byte holder releasing a TextureClass.
class TextureRefHolder009409F0
{
public:
	~TextureRefHolder009409F0()
	{
		if (m_texture != 0)
		{
			m_texture->Release_Ref();
		}
	}

private:
	TextureClass *m_texture;
};

// Sentence-data element. The 0x0113CE0C vector vtable names the instantiation
// VectorClassWide<TextureStatisticsStructWide>; retail destroys the elements
// through ILT 0x00018FCF, whose body (0x0005DBF0) is a bare tail jump to the
// W3DRadarResetSurface destructor, so the surface wrapper sits at +0x00 and
// the remaining 0x20 bytes hold no further reference-counted members.
struct TextureStatisticsStructWide
{
	~TextureStatisticsStructWide();			// retail ILT 0x00018FCF

	W3DRadarResetSurface m_surface;
	char m_pad[0x20];
};

class EnumParameterClass
{
public:
	// Renderer element. The 0x0113CE24 vector vtable names
	// VectorClass<ENUM_VALUE>, and retail destroys the 8-byte elements
	// through ILT 0x000470F5 (the pinned ??1_ENUM_VALUE dtor).
	struct ENUM_VALUE
	{
		~ENUM_VALUE();						// retail ILT 0x000470F5

		void *m_name;
		int m_value;
	};
};

template<class T>
class VectorClass
{
public:
	VectorClass(int size = 0, T const *array = 0);
	virtual ~VectorClass();
	virtual bool operator==(VectorClass const &other) const
		{ return VectorMax == other.VectorMax; }
	virtual bool Resize(int size, T const *array = 0) { return false; }
	virtual void Clear();
	virtual int ID(T const *ptr) { return 0; }
	virtual int ID(T const &object) { return 0; }

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template<class T>
VectorClass<T>::~VectorClass()
{
	VectorClass<T>::Clear();
}

template<class T>
void VectorClass<T>::Clear()
{
	if (Vector != 0 && IsAllocated)
	{
		delete [] Vector;
		Vector = 0;
	}
	IsAllocated = false;
	VectorMax = 0;
}

template<class T>
class DynamicVectorClass : public VectorClass<T>
{
public:
	DynamicVectorClass(int size = 0, T const *array = 0);

	virtual bool Resize(int size, T const *array = 0) { return false; }
	virtual void Clear() { ActiveCount = 0; VectorClass<T>::Clear(); }
	virtual int ID(T const *ptr) { return 0; }
	virtual int ID(T const &object) { return 0; }

protected:
	int ActiveCount;
	int GrowthStep;
};

template<class T>
class VectorClassWide
{
public:
	VectorClassWide(unsigned size, T const *array);
	virtual ~VectorClassWide();
	virtual bool operator==(VectorClassWide const &other) const
		{ return VectorMax == other.VectorMax; }
	virtual bool Resize(int size, T const *array = 0) { return false; }
	virtual void Clear();
	virtual int ID(T const *ptr) { return 0; }
	virtual int ID(T const &object) { return 0; }

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template<class T>
VectorClassWide<T>::~VectorClassWide()
{
	VectorClassWide<T>::Clear();
}

template<class T>
void VectorClassWide<T>::Clear()
{
	if (Vector != 0 && IsAllocated)
	{
		delete [] Vector;
		Vector = 0;
	}
	IsAllocated = false;
	VectorMax = 0;
}

template<class T>
class DynamicVectorClassWide : public VectorClassWide<T>
{
public:
	DynamicVectorClassWide(unsigned size = 0, T const *array = 0);

	virtual bool Resize(int size, T const *array = 0) { return false; }
	virtual void Clear() { ActiveCount = 0; VectorClassWide<T>::Clear(); }
	virtual int ID(T const *ptr) { return 0; }
	virtual int ID(T const &object) { return 0; }

protected:
	int ActiveCount;
	int GrowthStep;
};

class Render2DSentenceClass
{
public:
	struct PendingSurfaceStruct : public W3DRadarResetSurface
	{
		~PendingSurfaceStruct();				// retail 0x0045F5E0

		DynamicVectorClass<int> m_renderers;	// +0x04 (size filler: 0x18)
	};

	Render2DSentenceClass();
	virtual ~Render2DSentenceClass();
	virtual void Reset();						// retail 0x0093EA60

	DynamicVectorClassWide<TextureStatisticsStructWide> m_sentenceData;
	DynamicVectorClass<PendingSurfaceStruct> m_pendingSurfaces;
	DynamicVectorClass<EnumParameterClass::ENUM_VALUE> m_renderers;
	FontCharsClass *m_font;						// +0x4C
	float m_baseLocation[2];					// +0x50
	float m_location[2];						// +0x58
	float m_cursor[2];							// +0x60
	int m_textureOffset[2];						// +0x68
	int m_textureStartX;						// +0x70
	int m_currTextureSize;						// +0x74
	int m_textureSizeHint;						// +0x78
	W3DRadarResetSurface m_curSurface;			// +0x7C
	bool m_monoSpaced;							// +0x80
	char m_pad80[3];
	float m_wrapWidth;							// +0x84
	bool m_centered;							// +0x88
	char m_pad88[3];
	int m_clipRect[4];							// +0x8C
	int m_drawExtents[4];						// +0x9C
	bool m_clippingEnabled;						// +0xAC
	bool m_parseHotKey;							// +0xAD
	bool m_hardWordWrap;						// +0xAE
	char m_padAC;
	void *m_lockedPtr;							// +0xB0
	int m_lockedStride;							// +0xB4
	TextureRefHolder009409F0 m_curTexture;		// +0xB8
	int m_shader;								// +0xBC (POD tail)
};

// ??1Render2DSentenceClass@@UAE@XZ
Render2DSentenceClass::~Render2DSentenceClass()
{
	REF_PTR_RELEASE(m_font);
	W3DRadarResetLock();
	Render2DSentenceClass::Reset();
	m_renderers.Clear();
	bfmeUnlock1179();
}
