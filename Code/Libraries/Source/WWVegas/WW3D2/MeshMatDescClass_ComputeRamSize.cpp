// Open-BFME: MeshMatDescClass::Compute_Ram_Size at retail RVA 0x00929BE0.
// MeshModelClass::Compute_Ram_Size at 0x0096C9B0 calls this body for both
// material descriptions, which identifies the generated placeholder.

class BfmeThingNH
{
public:
	virtual void Release_Virtual(void) = 0;

	int bfmeSizeNH(void);

	void Add_Ref(void)
	{
		++m_refs;
	}

	void Release_Ref(void)
	{
		if (--m_refs == 0) {
			Release_Virtual();
		}
	}

private:
	int m_refs;
};

template <class T>
class BfmeBuffer
{
public:
	T **Get_Array(void)
	{
		return m_array;
	}

	int Get_Count(void)
	{
		return m_count;
	}

	T *Get_Element(int index)
	{
		if (Get_Array()[index] != 0) {
			Get_Array()[index]->Add_Ref();
		}
		return Get_Array()[index];
	}

private:
	char m_prefix[8];
	T **m_array;
	char m_gap[4];
	int m_count;
};

class MeshMatDescClass
{
public:
	int Compute_Ram_Size(void);

private:
	int m_pass_count;
	int m_vertex_count;
	int m_poly_count;
	BfmeBuffer<unsigned> *m_uv[8];
	int m_uv_source[4][2];
	BfmeBuffer<unsigned> *m_color_array[2];
	int m_dcg_source[4];
	int m_dig_source[4];
	BfmeThingNH *m_texture[8];
	unsigned m_shader[4];
	BfmeThingNH *m_material[4];
	BfmeBuffer<BfmeThingNH> *m_texture_array[8];
	BfmeBuffer<BfmeThingNH> *m_material_array[4];
	BfmeBuffer<BfmeThingNH> *m_shader_array[4];
};

int MeshMatDescClass::Compute_Ram_Size(void)
{
	int size = 0xf4;
	const char *object = reinterpret_cast<const char *>(this);

#define ADD_SHARED_BUFFER_SIZE(offset, element_size) \
	do { \
		const char *buffer = *reinterpret_cast<const char * const *>(object + offset); \
		if (buffer != 0) { \
			size += *reinterpret_cast<const int *>(buffer + 0x10) * element_size; \
		} \
	} while (0)

	ADD_SHARED_BUFFER_SIZE(0x0c, 8);
	ADD_SHARED_BUFFER_SIZE(0x10, 8);
	ADD_SHARED_BUFFER_SIZE(0x14, 8);
	ADD_SHARED_BUFFER_SIZE(0x18, 8);
	ADD_SHARED_BUFFER_SIZE(0x1c, 8);
	ADD_SHARED_BUFFER_SIZE(0x20, 8);
	ADD_SHARED_BUFFER_SIZE(0x24, 8);
	ADD_SHARED_BUFFER_SIZE(0x28, 8);
	ADD_SHARED_BUFFER_SIZE(0x4c, 4);
	ADD_SHARED_BUFFER_SIZE(0x50, 4);

#undef ADD_SHARED_BUFFER_SIZE

	for (int pass = 0; pass < 4; ++pass) {
		if (m_material[pass] != 0) {
			size += m_material[pass]->bfmeSizeNH();
		}

		if (m_texture_array[pass * 2] != 0) {
			size += m_texture_array[pass * 2]->Get_Count() * 4;
		}

		if (m_texture_array[pass * 2 + 1] != 0) {
			size += m_texture_array[pass * 2 + 1]->Get_Count() * 4;
		}

		if (m_material_array[pass] != 0) {
			size += m_material_array[pass]->Get_Count() * 4;

			for (int index = 0; index < m_material_array[pass]->Get_Count(); ++index) {
				BfmeThingNH *material = m_material_array[pass]->Get_Element(index);
				if (material != 0) {
					size += material->bfmeSizeNH();
					material->Release_Ref();
				}
			}
		}

		if (m_shader_array[pass] != 0) {
			size += m_shader_array[pass]->Get_Count() * 4;
		}
	}

	return size;
}
