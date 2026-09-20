// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

#include "../WWLib/multilist.h"

class TextureClass
{
public:
	void Release_Ref();
};

class BfmeHandleCX
{
public:
	TextureClass *p;

	~BfmeHandleCX()
	{
		if (p)
			p->Release_Ref();
	}

	bool operator==(TextureClass *other) const
	{
		return p == other;
	}
};

class Gen_00945490
{
public:
	BfmeHandleCX bfmeGet(int index) const throw();
};

class VertexMaterialClass
{
	unsigned char padding[0x64];
	mutable unsigned long crc;
	mutable bool crc_dirty;
	unsigned long Compute_CRC() const;

public:
	unsigned long Get_CRC() const
	{
		if (crc_dirty) {
			crc = Compute_CRC();
			crc_dirty = false;
		}
		return crc;
	}
};

class ShaderClass
{
public:
	unsigned ShaderBits;

	ShaderClass(const ShaderClass &other) : ShaderBits(other.ShaderBits) {}

	bool operator==(const ShaderClass &other) const
	{
		return ShaderBits == other.ShaderBits;
	}
};

class Vertex_Split_Table;
class IndexBufferClass;
class DX8PolygonRendererClass;
class DX8FVFCategoryContainer;

class DX8TextureCategoryClass : public MultiListObjectClass
{
public:
	virtual ~DX8TextureCategoryClass();

	DX8TextureCategoryClass(
		DX8FVFCategoryContainer *container,
		TextureClass **textures,
		ShaderClass shader,
		VertexMaterialClass *material,
		int pass);

	unsigned Add_Mesh(
		Vertex_Split_Table &split_table,
		unsigned vertex_offset,
		unsigned index_offset,
		IndexBufferClass *index_buffer,
		unsigned pass);

	const VertexMaterialClass *Peek_Material() const
	{
		return material;
	}

	ShaderClass Get_Shader() const
	{
		return shader;
	}

private:
	int category_pass;
	TextureClass *textures[2];
	ShaderClass shader;
	VertexMaterialClass *material;
	MultiListClass<DX8PolygonRendererClass> polygon_renderer_list;
	DX8FVFCategoryContainer *container;
	void *render_task_head;
};

typedef MultiListClass<DX8TextureCategoryClass> TextureCategoryList;
typedef MultiListIterator<DX8TextureCategoryClass> TextureCategoryListIterator;

class DX8FVFCategoryContainer : public MultiListObjectClass
{
protected:
	TextureCategoryList texture_category_list[4];
	TextureCategoryList visible_texture_category_list[4];
	void *visible_matpass_head;
	void *visible_matpass_tail;
	IndexBufferClass *index_buffer;
	int used_indices;
	IndexBufferClass *unknown_D8;
	unsigned unknown_DC;
	unsigned FVF;
	unsigned passes;
	unsigned uv_coordinate_channels;
	bool sorting;
	bool anything_to_render;
	bool any_delayed_passes_to_render;

	void Insert_To_Texture_Category(
		Vertex_Split_Table &split_table,
		TextureClass **texs,
		VertexMaterialClass *mat,
		ShaderClass shader,
		int pass,
		unsigned vertex_offset);
};

inline bool Equal_Material(
	const VertexMaterialClass *left,
	const VertexMaterialClass *right)
{
	unsigned long left_crc = left ? left->Get_CRC() : 0;
	unsigned long right_crc = right ? right->Get_CRC() : 0;
	return left_crc == right_crc;
}

void DX8FVFCategoryContainer::Insert_To_Texture_Category(
	Vertex_Split_Table &split_table,
	TextureClass **texs,
	VertexMaterialClass *mat,
	ShaderClass shader,
	int pass,
	unsigned vertex_offset)
{
	bool fit_in_existing_category = false;
	TextureCategoryListIterator it(&texture_category_list[pass]);
	while (!it.Is_Done()) {
		DX8TextureCategoryClass *tex_category = it.Peek_Obj();
		bool all_textures_same = true;
		for (unsigned stage = 0; stage < 2; ++stage) {
			all_textures_same = all_textures_same &&
				(reinterpret_cast<const Gen_00945490 *>(tex_category)->bfmeGet(stage) == texs[stage]);
		}
		if (all_textures_same &&
			Equal_Material(tex_category->Peek_Material(), mat) &&
			tex_category->Get_Shader() == shader) {
			unknown_DC += tex_category->Add_Mesh(
				split_table, vertex_offset, unknown_DC, unknown_D8, pass);
			fit_in_existing_category = true;
			break;
		}
		it.Next();
	}

	if (!fit_in_existing_category) {
		DX8TextureCategoryClass *new_tex_category = new DX8TextureCategoryClass(
			this, texs, shader, mat, pass);
		unknown_DC += new_tex_category->Add_Mesh(
			split_table, vertex_offset, unknown_DC, unknown_D8, pass);

		bool found_similar_category = false;
		TextureCategoryListIterator category_it(&texture_category_list[pass]);
		while (!category_it.Is_Done()) {
			if (reinterpret_cast<const Gen_00945490 *>(category_it.Peek_Obj())->bfmeGet(0) == texs[0]) {
				texture_category_list[pass].Add_After(new_tex_category, category_it.Peek_Obj());
				found_similar_category = true;
				break;
			}
			category_it.Next();
		}

		if (!found_similar_category) {
			texture_category_list[pass].Add_Tail(new_tex_category);
		}
	}
}
