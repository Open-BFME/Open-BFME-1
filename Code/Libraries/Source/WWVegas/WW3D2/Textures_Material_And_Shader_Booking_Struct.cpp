// cl: /DNDEBUG /MD /EHsc

typedef void (*Rva00945B80CellFunction)(void *);

class TextureClass
{
public:
	void Add_Ref()
	{
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
	}

	void Release_Ref();
};

class BfmeHandleCX
{
public:
	TextureClass *p;

	BfmeHandleCX &operator=(const BfmeHandleCX &other)
	{
		if (other.p != 0)
			other.p->Add_Ref();
		if (p != 0)
			p->Release_Ref();
		p = other.p;
		return *this;
	}

	bool operator==(const BfmeHandleCX &other) const
	{
		return p == other.p;
	}
};

class VertexMaterialClass
{
	unsigned char pad[0x64];
	mutable unsigned long CRC;
	mutable bool CRCDirty;
	unsigned long Compute_CRC() const;

public:
	unsigned long Get_CRC() const
	{
		if (CRCDirty) {
			CRC = Compute_CRC();
			CRCDirty = false;
		}
		return CRC;
	}
};

class ShaderClass
{
public:
	unsigned long ShaderBits;

	bool operator==(const ShaderClass &other) const
	{
		return ShaderBits == other.ShaderBits;
	}
};

static bool Equal_Material(VertexMaterialClass *mat1, VertexMaterialClass *mat2)
{
	unsigned long crc0 = mat1 ? mat1->Get_CRC() : 0;
	unsigned long crc1 = mat2 ? mat2->Get_CRC() : 0;
	return crc0 == crc1;
}

extern void __stdcall rva00906340VecCtor(
	void *ptr,
	unsigned element_size,
	int count,
	Rva00945B80CellFunction ctor,
	Rva00945B80CellFunction dtor);
extern void rva00906340CellCtor(void *self);
extern void rva00906340CellDtor(void *self);

class Textures_Material_And_Shader_Booking_Struct
{
public:
	Textures_Material_And_Shader_Booking_Struct();
	bool Add_Textures_Material_And_Shader(
		BfmeHandleCX *texs,
		VertexMaterialClass *mat,
		ShaderClass shd);

private:
	BfmeHandleCX added_textures[2][0x40];
	VertexMaterialClass *added_materials[0x40];
	ShaderClass added_shaders[0x40];
	unsigned added_type_count;
};

Textures_Material_And_Shader_Booking_Struct::Textures_Material_And_Shader_Booking_Struct()
{
	rva00906340VecCtor(
		this,
		4,
		0x80,
		rva00906340CellCtor,
		rva00906340CellDtor);

	for (int index = 0; index < 0x40; ++index)
		added_shaders[index].ShaderBits = 0x0010441B;

    added_type_count = 0;

    for (int index = 0; index < 0x40; ++index)
        added_materials[index] = 0;
}

bool Textures_Material_And_Shader_Booking_Struct::Add_Textures_Material_And_Shader(
	BfmeHandleCX *texs,
	VertexMaterialClass *mat,
	ShaderClass shd)
{
	for (unsigned index = 0; index < added_type_count; ++index) {
		bool all_textures_same = true;
		for (unsigned stage = 0; stage < 2; ++stage) {
			all_textures_same =
				all_textures_same &&
				(texs[stage] == added_textures[stage][index]);
		}
		if (all_textures_same &&
			Equal_Material(mat, added_materials[index]) &&
			shd == added_shaders[index]) {
			return false;
		}
	}

	for (unsigned stage = 0; stage < 2; ++stage) {
		added_textures[stage][added_type_count] = texs[stage];
	}
	added_materials[added_type_count] = mat;
	added_shaders[added_type_count].ShaderBits = shd.ShaderBits;
	++added_type_count;
	return true;
}
