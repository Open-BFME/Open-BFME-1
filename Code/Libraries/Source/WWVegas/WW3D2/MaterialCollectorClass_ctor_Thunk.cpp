// cl: /DNDEBUG /MD /EHsc
// readable body of ??0MaterialCollectorClass@@QAE@XZ: Code/Libraries/Source/WWVegas/WW3D2/matinfo.cpp
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class ShaderVectorBaseCtorShim
{
public:
	void construct(int, int);
};

class TextureVectorBaseCtorShim
{
public:
	void construct(int, int);
};

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
{
public:
	__forceinline TextureVector()
	{
		((TextureVectorBaseCtorShim *)this)->construct(0, 0);
		*(unsigned int *)((unsigned char *)this + 0x10) = 0;
		*(unsigned int *)this = 0x0113c62c;
		*(unsigned int *)((unsigned char *)this + 0x14) = 10;
	}
	~TextureVector();

private:
	unsigned char m_data[0x18];
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
