// cl: /DNDEBUG /MD /EHsc
// readable body of ?Draw_Sentence@Render2DSentenceClass@@: game/Libraries/Source/WWVegas/WW3D2/render2dsentence.cpp
// Retail RVA 0x0093EB50, 1983 bytes: the four-colour Render2DSentenceClass
// draw. Ported from the BFME 2 donor
// Code/Libraries/Source/WWVegas/WW3D2/Render2DSentenceDrawBFME2.cpp
// (open-bfme-2 b5a7b8290), itself the Zero Hour render2dsentence.cpp body plus
// the target-size scaling. BFME 1 facts from the retail body: TargetWidth and
// TargetHeight at +0xC4/+0xC8 against the defaults at +0xBC/+0xC0, DrawExtents
// at +0x9C, the 0x18-byte DynamicVectorClass members at +0x04/+0x1C/+0x34, the
// out-of-line RectClass::operator+= (0x0093C800), Add_Quad (ILT 0x0004183A)
// and the imported floor. The caller W3DGameWindowDrawText.cpp names the int
// spelling.
//
// Codegen: the RectClass union operator is the inline Zero Hour one; the
// inliner budget leaves the first (extent pre-pass) site out of line and
// inlines the second, as retail does. The screen rectangle is read into
// float locals, the height is a scalar computed before the Vector2 width,
// and the donor's block around the quad section keeps retail's frame slots.

void __cdecl operator delete[](void *) throw();
#include "../WWLib/vector.h"
#include <math.h>

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

class RectClass
{
public:
	RectClass() {}
	RectClass(const RectClass &r) { Left = r.Left; Top = r.Top; Right = r.Right; Bottom = r.Bottom; }
	RectClass(float left, float top, float right, float bottom) { Left = left; Top = top; Right = right; Bottom = bottom; }
	RectClass &operator=(const RectClass &r) { Left = r.Left; Top = r.Top; Right = r.Right; Bottom = r.Bottom; return *this; }
	void Set(float left, float top, float right, float bottom) { Left = left; Top = top; Right = right; Bottom = bottom; }
	float Width() const { return Right - Left; }
	float Height() const { return Bottom - Top; }
	RectClass &operator+=(const RectClass &r) { Left = MIN(Left, r.Left); Top = MIN(Top, r.Top); Right = MAX(Right, r.Right); Bottom = MAX(Bottom, r.Bottom); return *this; }
	RectClass &operator+=(const struct Vector2 &offset);
	float Left;
	float Top;
	float Right;
	float Bottom;
};

struct Vector2
{
	Vector2() {}
	Vector2(float x, float y) : X(x), Y(y) {}
	float X;
	float Y;
};

inline RectClass &RectClass::operator+=(const Vector2 &offset)
{
	Left += offset.X;
	Top += offset.Y;
	Right += offset.X;
	Bottom += offset.Y;
	return *this;
}


static inline float bfmeFloor(float value) { return (float)floor(value); }

class SurfaceClass
{
public:
	struct SurfaceDescription
	{
		unsigned Format;
		unsigned Width;
		unsigned Height;
	};

	virtual void __stdcall unused(void);
	virtual unsigned long __stdcall AddRef(void);
	virtual unsigned long __stdcall Release(void);
	void Get_Description(SurfaceDescription &description);
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

	SurfaceClass *m_surface;
};

class Render2DClass
{
public:
	Render2DClass();
	void Set_Coordinate_Range(const RectClass &range);
	void Add_Quad(const RectClass &screen, const RectClass &uv, unsigned long color1, unsigned long color2, unsigned long color3, unsigned long color4);

private:
	unsigned char m_unmodelled[0x58];
};

class DX8Wrapper
{
public:
	static unsigned int Get_Resolution_Width() { return ResolutionWidth; }
	static unsigned int Get_Resolution_Height() { return ResolutionHeight; }

protected:
	static int ResolutionWidth;
	static int ResolutionHeight;
};

class FontCharsClass;

class Render2DSentenceClass
{
public:
	struct SentenceDataStruct : public W3DRadarResetSurface
	{
		bool operator==(const SentenceDataStruct &) { return false; }
		bool operator!=(const SentenceDataStruct &) { return true; }
		RectClass ScreenRect, UVRect;
	};

	struct PendingSurfaceStruct : public W3DRadarResetSurface
	{
		DynamicVectorClass<int> rendererStorage;
		~PendingSurfaceStruct();

		bool operator==(const PendingSurfaceStruct &) { return false; }
		bool operator!=(const PendingSurfaceStruct &) { return true; }
	};

	struct RendererDataStruct
	{
		Render2DClass *Renderer;
		W3DRadarResetSurface Surface;
		bool operator==(const RendererDataStruct &) { return false; }
		bool operator!=(const RendererDataStruct &) { return true; }
	};

	virtual void Reset(void);
	void Draw_Sentence(int color1, int color2, int color3, int color4);

private:
	DynamicVectorClass<SentenceDataStruct> sentence_data;
	DynamicVectorClass<PendingSurfaceStruct> pending_surfaces;
	DynamicVectorClass<RendererDataStruct> renderers;
	FontCharsClass *font;
	float base_location_x;
	float base_location_y;
	Vector2 Location;
	float cursor_x;
	float cursor_y;
	int texture_offset_x;
	int texture_offset_y;
	int texture_start_x;
	int current_texture_size;
	int texture_size_hint;
	W3DRadarResetSurface cur_surface;
	char remaining_fields[0x0C];
	RectClass ClipRect, DrawExtents;
	bool IsClippedEnabled;
	char padAD[3];
	unsigned short *locked_ptr;
	int locked_stride;
	void *cur_texture;
	Vector2 DefaultScale;
	float TargetWidth, TargetHeight;
};

typedef char Rva0093EB50SentenceData[(sizeof(Render2DSentenceClass::SentenceDataStruct) == 0x24) ? 1 : -1];
typedef char Rva0093EB50Layout[(sizeof(Render2DSentenceClass) == 0xCC) ? 1 : -1];

void Render2DSentenceClass::Draw_Sentence(int color1, int color2, int color3, int color4)
{
	Render2DClass *curr_renderer = 0;
	W3DRadarResetSurface curr_surface;

	Vector2 scale = DefaultScale;
	DrawExtents.Set(0, 0, 0, 0);

	int index;
	if (TargetWidth > 0 && TargetHeight > 0)
	{
		for (index = 0; index < sentence_data.Count(); index++)
		{
			SentenceDataStruct &data = sentence_data[index];
			if (DrawExtents.Width() == 0)
				DrawExtents = data.ScreenRect;
			else
				DrawExtents += data.ScreenRect;
		}
		float width = DrawExtents.Width();
		if (width != 0)
			scale.X = TargetWidth / width;
		float height = DrawExtents.Height();
		if (height != 0)
			scale.Y = TargetHeight / height;
		DrawExtents.Set(0, 0, 0, 0);
	}

	for (index = 0; index < sentence_data.Count(); index++)
	{
		SentenceDataStruct &data = sentence_data[index];

		if (data.m_surface != curr_surface.m_surface)
		{
			curr_surface = data;

			bool found = false;
			for (int renderer_index = 0; renderer_index < renderers.Count(); renderer_index++)
			{
				if (renderers[renderer_index].Surface.m_surface == curr_surface.m_surface)
				{
					found = true;
					curr_renderer = renderers[renderer_index].Renderer;
					break;
				}
			}

			if (found == false)
			{
				curr_renderer = new Render2DClass;
				curr_renderer->Set_Coordinate_Range(RectClass(0, 0, (float)DX8Wrapper::Get_Resolution_Width(), (float)DX8Wrapper::Get_Resolution_Height()));

				RendererDataStruct render_info;
				render_info.Renderer = curr_renderer;
				render_info.Surface = curr_surface;
				renderers.Add(render_info);

				for (int surface_index = 0; surface_index < pending_surfaces.Count(); surface_index++)
				{
					PendingSurfaceStruct &surface_info = pending_surfaces[surface_index];
					if (surface_info.m_surface == curr_surface.m_surface)
						surface_info.rendererStorage.Add((int)curr_renderer);
				}
			}
		}

		{
		float left = data.ScreenRect.Left;
		float top = data.ScreenRect.Top;
		float right = data.ScreenRect.Right;
		float bottom = data.ScreenRect.Bottom;
		RectClass screen_rect;
		RectClass uv_rect = data.UVRect;
		Vector2 size;
		float height = bottom - top;
		size.X = right - left;
		screen_rect.Left = left * scale.X;
		screen_rect.Top = top * scale.Y;
		screen_rect.Right = size.X * scale.X + screen_rect.Left;
		screen_rect.Bottom = height * scale.Y + screen_rect.Top;
		screen_rect += Location;
		screen_rect.Left = bfmeFloor(screen_rect.Left + 0.5f);
		screen_rect.Top = bfmeFloor(screen_rect.Top + 0.5f);
		screen_rect.Right = bfmeFloor(screen_rect.Right + 0.5f);
		screen_rect.Bottom = bfmeFloor(screen_rect.Bottom + 0.5f);

		bool add_quad = true;
		if (IsClippedEnabled)
		{
			if (screen_rect.Right <= ClipRect.Left || screen_rect.Bottom <= ClipRect.Top)
			{
				add_quad = false;
			}
			else
			{
				RectClass clipped_rect;
				clipped_rect.Left = max(screen_rect.Left, ClipRect.Left);
				clipped_rect.Right = min(screen_rect.Right, ClipRect.Right);
				clipped_rect.Top = max(screen_rect.Top, ClipRect.Top);
				clipped_rect.Bottom = min(screen_rect.Bottom, ClipRect.Bottom);

				RectClass clipped_uv_rect;
				float percent = ((clipped_rect.Left - screen_rect.Left) / screen_rect.Width());
				clipped_uv_rect.Left = uv_rect.Left + (uv_rect.Width() * percent);

				percent = ((clipped_rect.Right - screen_rect.Left) / screen_rect.Width());
				clipped_uv_rect.Right = uv_rect.Left + (uv_rect.Width() * percent);

				percent = ((clipped_rect.Top - screen_rect.Top) / screen_rect.Height());
				clipped_uv_rect.Top = uv_rect.Top + (uv_rect.Height() * percent);

				percent = ((clipped_rect.Bottom - screen_rect.Top) / screen_rect.Height());
				clipped_uv_rect.Bottom = uv_rect.Top + (uv_rect.Height() * percent);

				screen_rect = clipped_rect;
				uv_rect = clipped_uv_rect;

				if (screen_rect.Right <= screen_rect.Left || screen_rect.Bottom <= screen_rect.Top)
				{
					add_quad = false;
				}
			}
		}

		if (add_quad)
		{
			SurfaceClass::SurfaceDescription desc;
			((SurfaceClass *)&curr_surface)->Get_Description(desc);

			uv_rect.Left *= 1.0F / ((float)desc.Width);
			uv_rect.Right *= 1.0F / ((float)desc.Width);
			uv_rect.Top *= 1.0F / ((float)desc.Height);
			uv_rect.Bottom *= 1.0F / ((float)desc.Height);

			curr_renderer->Add_Quad(screen_rect, uv_rect, color1, color2, color3, color4);

			if (DrawExtents.Width() == 0)
				DrawExtents = screen_rect;
			else
				DrawExtents += screen_rect;
		}
		}
	}
}
