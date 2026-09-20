// ?Rva00941700_Method@Rva00941700Owner@@QAEXPAVFontCharsClass@@PBGPAG_N@Z
// partial score=0.99 date=2026-09-19
// cl: /DNDEBUG /MD /EHsc

void __cdecl operator delete[](void *) throw();
#include "../../Code/Libraries/Source/WWVegas/WWLib/vector.h"

// The caller at 0x00941C60 supplies the font, UTF-16 text, glyph storage, and
// a calculation-only flag.  The method name remains address-derived because
// no semantic declaration names this BFME helper.

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

struct FontCharsClassCharDataStruct
{
	unsigned short Value;
	short Width;
	short ExtraSpacing;
};

class FontCharsClass
{
public:
	const FontCharsClassCharDataStruct *Get_Char_Data(unsigned short character);

	__forceinline int Get_Char_Height() const
	{
		return char_height;
	}

private:
	char fields00[0x2c];
	int char_height;
};

enum WW3DFormat
{
	WW3D_FORMAT_008FC560 = 0x15
};

enum _D3DPOOL
{
	D3DPOOL_SYSTEMMEM = 2
};
typedef _D3DPOOL D3DPOOL;

class SurfaceClass : public W3DRadarResetSurface
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
};

template <>
bool DynamicVectorClass<Render2DSentenceClass::PendingSurfaceStruct>::Add(
	const Render2DSentenceClass::PendingSurfaceStruct &object);

class Rva00941700Owner
{
public:
	void Rva00941700_Method(FontCharsClass *font, const unsigned short *text,
		unsigned short *glyphs, bool justCalcExtents);

private:
	DynamicVectorClass<Render2DSentenceClass::SentenceDataStruct> sentence_data;
	char sentence_data_pad[4];
	DynamicVectorClass<Render2DSentenceClass::PendingSurfaceStruct> pending_surfaces;
	char renderers[0x18];
	char font_fields[0x04];
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

void Rva00941700Owner::Rva00941700_Method(
	FontCharsClass *font, const unsigned short *text,
	unsigned short *glyphs, bool justCalcExtents)
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
		const FontCharsClassCharDataStruct *data = font->Get_Char_Data(glyphs[index]);
		int char_width;
		if (data != 0) {
			int extra_spacing = data->ExtraSpacing;
			int width = data->Width;
			char_width = width + extra_spacing;
		}
		else
			char_width = 0;
		text_width += char_width;
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
