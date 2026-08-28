// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Release_Ref();
};

class TextureClass : public TextureBaseClass {};

template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/ref_ptr.h
class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	~RefCountPtr()
	{
		if (Referent) {
			Referent->Release_Ref();
			Referent = 0;
		}
	}

	void Clear()
	{
		if (Referent) {
			Referent->Release_Ref();
			Referent = 0;
		}
	}

private:
	T * Referent;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/shader.h
class ShaderClass
{
public:
	ShaderClass() { Reset(); }
	ShaderClass(const ShaderClass & that) { ShaderBits = that.ShaderBits; }
	ShaderClass(unsigned int bits) : ShaderBits(bits) {}

private:
	void Set(unsigned int mask, unsigned int value)
	{
		ShaderBits &= ~mask;
		ShaderBits |= value;
	}

	void Reset()
	{
		ShaderBits = 0;
		Set(0x00000007, 0x00000003);
		Set(0x00000008, 0x00000008);
		Set(0x00000010, 0x00000010);
		Set(0x000000E0, 0);
		Set(0x00000300, 0);
		Set(0x00001C00, 0x00000400);
		Set(0x00002000, 0);
		Set(0x0000C000, 0x00004000);
		Set(0x00010000, 0);
		Set(0x00020000, 0);
		Set(0x000C0000, 0);
		Set(0x00100000, 0x00100000);
		Set(0x01E00000, 0);
		Set(0x0E000000, 0);
	}

	unsigned int ShaderBits;
};

class MeshMatDescClass
{
public:
	MeshMatDescClass(const MeshMatDescClass & that);
	MeshMatDescClass & operator =(const MeshMatDescClass & that);

private:
	enum {
		MAX_PASSES = 4,
		MAX_TEX_STAGES = 2,
		MAX_UV_ARRAYS = MAX_PASSES * MAX_TEX_STAGES
	};

	int PassCount;
	int VertexCount;
	int PolyCount;
	void * UV[MAX_UV_ARRAYS];
	int UVSource[MAX_PASSES][MAX_TEX_STAGES];
	void * ColorArray[2];
	int DCGSource[MAX_PASSES];
	int DIGSource[MAX_PASSES];
	RefCountPtr<TextureClass> Texture[MAX_PASSES][MAX_TEX_STAGES];
	ShaderClass Shader[MAX_PASSES];
	void * Material[MAX_PASSES];
	void * TextureArray[MAX_PASSES][MAX_TEX_STAGES];
	void * MaterialArray[MAX_PASSES];
	void * ShaderArray[MAX_PASSES];
};

MeshMatDescClass::MeshMatDescClass(const MeshMatDescClass & that) :
	PassCount(1),
	VertexCount(0),
	PolyCount(0)
{
	int pass;
	int stage;
	int array;

	for (array = 0; array < 2; array++) {
		ColorArray[array] = 0;
	}
	for (array = 0; array < MAX_UV_ARRAYS; array++) {
		UV[array] = 0;
	}

	for (pass = 0; pass < MAX_PASSES; pass++) {
		for (stage = 0; stage < MAX_TEX_STAGES; stage++) {
			UVSource[pass][stage] = -1;
			Texture[pass][stage].Clear();
			TextureArray[pass][stage] = 0;
		}
		DCGSource[pass] = 0;
		DIGSource[pass] = 0;
		Shader[pass] = 0;
		Material[pass] = 0;
		ShaderArray[pass] = 0;
		MaterialArray[pass] = 0;
	}

	*this = that;
}
