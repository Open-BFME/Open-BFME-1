// cl: /DNDEBUG /MD /EHsc

#include "../WWLib/vector.h"

// Retail RVA 0x0093F310..0x0093F3F0 (224 bytes), complete RET at +0xDF.
// The rendering-family caller is named, but the native Record_Sentence_Chunk
// spelling remains a lead rather than an identity proof.  Keep this body
// address-derived until that identity is independently established.

class BfmeSurfaceResource
{
public:
	virtual void slot00();
	virtual unsigned long __stdcall AddRef();
	virtual unsigned long __stdcall Release();
};

// This is the already-matched one-pointer surface wrapper.  Its destructor
// is the existing 0x008FC5B0 body; the two virtual calls below deliberately
// use the COM ABI visible in retail: AddRef at vtable +4 and Release at +8,
// with the receiver pushed for each __stdcall call.
class W3DRadarResetSurface
{
public:
	W3DRadarResetSurface() : m_surface(0) {}
	~W3DRadarResetSurface();

	BfmeSurfaceResource *m_surface;
};

// The retail local and vector element are 36 bytes: one four-byte surface
// wrapper followed by eight four-byte geometry values.  The canonical nested
// spelling is intentional: DynamicVectorClass::Add below is the existing
// verified callee whose implementation is BfmeSentenceDataVector::Add.
class Render2DSentenceClass
{
public:
	struct SentenceDataStruct : public W3DRadarResetSurface
	{
		// Native record stubs, used by the existing vector implementation.
		bool operator==(const SentenceDataStruct &) { return false; }
		bool operator!=(const SentenceDataStruct &) { return true; }
		float screen_left;
		float screen_top;
		float screen_right;
		float screen_bottom;
		float uv_left;
		float uv_top;
		float uv_right;
		float uv_bottom;
	};
};

class Rva0093F310Font
{
public:
	int Get_Char_Height() const { return char_height; }

private:
	char pad[0x2c];
	int char_height;
};

class Rva0093F310Owner
{
public:
	virtual void reset();
	void Rva0093F310_Method();

private:
	DynamicVectorClass<Render2DSentenceClass::SentenceDataStruct> sentence_data;
	char pending_surfaces[0x18];
	char renderers[0x18];
	Rva0093F310Font *font;
	float base_location_x;
	float base_location_y;
	float location_x;
	float location_y;
	float cursor_x;
	float cursor_y;
	int texture_offset_i;
	int texture_offset_j;
	int texture_start_x;
	int current_texture_size;
	int texture_size_hint;
	BfmeSurfaceResource *cur_surface;
};

typedef char rva0093f310_surface_wrapper_must_be_4[(sizeof(W3DRadarResetSurface) == 4) ? 1 : -1];
typedef char rva0093f310_sentence_record_must_be_36[
	(sizeof(Render2DSentenceClass::SentenceDataStruct) == 36) ? 1 : -1];
typedef char rva0093f310_sentence_vector_must_be_24[
	(sizeof(DynamicVectorClass<Render2DSentenceClass::SentenceDataStruct>) == 24) ? 1 : -1];

void Rva0093F310Owner::Rva0093F310_Method()
{
	int width = texture_offset_i - texture_start_x;
	if (width > 0)
	{
		float char_height = font->Get_Char_Height();

		Render2DSentenceClass::SentenceDataStruct sentence_data;
		// Re-read cur_surface after each COM call: this is the retail reload
		// sequence, not a cached helper parameter.
		if (cur_surface)
			cur_surface->AddRef();
		if (sentence_data.m_surface)
			sentence_data.m_surface->Release();
		sentence_data.m_surface = cur_surface;
		sentence_data.screen_left = cursor_x;
		sentence_data.screen_right = cursor_x + width;
		sentence_data.screen_top = cursor_y;
		sentence_data.screen_bottom = cursor_y + char_height;
		sentence_data.uv_left = texture_start_x;
		sentence_data.uv_top = texture_offset_j;
		sentence_data.uv_right = texture_offset_i;
		sentence_data.uv_bottom = texture_offset_j + char_height;

		this->sentence_data.Add(sentence_data);
	}
}
