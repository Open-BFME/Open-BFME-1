// cl: /DNDEBUG /MD
// DX8Wrapper::Set_Render_Target_With_Z retail 0x00906F10 (132 B). BFME port of
// the Zero Hour twin in dx8wrapper.cpp: raw Get_D3D_Surface_Level surfaces
// became W3DRadarResetSurface sret temporaries read straight out of the return
// buffer. The z-side pointer is a ?: over a single-arm sret temporary, so the
// compiler guards its destructor with a constructed flag (EBX) after the join
// and shares one Set_Render_Target(surf true) tail. Built without EH; /EHs-c-
// sets the flag before the call and misses.

struct IDirect3DSurface8;

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
	W3DRadarResetSurface() : m_surface( 0 ) {}
	__forceinline W3DRadarResetSurface( const W3DRadarResetSurface &other ) : m_surface( other.m_surface )
	{
		if( m_surface )
			m_surface->addRef();
	}
	~W3DRadarResetSurface();
	__forceinline void *getSurface() const { return m_surface; }

private:
	SurfaceResource *m_surface;
};

class W3DRadarResetTexture
{
public:
	W3DRadarResetSurface getSurfaceLevel();

private:
	void *texture;
};

class TextureClass : public W3DRadarResetTexture
{
};

class ZTextureClass : public W3DRadarResetTexture
{
};

class DX8Wrapper
{
public:
	static void Set_Render_Target_With_Z(TextureClass *texture, ZTextureClass *ztexture);
	static void Set_Render_Target(IDirect3DSurface8 *renderTarget, IDirect3DSurface8 *depthBuffer);
	static void Set_Render_Target(IDirect3DSurface8 *renderTarget, bool useDefaultDepthBuffer);

private:
	static bool IsRenderToTexture;
};

// ?Set_Render_Target_With_Z@DX8Wrapper@@SAXPAVTextureClass@@PAVZTextureClass@@@Z
void DX8Wrapper::Set_Render_Target_With_Z(TextureClass *texture, ZTextureClass *ztexture)
{
	IDirect3DSurface8 *d3d_surf = reinterpret_cast<IDirect3DSurface8 *>( texture->getSurfaceLevel().getSurface() );
	if (d3d_surf != 0)
	{
		IDirect3DSurface8 *d3d_zbuf = (*reinterpret_cast<void **>(ztexture) != 0)
			? reinterpret_cast<IDirect3DSurface8 *>( ztexture->getSurfaceLevel().getSurface() )
			: 0;
		if (d3d_zbuf != 0)
			Set_Render_Target(d3d_surf, d3d_zbuf);
		else
			Set_Render_Target(d3d_surf, true);
		IsRenderToTexture = true;
	}
}
