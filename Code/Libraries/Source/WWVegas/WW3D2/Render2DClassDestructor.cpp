// BFME's Render2DClass predates the virtual/layout changes in the vendored
// header.  This local declaration preserves its retail ownership layout.

#include <new.h>

extern void *__cdecl operator new[](size_t size);
extern void __cdecl operator delete[](void *pointer);
extern "C" __declspec(dllimport) void __cdecl free(void *pointer) throw();

class TextureBaseClass
{
public:
	void Release_Ref();
};

class ProxyClass
{
public:
	~ProxyClass();
	unsigned char Bytes[0x74];
};

class Render2DRawArray
{
public:
	~Render2DRawArray()
	{
		free(Data);
	}

	void *Data;
	unsigned char Rest[0x0c];
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
};

template<class T>
VectorClass<T>::~VectorClass()
{
	if (Vector && IsAllocated)
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
	virtual ~DynamicVectorClass() {}
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *);
	virtual int ID(T const &);

protected:
	int ActiveCount;
	int GrowthStep;
};

class Render2DClass
{
public:
	~Render2DClass();

private:
	int Shader;
	float CoordinateScale[2];
	float CoordinateOffset[2];
	Render2DRawArray ArrayA;
	Render2DRawArray ArrayB;
	DynamicVectorClass<ProxyClass> Batches;
	TextureBaseClass *Texture;
	int CurrentBatch;
	bool IsDirty;
	unsigned char Tail[3];
};

Render2DClass::~Render2DClass()
{
	if (Texture)
		Texture->Release_Ref();
}
