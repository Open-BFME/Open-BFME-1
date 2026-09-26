// cl: /DNDEBUG /MD /EHsc

void __cdecl operator delete[](void *) throw();
#include "../WWLib/vector.h"

// Retail RVA 0x00941A00..0x00941C54 (597 bytes), complete RET 8 at +0x252.
// The owner and method names remain address-derived.  The font character-data
// helper uses the independently pinned Rva00941400 ABI.

class BfmeSurfaceResource
{
public:
	virtual void slot00();
	virtual unsigned long __stdcall AddRef();
	virtual unsigned long __stdcall Release();
};

class W3DRadarResetSurface
{
public:
	W3DRadarResetSurface() : m_surface(0) {}
	~W3DRadarResetSurface();

	W3DRadarResetSurface &operator=(const W3DRadarResetSurface &that)
	{
		if (that.m_surface)
			that.m_surface->AddRef();
		if (m_surface)
			m_surface->Release();
		m_surface = that.m_surface;
		return *this;
	}

	BfmeSurfaceResource *m_surface;
};

struct Rva00941400CharRecord
{
	unsigned short Value;
	short Width;
	short ExtraSpacing;
};

// The callsite sets ecx to this font object, pushes one WCHAR, and the body
// returns a character-record pointer with RET 4.  This name and ABI are
// already pinned independently by the matching font-spacing thunk.
class Rva00941400Font
{
public:
	const Rva00941400CharRecord *Get_Char_Data(unsigned short character);

	__forceinline int Get_Char_Height() const
	{
		return char_height;
	}

	__forceinline int Get_Char_Spacing(unsigned short character)
	{
		const Rva00941400CharRecord *data = Get_Char_Data(character);
		if (data != 0 && data->Width != 0) {
			if ((character >= 0x0e01 && character <= 0x0e3a)
				|| (character >= 0x0e3f && character <= 0x0e5b)) {
				return data->Width + data->ExtraSpacing;
			}
			return data->Width - pixel_overlap - char_overhang;
		}
		return 0;
	}

private:
	char fields00[0x2c];
	int char_height;
	char fields30[4];
	int char_overhang;
	int pixel_overlap;
};

enum WW3DFormat
{
	// The retail constructor receives 0x15; the semantic format name is
	// intentionally neutral pending an enum witness.
	WW3D_FORMAT_008FC560 = 0x15
};

enum _D3DPOOL
{
	D3DPOOL_SYSTEMMEM = 2
};
typedef _D3DPOOL D3DPOOL;

// SurfaceClass is the one-pointer native wrapper whose constructor writes
// the COM resource at offset zero.  Its implicit destructor invokes the
// native W3DRadarResetSurface base destructor for the temporary lifetime.
class SurfaceClass
	: public W3DRadarResetSurface
{
public:
	SurfaceClass(unsigned width, unsigned height, WW3DFormat format, D3DPOOL pool);
	void Unlock();
};

class Render2DClass;

class Render2DSentenceClass
{
public:
	struct SentenceDataStruct : public W3DRadarResetSurface
	{
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

	struct PendingSurfaceStruct : public W3DRadarResetSurface
	{
		DynamicVectorClass<Render2DClass *> Renderers;

		bool operator==(const PendingSurfaceStruct &) { return false; }
		bool operator!=(const PendingSurfaceStruct &) { return true; }
	};

	virtual void reset();
	private:
	void Allocate_New_Surface(const unsigned short *text, bool justCalcExtents);

	DynamicVectorClass<Render2DSentenceClass::SentenceDataStruct> sentence_data;
	DynamicVectorClass<Render2DSentenceClass::PendingSurfaceStruct> pending_surfaces;
	char renderers[0x18];
	Rva00941400Font *font;
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
	W3DRadarResetSurface cur_surface;
	char remaining_fields[0x30];
	unsigned short *locked_ptr;
};

// Keep the native PendingSurfaceStruct Add body out-of-line at its already
// matched address; the generic header definition is otherwise small enough
// for this TU to inline it into the caller.
template <>
bool DynamicVectorClass<Render2DSentenceClass::PendingSurfaceStruct>::Add(
	const Render2DSentenceClass::PendingSurfaceStruct &object);

typedef char rva00941a00_surface_wrapper_must_be_4[(sizeof(W3DRadarResetSurface) == 4) ? 1 : -1];
typedef char rva00941a00_pending_surface_must_be_1c[
	(sizeof(Render2DSentenceClass::PendingSurfaceStruct) == 0x1c) ? 1 : -1];
typedef char rva00941a00_pending_vector_must_be_18[
	(sizeof(DynamicVectorClass<Render2DSentenceClass::PendingSurfaceStruct>) == 0x18) ? 1 : -1];

void Render2DSentenceClass::Allocate_New_Surface(
	const unsigned short *text, bool justCalcExtents)
{
	if (!justCalcExtents)
	{
		if (locked_ptr != 0) {
			reinterpret_cast<SurfaceClass *>(&cur_surface)->Unlock();
			locked_ptr = 0;
		}
	}

	int text_width = 0;
	for (int index = 0; text[index] != 0; index++) {
		text_width += font->Get_Char_Spacing(text[index]);
	}

	int char_height = font->Get_Char_Height();

	current_texture_size = 256;
	int best_tex_mem_usage = 999999999;
	for (int pow2 = 6; pow2 <= 8; pow2++) {
		int size = 1 << pow2;
		int row_count = (text_width / size) + 1;
		int rows_per_texture = size / (char_height + 1);

		if (rows_per_texture > 0) {
			int texture_count = row_count / rows_per_texture;
			texture_count = max(texture_count, 1);
			int texture_mem_usage = texture_count * size * size;
			if (texture_mem_usage < best_tex_mem_usage) {
				current_texture_size = size;
				best_tex_mem_usage = texture_mem_usage;
			}
		}
	}

	current_texture_size = max(texture_size_hint, current_texture_size);

	if (!justCalcExtents)
	{
		if (cur_surface.m_surface) {
			cur_surface.m_surface->Release();
			cur_surface.m_surface = 0;
		}

		cur_surface = SurfaceClass(current_texture_size, current_texture_size,
			WW3D_FORMAT_008FC560, D3DPOOL_SYSTEMMEM);

		Render2DSentenceClass::PendingSurfaceStruct surface_info;
		static_cast<W3DRadarResetSurface &>(surface_info) = cur_surface;
		pending_surfaces.Add(surface_info);
	}

	texture_offset_i = 0;
	texture_offset_j = 0;
	texture_start_x = 0;
}
