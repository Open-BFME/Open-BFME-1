// cl: /DNDEBUG /MD /EHsc
// readable body of ?Build_Textures@Render2DSentenceClass@@AAEXXZ: game/Libraries/Source/WWVegas/WW3D2/render2dsentence.cpp
// Retail RVA 0x0093DD60, 530 bytes: BFME's Render2DSentenceClass::Build_Textures.
// It follows Zero Hour's render2dsentence.cpp loop (unlock and release the
// current surface, turn every pending surface into a texture, hand it to the
// pending renderers, then Delete_All the list) over BFME's handle types:
// the pending surface is a ref-counted D3D surface handle (W3DRadarResetSurface),
// the texture is a handle created by the six-argument init (0x0090DBC0), its
// surface comes back by value from getSurfaceLevel (0x0090E670), and the copy
// is the inlined zero-count path of the D3D9 UpdateSurface helper 0x0093D050
// (device slot 30 plus the DX8 call counter). Class layout and handle views
// follow the matched siblings Render2DSentenceDrawSentence.cpp, W3DRadarInit.cpp
// and Rva006C3500W3DRadarShroudCopy.cpp; Render2DClass keeps its texture at
// +0x4C with the +0x50 flag set to -1 while a texture is bound.
//
// [BFME 2 donor] Code/Libraries/Source/WWVegas/WW3D2/
// Render2DSentenceBuildTexturesBFME2.cpp (45afcff3): Set_Texture assigns the
// texture handle through its inline operator= and then derives the flag from
// the stored handle, which gives retail's neg / store +0x4C / sbb interleave.

#include "../WWLib/vector.h"

class SurfaceClass
{
public:
	struct SurfaceDescription
	{
		unsigned Format;
		unsigned Width;
		unsigned Height;
	};

	void Get_Description(SurfaceDescription &description);
	void Unlock(void);
};

class SurfaceResource
{
public:
	virtual void slot00();
	virtual unsigned long __stdcall addRef();
	virtual unsigned long __stdcall release();
};

class W3DRadarResetSurface
{
public:
	W3DRadarResetSurface() : m_surface(0) {}
	W3DRadarResetSurface(const W3DRadarResetSurface &other) : m_surface(other.m_surface)
	{
		if (m_surface)
			m_surface->addRef();
	}
	~W3DRadarResetSurface();

	SurfaceResource *m_surface;
};

class TextureBaseClass
{
public:
	void Add_Ref(void) { ++m_numRefs; }
	void Release_Ref(void);

	int m_unreconstructed_00;
	unsigned short m_numRefs;
};

class ShroudFilter
{
public:
	unsigned min_filter;
	unsigned mag_filter;
	unsigned unused;
	unsigned address_u;
	unsigned address_v;
};

class Gen_00920a60
{
public:
	void m(int value);
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter();
	TextureBaseClass *m_texture;
};

class Rva006D6050
{
public:
	void init(unsigned width, unsigned height, unsigned format,
		unsigned mip_levels, unsigned pool, unsigned render_target);

	TextureBaseClass *m_texture;
};

class W3DRadarResetTexture
{
public:
	W3DRadarResetSurface getSurfaceLevel();

	TextureBaseClass *m_texture;
};

// The texture handle: empty on construction, releases its texture on scope exit.
class Render2DSentenceTextureHandle
{
public:
	Render2DSentenceTextureHandle() : m_texture(0) {}
	~Render2DSentenceTextureHandle()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	__forceinline Render2DSentenceTextureHandle &operator=(const Render2DSentenceTextureHandle &other)
	{
		if (other.m_texture)
			other.m_texture->Add_Ref();
		if (m_texture)
			m_texture->Release_Ref();
		m_texture = other.m_texture;
		return *this;
	}

	TextureBaseClass *m_texture;
};

class Render2DClass
{
public:
	void Set_Texture(const Render2DSentenceTextureHandle &texture)
	{
		if (texture.m_texture == Texture.m_texture)
			return;
		Texture = texture;
		HasTexture = Texture.m_texture ? -1 : 0;
	}

private:
	unsigned char m_unmodelled[0x4C];
	Render2DSentenceTextureHandle Texture;
	int HasTexture;
};

class IDirect3DSurface9;
class D3DDeviceInterface;

typedef long (__stdcall *UpdateSurfaceProc)(
	D3DDeviceInterface *device,
	SurfaceResource *source_surface,
	const void *source_rect,
	SurfaceResource *destination_surface,
	const void *destination_point);

struct D3DDeviceVTable
{
	void *m_slots_0_29[30];
	UpdateSurfaceProc UpdateSurface;
};

class D3DDeviceInterface
{
public:
	D3DDeviceVTable *m_vtable;
};

struct IDirect3DDevice8;

class Render2DSentenceClass;

class DX8Wrapper
{
protected:
	static IDirect3DDevice8 *D3DDevice;
	friend class Render2DSentenceClass;
};
#define g_render2DSentenceD3DDevice (reinterpret_cast<D3DDeviceInterface *>(DX8Wrapper::D3DDevice))
extern unsigned number_of_DX8_calls;

class FontCharsClass;

struct Vector2i
{
	int I;
	int J;
	void Set(int i, int j) { I = i; J = j; }
};

class Render2DSentenceClass
{
public:
	struct SentenceDataStruct : public W3DRadarResetSurface
	{
		bool operator==(const SentenceDataStruct &) { return false; }
		bool operator!=(const SentenceDataStruct &) { return true; }
		float ScreenRect[4], UVRect[4];
	};

	struct PendingSurfaceStruct : public W3DRadarResetSurface
	{
		DynamicVectorClass<Render2DClass *> Renderers;
		~PendingSurfaceStruct();

		bool operator==(const PendingSurfaceStruct &) { return false; }
		bool operator!=(const PendingSurfaceStruct &) { return true; }
	};

	virtual void Reset(void);

private:
	void Build_Textures(void);

	DynamicVectorClass<SentenceDataStruct> sentence_data;
	DynamicVectorClass<PendingSurfaceStruct> pending_surfaces;
	unsigned char renderers[0x18];
	FontCharsClass *font;
	float base_location_x;
	float base_location_y;
	float Location[2];
	float cursor_x;
	float cursor_y;
	Vector2i TextureOffset;
	int texture_start_x;
	int current_texture_size;
	int texture_size_hint;
	W3DRadarResetSurface cur_surface;
	char remaining_fields[0x0C];
	float ClipRect[4], DrawExtents[4];
	bool IsClippedEnabled;
	char padAD[3];
	unsigned short *locked_ptr;
};

typedef char Rva0093DD60PendingSurface[(sizeof(Render2DSentenceClass::PendingSurfaceStruct) == 0x1C) ? 1 : -1];

// ?Build_Textures@Render2DSentenceClass@@AAEXXZ
void Render2DSentenceClass::Build_Textures(void)
{
	//
	//	Make sure we unlock the current surface
	//
	if (locked_ptr != 0) {
		((SurfaceClass *)&cur_surface)->Unlock();
		locked_ptr = 0;
	}

	//
	//	Release our hold on the current surface
	//
	if (cur_surface.m_surface) {
		cur_surface.m_surface->release();
		cur_surface.m_surface = 0;
	}
	TextureOffset.Set(0, 0);
	texture_start_x = 0;

	//
	//	Convert all pending surfaces to textures
	//
	for (int index = 0; index < pending_surfaces.Count(); index++) {
		PendingSurfaceStruct &surface_info = pending_surfaces[index];
		W3DRadarResetSurface curr_surface(surface_info);

		SurfaceClass::SurfaceDescription desc;
		((SurfaceClass *)&curr_surface)->Get_Description(desc);

		Render2DSentenceTextureHandle new_texture;
		((Rva006D6050 *)&new_texture)->init(desc.Width, desc.Width, desc.Format, 1, 0, 0);
		W3DRadarResetSurface texture_surface = ((W3DRadarResetTexture *)&new_texture)->getSurfaceLevel();

		ShroudTexture *filter_owner = (ShroudTexture *)&new_texture;
		filter_owner->getFilter()->address_u = 1;
		filter_owner->getFilter()->address_v = 1;
		filter_owner->getFilter()->min_filter = 2;
		filter_owner->getFilter()->mag_filter = 2;
		((Gen_00920a60 *)filter_owner->getFilter())->m(2);

		//
		//	Copy the contents of the texture from the surface
		//
		g_render2DSentenceD3DDevice->m_vtable->UpdateSurface(
			g_render2DSentenceD3DDevice, curr_surface.m_surface, 0, texture_surface.m_surface, 0);
		++number_of_DX8_calls;

		//
		//	Assign this texture to any renderers that need it
		//
		for (int renderer_index = 0; renderer_index < surface_info.Renderers.Count(); renderer_index++) {
			Render2DClass *renderer = surface_info.Renderers[renderer_index];
			renderer->Set_Texture(new_texture);
		}

		if (new_texture.m_texture) {
			new_texture.m_texture->Release_Ref();
			new_texture.m_texture = 0;
		}
	}

	//
	//	Reset the list
	//
	if (pending_surfaces.Count() > 0) {
		pending_surfaces.Delete_All();
	}
}
