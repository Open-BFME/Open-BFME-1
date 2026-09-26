// ?Draw_Sentence@Render2DSentenceClass@@QAEXKKKK@Z
// partial score=0.43 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Oy /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

#include "vector.h"
#include "vector2.h"
#include "vector2i.h"
#include "rect.h"

class FontCharsClass;
class TextureClass;
class SurfaceClass;

class Render2DClass
{
public:
	Render2DClass(void);
	void Set_Coordinate_Range(const RectClass &range);
	void Add_Quad(const RectClass &screen, const RectClass &uv,
		unsigned long color0, unsigned long color1,
		unsigned long color2, unsigned long color3);

private:
	unsigned char m_unmodelled[0x58];
};

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
	virtual void __stdcall add_ref(void);
	virtual void __stdcall release(void);
	void Get_Description(SurfaceDescription &description);
};

class W3DRadarResetSurface
{
public:
	W3DRadarResetSurface(void) : m_surface(0) { }

	W3DRadarResetSurface &operator=(SurfaceClass *surface)
	{
		if (surface)
			surface->add_ref();
		SurfaceClass *old_surface = getSurface();
		if (old_surface)
			old_surface->release();
		m_surface = surface;
		return *this;
	}

	W3DRadarResetSurface &operator=(const W3DRadarResetSurface &other)
	{
		SurfaceClass *incoming = other.getSurface();
		if (incoming)
			incoming->add_ref();
		SurfaceClass *outgoing = getSurface();
		if (outgoing)
			outgoing->release();
		m_surface = incoming;
		return *this;
	}

	~W3DRadarResetSurface(void);

	SurfaceClass *getSurface(void) const
	{
		return m_surface;
	}

	void Get_Description(SurfaceClass::SurfaceDescription &description)
	{
		reinterpret_cast<SurfaceClass *>(this)->Get_Description(description);
	}

	SurfaceClass *m_surface;
};

extern unsigned int BfmeRenderWidth;
extern unsigned int BfmeRenderHeight;
extern float g_bfmeDefaultBR;
extern float g_bfmeDefaultBU;
extern float g_bfmeUint32Scale;
extern float g_bfmeADL;
extern "C" __declspec(dllimport) double __cdecl floor(double value);

class Render2DSentenceClass
{
public:
	virtual void Reset(void);

	struct SentenceDataStruct
	{
		SurfaceClass *Surface;
		RectClass ScreenRect;
		RectClass UVRect;

		bool operator==(const SentenceDataStruct &) const { return false; }
		bool operator!=(const SentenceDataStruct &) const { return true; }
	};

	struct PendingSurfaceStruct
	{
		SurfaceClass *Surface;
		DynamicVectorClass<Render2DClass *> Renderers;

		bool operator==(const PendingSurfaceStruct &) const { return false; }
		bool operator!=(const PendingSurfaceStruct &) const { return true; }
	};

	struct RendererDataStruct
	{
		Render2DClass *Renderer;
		W3DRadarResetSurface Surface;

		bool operator==(const RendererDataStruct &) const { return false; }
		bool operator!=(const RendererDataStruct &) const { return true; }
	};

	void Draw_Sentence(unsigned long color0, unsigned long color1,
		unsigned long color2, unsigned long color3);

private:
	DynamicVectorClass<SentenceDataStruct> SentenceData;
	DynamicVectorClass<PendingSurfaceStruct> PendingSurfaces;
	DynamicVectorClass<RendererDataStruct> Renderers;
	FontCharsClass *Font;
	Vector2 BaseLocation;
	Vector2 Location;
	Vector2 Cursor;
	Vector2i TextureOffset;
	int TextureStartX;
	int CurrTextureSize;
	int TextureSizeHint;
	W3DRadarResetSurface CurSurface;
	bool MonoSpaced;
	float WrapWidth;
	bool Centered;
	RectClass ClipRect;
	RectClass DrawExtents;
	bool IsClippedEnabled;
	bool ParseHotKey;
	bool useHardWordWrap;
	unsigned short *LockedPtr;
	int LockedStride;
	TextureClass *CurTexture;
	float ScaleX;
	float ScaleY;
	float RequestedWidth;
	float RequestedHeight;
};

void Render2DSentenceClass::Draw_Sentence(unsigned long color0,
	unsigned long color1, unsigned long color2, unsigned long color3)
{
	Render2DClass *curr_renderer = NULL;
	W3DRadarResetSurface curr_surface;
	float scale_x = ScaleX;
	float scale_y = ScaleY;
	int offset = 0;

	DrawExtents = RectClass(0.0F, 0.0F, 0.0F, 0.0F);

	if (RequestedWidth > g_bfmeDefaultBR && RequestedHeight > g_bfmeDefaultBR) {
		for (int index = 0; index < SentenceData.Count(); index++, offset += sizeof(SentenceDataStruct)) {
			SentenceDataStruct *data = reinterpret_cast<SentenceDataStruct *>(
				(unsigned int)&SentenceData[0] + offset);
			if (DrawExtents.Right - DrawExtents.Left == g_bfmeDefaultBR)
				DrawExtents = data->ScreenRect;
			else
				DrawExtents += data->ScreenRect;
		}
		offset = 0;
		if (DrawExtents.Right - DrawExtents.Left != g_bfmeDefaultBR)
			scale_x = RequestedWidth / (DrawExtents.Right - DrawExtents.Left);
		if (DrawExtents.Bottom - DrawExtents.Top != g_bfmeDefaultBR)
			scale_y = RequestedHeight / (DrawExtents.Bottom - DrawExtents.Top);
	}

	DrawExtents = RectClass(0.0F, 0.0F, 0.0F, 0.0F);

	for (int index = 0; index < SentenceData.Count(); index++, offset += sizeof(SentenceDataStruct)) {
		SentenceDataStruct &data = SentenceData[index];

		if (data.Surface != curr_surface.getSurface()) {
			curr_surface = data.Surface;

			bool found = false;
        for (int renderer_index = 0; renderer_index < Renderers.Count(); renderer_index++) {
				if (Renderers[renderer_index].Surface.getSurface() == curr_surface.getSurface()) {
					found = true;
					curr_renderer = Renderers[renderer_index].Renderer;
					break;
				}
			}

			if (!found) {
				curr_renderer = W3DNEW Render2DClass;
				RectClass range(0.0F, 0.0F, (float)BfmeRenderWidth,
					(float)BfmeRenderHeight);
				curr_renderer->Set_Coordinate_Range(range);

				RendererDataStruct render_info;
				render_info.Renderer = curr_renderer;
				render_info.Surface = curr_surface;
				Renderers.Add(render_info);

				for (int surface_index = 0; surface_index < PendingSurfaces.Count(); surface_index++) {
					PendingSurfaceStruct &surface_info = PendingSurfaces[surface_index];
                    if (surface_info.Surface == curr_surface.getSurface())
						surface_info.Renderers.Add(curr_renderer);
				}
			}
		}

		RectClass uv_rect;
		RectClass screen_rect = data.ScreenRect;
		float width = screen_rect.Width();
		float height = screen_rect.Height();
		screen_rect.Left *= scale_x;
		screen_rect.Top *= scale_y;
		screen_rect.Right = screen_rect.Left + width * scale_x;
		screen_rect.Bottom = screen_rect.Top + height * scale_y;
		screen_rect += Location;
		uv_rect = data.UVRect;
		uv_rect.Left = (float)floor(uv_rect.Left + g_bfmeADL);
		uv_rect.Top = (float)floor(uv_rect.Top + g_bfmeADL);
		uv_rect.Right = (float)floor(uv_rect.Right + g_bfmeADL);
		uv_rect.Bottom = (float)floor(uv_rect.Bottom + g_bfmeADL);

		bool add_quad = true;
		if (IsClippedEnabled) {
			if (screen_rect.Right <= ClipRect.Left ||
				screen_rect.Bottom <= ClipRect.Top) {
				add_quad = false;
			} else {
				RectClass clipped_rect;
				clipped_rect.Left = max(screen_rect.Left, ClipRect.Left);
				clipped_rect.Right = min(screen_rect.Right, ClipRect.Right);
				clipped_rect.Top = max(screen_rect.Top, ClipRect.Top);
				clipped_rect.Bottom = min(screen_rect.Bottom, ClipRect.Bottom);

				RectClass clipped_uv_rect;
				float percent = (clipped_rect.Left - screen_rect.Left) / screen_rect.Width();
				clipped_uv_rect.Left = uv_rect.Left + uv_rect.Width() * percent;
				percent = (clipped_rect.Right - screen_rect.Left) / screen_rect.Width();
				clipped_uv_rect.Right = uv_rect.Left + uv_rect.Width() * percent;
				percent = (clipped_rect.Top - screen_rect.Top) / screen_rect.Height();
				clipped_uv_rect.Top = uv_rect.Top + uv_rect.Height() * percent;
				percent = (clipped_rect.Bottom - screen_rect.Top) / screen_rect.Height();
				clipped_uv_rect.Bottom = uv_rect.Top + uv_rect.Height() * percent;

				screen_rect = clipped_rect;
				uv_rect = clipped_uv_rect;

				if (screen_rect.Right <= screen_rect.Left ||
					screen_rect.Bottom <= screen_rect.Top)
					add_quad = false;
			}
		}

		if (add_quad) {
			__declspec(align(8)) SurfaceClass::SurfaceDescription desc;
			curr_surface.Get_Description(desc);
			float inv_width = g_bfmeDefaultBU / (float)desc.Width;
			uv_rect.Left *= inv_width;
			uv_rect.Right *= inv_width;
			float inv_height = g_bfmeDefaultBU / (float)desc.Height;
			uv_rect.Top *= inv_height;
			uv_rect.Bottom *= inv_height;
			curr_renderer->Add_Quad(screen_rect, uv_rect, color0, color1,
				color2, color3);

			if (DrawExtents.Right - DrawExtents.Left == g_bfmeDefaultBR)
				DrawExtents = screen_rect;
			else
				DrawExtents += screen_rect;
		}
	}
}
