// Open-BFME: BFME's MeshMatDescClass reset with ref-counted texture slots.

class TextureBaseClass
{
public:
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
};

class InlineRefCounted
{
public:
	virtual void Delete_This() = 0;

	void Release_Ref()
	{
		if (--m_refs == 0)
			Delete_This();
	}

	int m_refs;
};

template <class T>
class RefCountPtr
{
public:
	void Clear()
	{
		if (m_referent != 0) {
			m_referent->Release_Ref();
			m_referent = 0;
		}
	}

private:
	T *m_referent;
};

class MeshMatDescClass
{
public:
	void Reset(int polycount, int vertcount, int passcount);

private:
	int m_pass_count;
	int m_vertex_count;
	int m_poly_count;
	InlineRefCounted *m_uv[8];
	int m_uv_source[4][2];
	InlineRefCounted *m_color_array[2];
	int m_dcg_source[4];
	int m_dig_source[4];
	RefCountPtr<TextureClass> m_texture[4][2];
	unsigned m_shader[4];
	InlineRefCounted *m_material[4];
	InlineRefCounted *m_texture_array[4][2];
	InlineRefCounted *m_material_array[4];
	InlineRefCounted *m_shader_array[4];
};

void MeshMatDescClass::Reset(int polycount, int vertcount, int passcount)
{
	m_poly_count = polycount;
	m_vertex_count = vertcount;
	m_pass_count = passcount;

	for (int array = 0; array < 2; ++array) {
		if (m_color_array[array] != 0) {
			m_color_array[array]->Release_Ref();
			m_color_array[array] = 0;
		}
	}

	for (int uv_array = 0; uv_array < 8; ++uv_array) {
		if (m_uv[uv_array] != 0) {
			m_uv[uv_array]->Release_Ref();
			m_uv[uv_array] = 0;
		}
	}

	for (int pass = 0; pass < 4; ++pass) {
		for (int stage = 0; stage < 2; ++stage) {
			m_uv_source[pass][stage] = -1;
			m_texture[pass][stage].Clear();
			if (m_texture_array[pass][stage] != 0) {
				m_texture_array[pass][stage]->Release_Ref();
				m_texture_array[pass][stage] = 0;
			}
		}

		m_dcg_source[pass] = 0;
		m_dig_source[pass] = 0;
		m_shader[pass] = 0;
		if (m_shader_array[pass] != 0) {
			m_shader_array[pass]->Release_Ref();
			m_shader_array[pass] = 0;
		}
		if (m_material[pass] != 0) {
			m_material[pass]->Release_Ref();
			m_material[pass] = 0;
		}
		if (m_material_array[pass] != 0) {
			m_material_array[pass]->Release_Ref();
			m_material_array[pass] = 0;
		}
	}
}
