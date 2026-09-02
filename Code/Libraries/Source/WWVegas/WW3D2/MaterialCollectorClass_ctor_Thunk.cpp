// cl: /DNDEBUG /MD /EHsc
// readable body of ??0MaterialCollectorClass@@QAE@XZ: Code/Libraries/Source/WWVegas/WW3D2/matinfo.cpp
// Open-BFME5: lift MASM dump to standalone C++ thunk.

#include <new.h>

void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *pointer);

class ShaderVectorBaseCtorShim
{
public:
	void construct(int, int);
};

class TextureClass
{
public:
	void Release_Ref();
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	~RefCountPtr()
	{
		if (Referent != 0) {
			Referent->Release_Ref();
			Referent = 0;
		}
	}

private:
	T *Referent;
};

typedef RefCountPtr<TextureClass> TextureVectorCell;

class TextureVectorBaseCtorShim
{
public:
	__declspec(noinline) TextureVectorBaseCtorShim(int, TextureVectorCell const *);
	virtual ~TextureVectorBaseCtorShim();

private:
	TextureVectorCell *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

TextureVectorBaseCtorShim::TextureVectorBaseCtorShim(int size, TextureVectorCell const *array)
{
	*(unsigned int *)this = 0x0113c5fc;
	Vector = 0;
	VectorMax = size;
	IsValid = true;
	IsAllocated = false;

	if (size) {
		if (array) {
			Vector = new ((void *)(unsigned char *)array) TextureVectorCell[size];
		} else {
			Vector = new TextureVectorCell[size];
			IsAllocated = true;
		}
	}
}

class ShaderVector
{
public:
	__forceinline ShaderVector()
	{
		((ShaderVectorBaseCtorShim *)this)->construct(0, 0);
		*(unsigned int *)this = 0x0113c644;
		*(unsigned int *)((unsigned char *)this + 0x14) = 10;
		*(unsigned int *)((unsigned char *)this + 0x10) = 0;
	}
	~ShaderVector();

private:
	unsigned char m_data[0x18];
};

class MaterialVector
{
public:
	__forceinline MaterialVector()
	{
		unsigned char *self = (unsigned char *)this;
		*(unsigned int *)(self + 4) = 0;
		*(unsigned int *)(self + 8) = 0;
		*(unsigned char *)(self + 0x0c) = 1;
		*(unsigned char *)(self + 0x0d) = 0;
		*(unsigned int *)self = 0x0113c614;
		*(unsigned int *)(self + 0x14) = 10;
		*(unsigned int *)(self + 0x10) = 0;
	}
	~MaterialVector();

private:
	unsigned char m_data[0x18];
};

class TextureVector
	: public TextureVectorBaseCtorShim
{
public:
	__forceinline TextureVector()
		: TextureVectorBaseCtorShim(0, 0)
	{
		*(unsigned int *)((unsigned char *)this + 0x10) = 0;
		*(unsigned int *)this = 0x0113c62c;
		*(unsigned int *)((unsigned char *)this + 0x14) = 10;
	}
	~TextureVector();

private:
	unsigned char m_data[8];
};

class ShaderValue
{
public:
	__forceinline ShaderValue()
	{
		*(volatile unsigned int *)&m_value = 0x0010441b;
	}

	__forceinline ShaderValue &operator=(unsigned int value)
	{
		m_value = value;
		return *this;
	}

private:
	unsigned int m_value;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/matinfo.h
class MaterialCollectorClass
{
public:
	MaterialCollectorClass();

private:
	ShaderVector m_shaders;
	MaterialVector m_materials;
	TextureVector m_textures;
	ShaderValue LastShader;
	void *LastMaterial;
	void *LastTexture;
};

// ??0MaterialCollectorClass@@QAE@XZ
MaterialCollectorClass::MaterialCollectorClass()
{
	LastTexture = 0;
	LastMaterial = 0;
	LastShader = 0xffffffff;
}
