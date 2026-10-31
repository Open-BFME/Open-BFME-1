// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail RVA 0x009369A0, 773 bytes, RET 16: Render2DClass's batch allocator
// that the Add_Quad bodies reserve vertices and 16-bit indices through.
// Statement shape ported from the BFME 2 donor allocateGeometry006e in
// Code/Libraries/Source/WWVegas/WW3D2/Render2DClassReset.cpp (open-bfme-2
// b5a7b8290) onto BFME 1's older layout (the 0.38 bank's views): batches are
// a DynamicVectorClass of 0x74-byte Rva00933C60 records at +0x34, the raw
// vertex array's operator[] is bounds-checked, the index array grows through
// the imported realloc. Levers: Add() reads ActiveCount itself, the batch is
// built trivially and then takes the texture through a const& setter (retail
// sets the EH state before re-testing the handle), and the index array's Add
// is __forceinline.
// BFME Render2D uses a pre-vendored layout.  Keep this mirror local so the
// older retail offsets do not alter the shared Zero Hour declarations.

extern "C" __declspec(dllimport) void *__cdecl realloc(
	void *pointer, unsigned int bytes);

typedef unsigned long BfmeUInt32;

struct BfmeRenderVertex
{
	float x;
	float y;
	float z;
	int m_field0C;
	int m_field10;
	int m_field14;
	BfmeUInt32 color;
	float u;
	float v;
	unsigned char m_unmodelled_24[0x08];
};

struct Render2DPackedVert
{
	unsigned char bytes[0x2C];
};

class TextureClass
{
public:
	void Add_Ref() { ++RefCount; }
	void Release_Ref();

	int Unknown00;
	unsigned short RefCount;
	unsigned short Unknown06;
};

class Render2DRawArray
{
public:
	Render2DPackedVert *Add(int count);
	BfmeRenderVertex &operator[](int index)
	{
		if ((unsigned)index >= (unsigned)Count)
			return *(BfmeRenderVertex *)Data;
		return ((BfmeRenderVertex *)Data)[index];
	}

	BfmeRenderVertex *Data;
	int Size;
	int Count;
	int GrowthStep;
};

class Render2DIndexArray
{
public:
	__forceinline unsigned short *Add(unsigned int count)
	{
		if (count == 0 || count >= 0x80000000u)
			return 0;
		Count += count;
		if (Count <= Size)
			return Data + (Count - count);
		Size = Count + GrowthStep;
		Data = (unsigned short *)realloc(Data, Size * sizeof(unsigned short));
		if (Data == 0)
			return 0;
		return Data + (Count - count);
	}

	unsigned short *Data;
	unsigned int Size;
	unsigned int Count;
	int GrowthStep;
};

class Rva00933C60
{
public:
	Rva00933C60 &operator=(Rva00933C60 const &other);

	__forceinline void Set_Texture(TextureClass *const &texture)
	{
		if (texture)
			texture->Add_Ref();
		m_texture = texture;
	}

	__forceinline ~Rva00933C60()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	__forceinline void Initialize()
	{
		m_field20 = -1;
		m_field3C = -1;
		m_field04 = -1;
		m_field58 = 0;
		m_field24 = -1;
		m_field40 = -1;
		m_field08 = -1;
		m_field5C = 0;
		m_field28 = -1;
		m_field44 = -1;
		m_field0C = -1;
		m_field60 = 0;
		m_field2C = -1;
		m_field48 = -1;
		m_field10 = -1;
		m_field64 = 0;
		m_field30 = -1;
		m_field4C = -1;
		m_field14 = -1;
		m_field68 = 0;
		m_field34 = -1;
		m_field50 = -1;
		m_field18 = -1;
		m_field6C = 0;
		m_field38 = -1;
		m_field54 = -1;
		m_field1C = -1;
		m_field70 = 0;
	}

	TextureClass *m_texture;
	int m_field04;
	int m_field08;
	int m_field0C;
	int m_field10;
	int m_field14;
	int m_field18;
	int m_field1C;
	int m_field20;
	int m_field24;
	int m_field28;
	int m_field2C;
	int m_field30;
	int m_field34;
	int m_field38;
	int m_field3C;
	int m_field40;
	int m_field44;
	int m_field48;
	int m_field4C;
	int m_field50;
	int m_field54;
	int m_field58;
	int m_field5C;
	int m_field60;
	int m_field64;
	int m_field68;
	int m_field6C;
	int m_field70;
};

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

public:
	int Length() const { return VectorMax; }
	T &operator[](int index) { return Vector[index]; }
};

template<class T>
class DynamicVectorClass : public VectorClass<T>
{
public:
	DynamicVectorClass(int size = 0, T const *array = 0);
	virtual ~DynamicVectorClass();
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *);
	virtual int ID(T const &);

	__forceinline bool Add(T const &object)
	{
		if (ActiveCount >= Length())
		{
			if ((IsAllocated || !VectorMax) && GrowthStep > 0)
			{
				if (!Resize(Length() + GrowthStep))
					return false;
			}
			else
			{
				return false;
			}
		}
		(*this)[ActiveCount++] = object;
		return true;
	}

	int Count() const { return ActiveCount; }

protected:
	int ActiveCount;
	int GrowthStep;
};

class Render2DClass
{
private:
	int Shader;
	float CoordinateScale[2];
	float CoordinateOffset[2];
	Render2DRawArray ArrayA;
	Render2DIndexArray ArrayB;
	DynamicVectorClass<Rva00933C60> Batches;
	TextureClass *Texture;
	int CurrentBatch;
	bool IsDirty;
	unsigned char Tail[3];

	BfmeRenderVertex *allocateGeometry006e(
		unsigned int vertexCount,
		unsigned int indexCount,
		BfmeUInt32 **indices,
		BfmeUInt32 *baseVertexPair);
};

// ?allocateGeometry006e@Render2DClass@@AAEPAUBfmeRenderVertex@@IIPAPAKPAK@Z
BfmeRenderVertex *Render2DClass::allocateGeometry006e(
	unsigned int vertexCount,
	unsigned int indexCount,
	BfmeUInt32 **indices,
	BfmeUInt32 *baseVertexPair)
{
	*baseVertexPair = (ArrayA.Count << 16) | ArrayA.Count;
	if (CurrentBatch < 0 && IsDirty && Texture)
	{
		unsigned int i;
		for (i = 1; i < (unsigned int)Batches.Count(); ++i)
		{
			if (Batches[i].m_texture == Texture)
				break;
		}
		if (i == (unsigned int)Batches.Count())
		{
			Rva00933C60 batch;
			batch.Set_Texture(Texture);
			batch.Initialize();
			Batches.Add(batch);
		}
		CurrentBatch = i;
	}
	Rva00933C60 &batch = Batches[(IsDirty && Texture) ? CurrentBatch : 0];
	BfmeRenderVertex *vertices = (BfmeRenderVertex *)ArrayA.Add(vertexCount);
	*indices = (BfmeUInt32 *)ArrayB.Add(indexCount);
	(&batch.m_field58)[Shader] += indexCount;
	if ((&batch.m_field3C)[Shader] >= 0)
	{
		int last = (&batch.m_field3C)[Shader];
		if (ArrayA[last].m_field10 + ArrayA[last].m_field14 == ArrayB.Count)
		{
			ArrayA[last].m_field14 += indexCount;
			return vertices;
		}
		unsigned int count = ArrayA.Count;
		ArrayA[last].m_field0C = count - vertexCount;
	}
	else
	{
		(&batch.m_field04)[Shader] = ArrayA.Count - vertexCount;
		(&batch.m_field20)[Shader] = ArrayB.Count - indexCount;
	}
	vertices->m_field0C = 0;
	vertices->m_field10 = ArrayB.Count - indexCount;
	vertices->m_field14 = indexCount;
	(&batch.m_field3C)[Shader] = ArrayA.Count - vertexCount;
	return vertices;
}
