// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// DX8FVFCategoryContainer::Generate_Texture_Categories, retail 0x00948820 /
// 796 bytes (ret 8 at +0x319). The Zero Hour routine (dx8renderer.cpp): the
// 12000-entry index buffer (sorting or npatch-aware), then per pass a booking
// of texture/material/shader triples feeding the matched
// Insert_To_Texture_Category at 0x009485C0. BFME holds textures through the
// BfmeHandleCX handle, as the matched Change_Polygon_Renderer_* siblings do.

#include "../WWLib/multilist.h"

class TextureClass
{
public:
	void Add_Ref() { ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4); }
	void Release_Ref();
};

class BfmeHandleCX
{
public:
	TextureClass *p;
	BfmeHandleCX() : p(0) {}
	BfmeHandleCX(const BfmeHandleCX &other) : p(other.p) { if (p) p->Add_Ref(); }
	~BfmeHandleCX() { if (p) p->Release_Ref(); }
	BfmeHandleCX &operator=(const BfmeHandleCX &other)
	{
		if (other.p) other.p->Add_Ref();
		if (p) p->Release_Ref();
		p = other.p;
		return *this;
	}
};

class Gen_00945B20
{
public:
	BfmeHandleCX bfmeGet(int index, int pass, int stage) const;
};

class VertexMaterialClass;

class ShaderClass
{
public:
	unsigned ShaderBits;
	ShaderClass() : ShaderBits(0x0010441B) {}
	ShaderClass(const ShaderClass &other) : ShaderBits(other.ShaderBits) {}
};

class MeshMatDescClass
{
public:
	int PassCount;
	VertexMaterialClass *Peek_Material(int vidx, int pass) const;
	unsigned char pad004[0xa4 - 4];
	VertexMaterialClass *Material[4];			// +0xa4
	unsigned char padb4[0xd4 - 0xb4];
	void *MaterialArray[4];					// +0xd4
};

struct TriIndex { unsigned short I, J, K; };

class MeshGeometryClass
{
public:
	unsigned char pad00[0xc];
	TriIndex *Poly;						// +0x0c
};

class MeshModelClass
{
public:
	unsigned char pad00[0x2c];
	MeshGeometryClass *PolyArray;				// +0x2c
	unsigned char pad30[0x9c - 0x30];
	MeshMatDescClass *CurMatDesc;				// +0x9c
	int Get_Pass_Count() const { return CurMatDesc->PassCount; }
	bool Has_Material_Array(int pass) const { MeshMatDescClass *d = CurMatDesc; return d->MaterialArray[pass] != 0; }
	VertexMaterialClass *Peek_Material(int vidx, int pass) const { return CurMatDesc->Peek_Material(vidx, pass); }
	VertexMaterialClass *Peek_Single_Material(int pass) const { return CurMatDesc->Material[pass]; }
	TriIndex *Get_Polygon_Array() { return PolyArray->Poly; }
};

class Vertex_Split_Table
{
public:
	MeshModelClass *mmc;
	bool npatch_enable;
	unsigned polygon_count;

	unsigned Get_Polygon_Count() const { return polygon_count; }
	unsigned Get_Pass_Count() const { return mmc->Get_Pass_Count(); }
	VertexMaterialClass *Peek_Material(unsigned index, unsigned pass)
	{
		if (mmc->Has_Material_Array(pass))
			return mmc->Peek_Material(mmc->Get_Polygon_Array()[index].I, pass);
		return mmc->Peek_Single_Material(pass);
	}
	ShaderClass Peek_Shader(unsigned index, unsigned pass);
};

class IndexBufferClass
{
public:
	unsigned char opaque[0x18];
};
class DX8IndexBufferClass : public IndexBufferClass
{
public:
	enum UsageType { USAGE_DEFAULT = 0, USAGE_NPATCHES = 4 };
	DX8IndexBufferClass(unsigned index_count, UsageType usage);
};
class SortingIndexBufferClass : public IndexBufferClass
{
public:
	SortingIndexBufferClass(unsigned short index_count);
};

extern unsigned char *BfmeCurrentCaps;
extern unsigned NPatchesLevel;

const unsigned MAX_ADDED_TYPE_COUNT = 64;

struct Textures_Material_And_Shader_Booking_Struct
{
	BfmeHandleCX added_textures[2][MAX_ADDED_TYPE_COUNT];
	VertexMaterialClass *added_materials[MAX_ADDED_TYPE_COUNT];
	ShaderClass added_shaders[MAX_ADDED_TYPE_COUNT];
	unsigned added_type_count;

	Textures_Material_And_Shader_Booking_Struct() : added_type_count(0)
	{
		for (unsigned a = 0; a < MAX_ADDED_TYPE_COUNT; ++a)
			added_materials[a] = 0;
	}
	bool Add_Textures_Material_And_Shader(BfmeHandleCX *texs, VertexMaterialClass *mat, ShaderClass shd);
};

class DX8FVFCategoryContainer : public MultiListObjectClass
{
protected:
	MultiListClass<MultiListObjectClass> texture_category_list[4];
	MultiListClass<MultiListObjectClass> visible_texture_category_list[4];
	void *visible_matpass_head;
	void *visible_matpass_tail;
	void *unknown_D0;
	int unknown_D4;
	IndexBufferClass *index_buffer;				// +0xd8
	unsigned used_indices;
	unsigned FVF;
	unsigned passes;
	unsigned uv_coordinate_channels;
	bool sorting;						// +0xec
	bool AnythingToRender;
	bool AnyDelayedPassesToRender;

	void Insert_To_Texture_Category(Vertex_Split_Table &split_table, TextureClass **textures,
		VertexMaterialClass *mat, ShaderClass shader, int pass, unsigned vertex_offset);
	void Generate_Texture_Categories(Vertex_Split_Table &split_table, unsigned vertex_offset);
};

void DX8FVFCategoryContainer::Generate_Texture_Categories(Vertex_Split_Table &split_table, unsigned vertex_offset)
{
	int polygon_count = split_table.Get_Polygon_Count();
	int index_count = polygon_count * 3 * split_table.Get_Pass_Count();

	if (!index_buffer) {
		int ib_size = 12000;
		if (ib_size < index_count) ib_size = index_count;
		if (sorting) {
			index_buffer = new SortingIndexBufferClass(ib_size);
		} else {
			index_buffer = new DX8IndexBufferClass(ib_size,
				(BfmeCurrentCaps[0x13b] && NPatchesLevel > 1) ?
					DX8IndexBufferClass::USAGE_NPATCHES : DX8IndexBufferClass::USAGE_DEFAULT);
		}
	}

	for (unsigned pass = 0; pass < split_table.Get_Pass_Count(); ++pass) {
		Textures_Material_And_Shader_Booking_Struct textures_material_and_shader_booking;

		for (int i = 0; i < polygon_count; ++i) {
			BfmeHandleCX textures[2];
			for (int stage = 0; stage < 2; stage++) {
				textures[stage] = reinterpret_cast<const Gen_00945B20 *>(&split_table)->bfmeGet(i, pass, stage);
			}
			VertexMaterialClass *mat = split_table.Peek_Material(i, pass);
			ShaderClass tmp = split_table.Peek_Shader(i, pass);
			ShaderClass shader = tmp;
			if (!textures_material_and_shader_booking.Add_Textures_Material_And_Shader(textures, mat, shader)) continue;

			Insert_To_Texture_Category(split_table, reinterpret_cast<TextureClass **>(textures), mat, shader, pass, vertex_offset);
		}
	}
}
