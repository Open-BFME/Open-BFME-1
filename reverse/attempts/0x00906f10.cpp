// ?d_00906f10@@YAXXZ
// partial score=0.63 date=2026-09-09
// cl: /DNDEBUG /MD /EHs-c-
// Scratch shape for the BFME DX8 render-target wrapper.  The production
// version will retain the W3DRadar value-surface ABI and its upstream source
// provenance at the official DX8Wrapper path.

struct IDirect3DSurface8;

class W3DRadarResetSurface
{
public:
	W3DRadarResetSurface() : m_surface( 0 ) {}
	W3DRadarResetSurface( const W3DRadarResetSurface &other ) : m_surface( other.m_surface ) {}
	~W3DRadarResetSurface();
	__forceinline void *getSurface() const { return m_surface; }

	void *m_surface;
};

class W3DRadarResetTexture
{
public:
	__declspec(noinline) W3DRadarResetSurface getSurfaceLevel();

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
};

void DX8Wrapper::Set_Render_Target_With_Z(TextureClass *texture, ZTextureClass *ztexture)
{
	IDirect3DSurface8 *d3d_surf = reinterpret_cast<IDirect3DSurface8 *>( texture->getSurfaceLevel().getSurface() );
	if (d3d_surf != 0)
	{
		if ( *reinterpret_cast<void **>( ztexture ) != 0 )
		{
			IDirect3DSurface8 *d3d_zbuf = reinterpret_cast<IDirect3DSurface8 *>( ztexture->getSurfaceLevel().getSurface() );
			if (d3d_zbuf != 0)
				Set_Render_Target( d3d_surf, d3d_zbuf );
		}
		else
		{
			Set_Render_Target( d3d_surf, true );
		}
		*reinterpret_cast<bool *>( 0x01340548 ) = true;
	}
}
