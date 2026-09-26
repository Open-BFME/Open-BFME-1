// ?d_00948820@@YAXXZ
// partial score=0.7 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep /Iinputs/toolchains/dx81/include

#include "dx8indexbuffer.h"
#include "dx8wrapper.h"
#include "meshmdl.h"
#include "meshmatdesc.h"
#include "shader.h"
#include "../WWLib/multilist.h"

class BfmeHandleCX
{
public:
	BfmeHandleCX(void) : p(0) {}

	BfmeHandleCX(const BfmeHandleCX &other) : p(other.p)
	{
		if (p)
			++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(p) + 4);
	}

	TextureClass *p;

	BfmeHandleCX &operator=(const BfmeHandleCX &other)
	{
		if (other.p)
			++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(other.p) + 4);
		if (p)
			p->Release_Ref();
		p = other.p;
		return *this;
	}

	~BfmeHandleCX(void)
	{
		if (p)
			p->Release_Ref();
	}
};

class Gen_00945B20
{
public:
	BfmeHandleCX bfmeGet(int index, int pass, int stage) const;
};

class VertexMaterialClass;

class Vertex_Split_Table
{
	MeshModelClass *mmc;
	bool npatch_enable;
	unsigned polygon_count;
	TriIndex *polygon_array;
	bool allocated_polygon_array;

public:
	unsigned Get_Polygon_Count(void) const
	{
		return polygon_count;
	}

	unsigned Get_Pass_Count(void) const
	{
		return mmc->Get_Pass_Count();
	}

	BfmeHandleCX Peek_Texture(unsigned index, unsigned pass, unsigned stage)
	{
		return reinterpret_cast<const Gen_00945B20 *>(this)->bfmeGet(index, pass, stage);
	}

	VertexMaterialClass *Peek_Material(unsigned index, unsigned pass)
	{
		MeshMatDescClass *desc = *reinterpret_cast<MeshMatDescClass **>(
			reinterpret_cast<char *>(mmc) + 0x9c);
		if (*reinterpret_cast<void **>(reinterpret_cast<char *>(desc) + 0xd4 + pass * 4)) {
			typedef unsigned short BfmeTriIndex[3];
			BfmeTriIndex *polygon_array = *reinterpret_cast<BfmeTriIndex **>(
				reinterpret_cast<char *>(*reinterpret_cast<void **>(
					reinterpret_cast<char *>(mmc) + 0x2c)) + 0xc);
			return desc->Peek_Material(polygon_array[index][0], pass);
		}
		return *reinterpret_cast<VertexMaterialClass **>(
			reinterpret_cast<char *>(desc) + 0xa4 + pass * 4);
	}

	ShaderClass Peek_Shader(unsigned index, unsigned pass);
};

class DX8FVFCategoryContainer;

typedef void (*Rva00945B80CellFunction)(void *);

extern void __stdcall rva00906340VecCtor(
	void *ptr,
	unsigned element_size,
	int count,
	Rva00945B80CellFunction ctor,
	Rva00945B80CellFunction dtor);
extern void rva00906340CellCtor(void *self);
extern void rva00906340CellDtor(void *self);
extern void __stdcall ArrayDeleteHelperBodyThunk(
	void *ptr,
	unsigned element_size,
	unsigned count,
	Rva00945B80CellFunction dtor);

const unsigned MAX_ADDED_TYPE_COUNT = 64;

struct BfmeHandleCXCell
{
	TextureClass *p;
};

struct Textures_Material_And_Shader_Booking_Struct
{
	BfmeHandleCXCell added_textures[2][MAX_ADDED_TYPE_COUNT];
	VertexMaterialClass *added_materials[MAX_ADDED_TYPE_COUNT];
	unsigned added_shader_bits[MAX_ADDED_TYPE_COUNT];
	unsigned added_type_count;

	__forceinline Textures_Material_And_Shader_Booking_Struct()
	{
		rva00906340VecCtor(
			added_textures,
			4,
			0x80,
			rva00906340CellCtor,
			rva00906340CellDtor);

		for (int index = 0; index < MAX_ADDED_TYPE_COUNT; ++index)
			added_shader_bits[index] = 0x0010441B;

		added_type_count = 0;

		for (int index = 0; index < MAX_ADDED_TYPE_COUNT; ++index)
			added_materials[index] = 0;
	}

	~Textures_Material_And_Shader_Booking_Struct()
	{
		ArrayDeleteHelperBodyThunk(
			added_textures,
			4,
			0x80,
			rva00906340CellDtor);
	}
	bool Add_Textures_Material_And_Shader(
		BfmeHandleCX *texs,
		VertexMaterialClass *mat,
		ShaderClass shader);
};

class DX8FVFCategoryContainer : public MultiListObjectClass
{
protected:
	MultiListClass<MultiListObjectClass> texture_category_list[4];
	MultiListClass<MultiListObjectClass> visible_texture_category_list[4];
	void *visible_matpass_head;
	void *visible_matpass_tail;
	IndexBufferClass *unused_D0;
	int unused_D4;
	IndexBufferClass *index_buffer;
	unsigned used_indices;
	unsigned FVF;
	unsigned passes;
	unsigned uv_coordinate_channels;
	bool sorting;
	bool anything_to_render;
	bool any_delayed_passes_to_render;

	void Insert_To_Texture_Category(
		Vertex_Split_Table &split_table,
		TextureClass **textures,
		VertexMaterialClass *mat,
		ShaderClass shader,
		int pass,
		unsigned vertex_offset);
	void Generate_Texture_Categories(Vertex_Split_Table &split_table, unsigned vertex_offset);
};

// ?Generate_Texture_Categories@DX8FVFCategoryContainer@@IAEXAAVVertex_Split_Table@@I@Z
void DX8FVFCategoryContainer::Generate_Texture_Categories(
	Vertex_Split_Table &split_table,
	unsigned vertex_offset)
{
	register int polygon_count = split_table.Get_Polygon_Count();
	int pass_count = split_table.Get_Pass_Count();
	int index_count = polygon_count * 3 * pass_count;

	if (!index_buffer) {
		int ib_size = 12000;
		if (ib_size < index_count)
			ib_size = index_count;
		if (sorting) {
			index_buffer = new SortingIndexBufferClass(ib_size);
		} else {
			index_buffer = new DX8IndexBufferClass(
				ib_size,
				(reinterpret_cast<const unsigned char *>(
					DX8Wrapper::Get_Current_Caps())[0x13b] &&
				 WW3D::Get_NPatches_Level() > 1) ?
					DX8IndexBufferClass::USAGE_NPATCHES :
					DX8IndexBufferClass::USAGE_DEFAULT);
		}
	}

	for (unsigned pass = 0; pass < split_table.Get_Pass_Count(); ++pass) {
		Textures_Material_And_Shader_Booking_Struct booking;

		for (int i = 0; i < polygon_count; ++i) {
			BfmeHandleCX textures[2];
			for (int stage = 0; stage < 2; ++stage) {
				textures[stage] = split_table.Peek_Texture(i, pass, stage);
			}
			VertexMaterialClass *mat = split_table.Peek_Material(i, pass);
			ShaderClass shader = split_table.Peek_Shader(i, pass);
			if (!booking.Add_Textures_Material_And_Shader(
				reinterpret_cast<BfmeHandleCX *>(textures), mat, shader))
				continue;

			Insert_To_Texture_Category(
				split_table,
				reinterpret_cast<TextureClass **>(textures),
				mat,
				shader,
				pass,
				vertex_offset);
		}
	}
}
