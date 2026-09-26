// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned char Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

// The value returned by this BFME radar helper is the one-pointer D3D surface
// wrapper.  The adopting constructor and destructor are already byte-verified
// at 0x008FC590 and 0x008FC5B0 respectively.
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
	W3DRadarResetSurface( SurfaceResource *surface );
	__forceinline W3DRadarResetSurface( const W3DRadarResetSurface &other ) : m_surface( other.m_surface )
	{
		if( m_surface )
			m_surface->addRef();
	}
	~W3DRadarResetSurface();

private:
	SurfaceResource *m_surface;
};

class W3DRadarD3DTexture
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual int __stdcall getSurfaceLevel( UnsignedInt level, SurfaceResource **surface );
};

struct W3DRadarTextureResource
{
	char pad00[ 8 ];
	W3DRadarD3DTexture *d3dTexture;
};

// The caller passes the Image-held texture pointer as this.  Its texture
// object's BFME resource field is at +0x14, and the D3D object is at +0x08 of
// that resource; both offsets are visible in the retail body.
class W3DRadarTextureObject
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual Bool slot28();
	virtual void slot2c();
	char pad04[ 0x10 ];
	W3DRadarTextureResource *resource;
};

class W3DRadarIndexBufferDebugStream
{
public:
	virtual W3DRadarIndexBufferDebugStream *slot00( int value );
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual W3DRadarIndexBufferDebugStream *slot38( const void *value );
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual W3DRadarIndexBufferDebugStream *slot4c( int value );
};

class BFMEIndexBufferDebugClass
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5c();
	virtual void slot60(); virtual void slot64(); virtual void slot68();
	virtual W3DRadarIndexBufferDebugStream *slot6c( int first, int second );
};

extern BFMEIndexBufferDebugClass *g_BFMEIndexBufferDebug;
extern void _bfme_debugRecordCallsite( int kind );

static __forceinline void W3DRadarDX8ErrorCode( int result )
{
	if( result != 0 )
	{
		_bfme_debugRecordCallsite( 1 );
		g_BFMEIndexBufferDebug->slot60();
		g_BFMEIndexBufferDebug->slot6c( 0, 0 )->slot38( (const void *)0x111d770 )
			->slot00( result )->slot4c( 1 );
	}
}

class W3DRadarResetTexture
{
public:
	W3DRadarResetSurface getSurfaceLevel( UnsignedInt level );

private:
	W3DRadarTextureObject *texture;
};

W3DRadarResetSurface W3DRadarResetTexture::getSurfaceLevel( UnsignedInt level )
{
	if( static_cast<Int>( level ) < 0 )
		return W3DRadarResetSurface();

	W3DRadarTextureObject *textureObject = texture;
	if( textureObject == 0 )
		return W3DRadarResetSurface();

	if( !textureObject->slot28() )
		textureObject->slot2c();

	if( textureObject->resource->d3dTexture == 0 )
		return W3DRadarResetSurface();

	SurfaceResource *surface = 0;
	W3DRadarD3DTexture *texture = textureObject->resource->d3dTexture;
	int result = texture->getSurfaceLevel( level, &surface );
	W3DRadarDX8ErrorCode( result );

	W3DRadarResetSurface resultSurface( surface );
	if( surface )
		surface->release();
	return resultSurface;
}
