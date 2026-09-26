// cl: /DNDEBUG /MD /EHsc

// W3DRadarResetSurface::~W3DRadarResetSurface, retail 0x008FC5B0.  The
// temporary wrapper owns a SurfaceClass-like pointer at offset zero.  BFME's
// destructor releases that resource through vtable slot 2.

typedef void (__stdcall *SurfaceRelease)( void *surface );

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();

private:
	void *m_surface;
};

// ??1W3DRadarResetSurface@@QAE@XZ
W3DRadarResetSurface::~W3DRadarResetSurface()
{
	void *surface = m_surface;
	if (surface)
	{
		void **vtable = *reinterpret_cast<void ***>( surface );
		SurfaceRelease release = reinterpret_cast<SurfaceRelease>( vtable[ 2 ] );
		release( surface );
	}
}
