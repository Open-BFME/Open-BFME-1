// ?Set_Render_Target_With_Z@DX8Wrapper@@SAXPAVTextureClass@@PAVZTextureClass@@@Z
// partial score=0.75 date=2026-09-13
// cl: /DNDEBUG /MD /EHs-c-
// DX8Wrapper::Set_Render_Target_With_Z, retail 0x00906F10 (132 B).  texture/
// ztexture alias BFME's ref-counted radar texture wrapper view: a single
// pointer field at offset 0, matching W3DRadarResetTexture's layout already
// proven at W3DRadarGetSurfaceLevel.cpp / W3DRadarResetSurface_destructor.cpp.
// Full retail disassembly confirms the ABI: two getSurfaceLevel() sret calls
// (0x0090E670), each read via edi/esi with NO separate stack-resident
// wrapper access (the wrapper's .getSurface() is read straight out of the
// sret buffer), two conditional ~W3DRadarResetSurface() calls (0x008FC5B0),
// then Set_Render_Target(surf, zbuf|true).  Retail shares ONE physical call
// site for both "no z-target" paths (ztexture's internal pointer null, or
// its surface fetch failing) by tracking "was zbuf constructed" in EBX (bl)
// and only calling the destructor when set; this source's two textual calls
// to Set_Render_Target(d3d_surf, true) do not fold into that shared tail, so
// the body compiles 10 bytes over (142 vs 132) with no EBX in use.  Ruled
// out: /EHsc (adds a full SEH frame, +44 bytes, wrong); default-init +
// nested if/else in ZH's textual shape (still no merge, same 142 B); direct
// getSurfaceLevel() call without the wrapper (was the 109 B / 0.63 bank,
// missing the whole surface-wrapper ABI).  Next lever to try: reproduce the
// EBX "constructed" flag explicitly, or find the exact statement order that
// makes MSVC 7.1 emit the shared fallback tail instead of two copies.
// t=32min model=claude-sonnet-5

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

void DX8Wrapper::Set_Render_Target_With_Z(TextureClass *texture, ZTextureClass *ztexture)
{
	IDirect3DSurface8 *d3d_surf;
	{
		W3DRadarResetSurface surf;
		surf = texture->getSurfaceLevel();
		d3d_surf = reinterpret_cast<IDirect3DSurface8 *>(surf.getSurface());
	}
	if (d3d_surf != 0)
	{
		if (*reinterpret_cast<void **>(ztexture) != 0)
		{
			IDirect3DSurface8 *d3d_zbuf;
			{
				W3DRadarResetSurface zbuf = ztexture->getSurfaceLevel();
				d3d_zbuf = reinterpret_cast<IDirect3DSurface8 *>(zbuf.getSurface());
			}
			if (d3d_zbuf != 0)
				Set_Render_Target(d3d_surf, d3d_zbuf);
			else
				Set_Render_Target(d3d_surf, true);
		}
		else
		{
			Set_Render_Target(d3d_surf, true);
		}
		IsRenderToTexture = true;
	}
}
