// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME's Render2D layout predates the later vendored class. Keep the retail
// layout and its 0x74-byte batch element local to this translation unit.

class ShaderState
{
public:
	ShaderState() : Value(2) {}
	int Value;
};

class Vector2
{
public:
	Vector2(float x, float y) : X(x), Y(y) {}
	float X;
	float Y;
};

class Render2DRawArray
{
public:
	Render2DRawArray() : Data(0), Size(0), Count(0), GrowthStep(16) {}
	~Render2DRawArray();

	void *Data;
	int Size;
	int Count;
	int GrowthStep;
};

// The batch element is 0x74 bytes, and its constructor (0x00933A40) only nulls a
// released pointer at +0. That rules out Zero Hour's 0x34-byte ProxyClass, which
// opens with a StringClass. Its real type is unknown, so it is named by its
// vector's vtable.
class Rva0113C8ACElem;

template<class T>
class VectorClass
{
public:
	VectorClass(int size = 0, T const *array = 0);
	virtual ~VectorClass();
	virtual bool operator==(VectorClass const &) const;
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *);
	virtual int ID(T const &);

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template<class T>
class DynamicVectorClass : public VectorClass<T>
{
public:
	DynamicVectorClass(int size = 0, T const *array = 0);
	virtual ~DynamicVectorClass() {}
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *);
	virtual int ID(T const &);

protected:
	int ActiveCount;
	int GrowthStep;
};

template<class T>
DynamicVectorClass<T>::DynamicVectorClass(int size, T const *array) :
	VectorClass<T>(size, array)
{
	GrowthStep = 10;
	ActiveCount = 0;
}
// ??0?$DynamicVectorClass@VRva0113C8ACElem@@@@QAE@HPBVRva0113C8ACElem@@@Z
// Retail 0x00936D00 is the batch-vector constructor: it forwards (size,
// array) to the VectorClass base at 0x00933D30, seats vtable 0x0113C8AC,
// then stores GrowthStep = 10 at this+0x14 and ActiveCount = 0 at
// this+0x10 before returning this. The Render2DClass constructor below
// calls it for the Batches member.
template DynamicVectorClass<Rva0113C8ACElem>::DynamicVectorClass(int, Rva0113C8ACElem const *);

class TextureRef
{
public:
	TextureRef() : Pointer(0) {}
	~TextureRef();

	void *Pointer;
};

extern int g_bfmeFirstEB;
extern int g_bfmeSecondEB;
extern int g_bfmeThirdEB;
extern int g_bfmeFourthEB;
extern int g_bfmeFifthEB;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2d.h
class Render2DClass
{
public:
	Render2DClass();
	void Reset();

private:
	ShaderState Shader;
	Vector2 CoordinateScale;
	Vector2 CoordinateOffset;
	Render2DRawArray ArrayA;
	Render2DRawArray ArrayB;
	DynamicVectorClass<Rva0113C8ACElem> Batches;
	TextureRef Texture;
	int CurrentBatch;
	bool IsDirty;
	unsigned char tail[3];
};

Render2DClass::Render2DClass() :
	CoordinateScale(1.0f, 1.0f),
	CoordinateOffset(0.0f, 0.0f),
	CurrentBatch(-1),
	IsDirty(true)
{
	Reset();
	g_bfmeSecondEB = 0;
	g_bfmeFirstEB = 0;
	g_bfmeThirdEB = 7;
	g_bfmeFourthEB = 2;
	g_bfmeFifthEB = 5;
}
