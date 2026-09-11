// ?d_009369a0@@YAXXZ
// partial score=0.38 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
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
		if ((unsigned)index < (unsigned)Count)
			return ((BfmeRenderVertex *)Data)[index];
		return *(BfmeRenderVertex *)Data;
	}

	BfmeRenderVertex *Data;
	int Size;
	int Count;
	int GrowthStep;
};

class Render2DIndexArray
{
public:
	unsigned short *Data;
	int Size;
	int Count;
	int GrowthStep;
};

class Rva00933C60
{
public:
	Rva00933C60 &operator=(Rva00933C60 const &other);

	__forceinline ~Rva00933C60()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	__forceinline void Initialize()
	{
		for (int i = 0; i < 7; ++i)
		{
			m_field20[i] = -1;
			m_field3C[i] = -1;
			m_field04[i] = -1;
			m_field58[i] = 0;
		}
	}

	TextureClass *m_texture;
	int m_field04[7];
	int m_field20[7];
	int m_field3C[7];
	int m_field58[7];
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

	__forceinline bool Add(T const &object, int count)
	{
		if (count >= Length())
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
	*baseVertexPair = ArrayA.Count | (ArrayA.Count << 16);

	if (CurrentBatch < 0)
	{
		if (IsDirty)
		{
			TextureClass *texture = Texture;
			if (texture)
			{
				unsigned int count = Batches.Count();
				int found = 1;
				if (count > 1)
				{
					for (; (unsigned int)found < (unsigned int)Batches.Count(); ++found)
					{
						if (Batches[found].m_texture == texture)
							break;
					}
				}

				if ((unsigned int)found == count)
				{
					if (texture)
						texture->Add_Ref();
					Rva00933C60 batch;
					batch.m_texture = texture;
					batch.Initialize();
					Batches.Add(batch, count);
				}
				CurrentBatch = found;
			}
		}
	}

	Rva00933C60 *batch = &Batches[
		(IsDirty && Texture) ? CurrentBatch : 0];
	BfmeRenderVertex *vertices =
		(BfmeRenderVertex *)ArrayA.Add((int)vertexCount);
	if (indexCount == 0 || indexCount >= 0x80000000u)
		return 0;

	ArrayB.Count += indexCount;
	unsigned short *indexPointer;
	if ((unsigned)ArrayB.Count > (unsigned)ArrayB.Size)
	{
		ArrayB.Size = ArrayB.Count + ArrayB.GrowthStep;
		ArrayB.Data = (unsigned short *)realloc(
			ArrayB.Data, (unsigned)ArrayB.Size * 2);
		indexPointer = (unsigned short *)ArrayB.Data;
		if (indexPointer)
			indexPointer += ArrayB.Count - indexCount;
	}
	else
	{
		indexPointer = (unsigned short *)ArrayB.Data +
			(ArrayB.Count - indexCount);
	}
	*indices = (BfmeUInt32 *)indexPointer;

	int mode = Shader;
	(reinterpret_cast<int *>(&batch->m_field58))[mode] += indexCount;
	int previous = (reinterpret_cast<int *>(&batch->m_field3C))[mode];
	if (previous >= 0)
	{
		if (ArrayA[previous].m_field14 +
			ArrayA[previous].m_field10 == ArrayB.Count)
		{
			ArrayA[previous].m_field14 += indexCount;
			return vertices;
		}
	}

	ArrayA[previous].m_field0C = ArrayA.Count - vertexCount;
	(reinterpret_cast<int *>(&batch->m_field04))[mode] =
		ArrayA.Count - vertexCount;
	(reinterpret_cast<int *>(&batch->m_field20))[mode] =
		ArrayB.Count - indexCount;
	vertices->m_field0C = 0;
	vertices->m_field10 = ArrayB.Count - indexCount;
	vertices->m_field14 = indexCount;
	(reinterpret_cast<int *>(&batch->m_field3C))[mode] =
		ArrayA.Count - vertexCount;
	return vertices;
}
