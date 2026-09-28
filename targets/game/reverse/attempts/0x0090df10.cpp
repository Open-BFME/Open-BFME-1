// ?bfmeOneBKF@BfmePartBKF@@QAEXXZ
// partial score=0.94 date=2026-09-28
struct BfmePartBKF
{
	void bfmeOneBKF();
	unsigned char m_bfmeHead[4];
};

class BfmeThingBKF
{
public:
	void bfmeGoBKF();
	unsigned char m_bfmeHead[0x2c];
	BfmePartBKF m_bfmeB;
	BfmePartBKF m_bfmeA;
	unsigned char m_bfmeGap[0x40];
	bool m_bfmeFlag;
};

void BfmeThingBKF::bfmeGoBKF()
{
	m_bfmeFlag = true;
	m_bfmeA.bfmeOneBKF();
	m_bfmeB.bfmeOneBKF();
}

// The matched caller at 0x00728A60 names this method and calls its retail body
// at 0x0090DF10, so the reconstruction stays beside that caller.
class Rva008FCAB0
{
public:
	char storage[ 4 ];
	void method( float x, float y, float z );
};

class W3DRadarResetSurface : public Rva008FCAB0
{
public:
	~W3DRadarResetSurface();
};

class W3DRadarTextureResource
{
public:
	char pad00[ 8 ];
	void * volatile d3dTexture;
};

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
	virtual bool slot28();
	virtual void slot2c();
	char pad04[ 0x10 ];
	W3DRadarTextureResource *resource;
};

class W3DRadarResetTexture
{
public:
	W3DRadarResetSurface getSurfaceLevel( unsigned int level );
};

struct Rva0090DF10TextureVTable
{
	void *slots00Through30[ 13 ];
	int (__stdcall *slot34)( void *texture );
	void *slots38Through50[ 7 ];
	void (__stdcall *slot54)( void *texture, int value );
};

extern float g_bfmeDefaultBU;

void BfmePartBKF::bfmeOneBKF()
{
	W3DRadarTextureObject *textureObject = *reinterpret_cast< W3DRadarTextureObject ** >( m_bfmeHead );
	if ( textureObject == 0 )
		return;
	if ( !textureObject->slot28() )
		return;
	W3DRadarTextureResource *resource = textureObject->resource;
	if ( resource->d3dTexture == 0 )
		return;

	void *texture = resource->d3dTexture;
	int surfaceCount = (*reinterpret_cast< Rva0090DF10TextureVTable ** >( texture ))->slot34( texture );
	float x;
	float y;
	float z;
	for ( int level = 1; level < surfaceCount; ++level )
	{
		float defaultValue = g_bfmeDefaultBU;
		switch ( level )
		{
		case 1:
			z = defaultValue;
			y = 0.0f;
			x = 0.0f;
			break;
		case 2:
			y = defaultValue;
			z = 0.0f;
			break;
		case 3:
			x = defaultValue;
			z = 0.0f;
			y = 0.0f;
			break;
		default:
			y = defaultValue;
			z = defaultValue;
			break;
		}

		reinterpret_cast< W3DRadarResetTexture * >( this )->getSurfaceLevel( level ).method( x, y, z );
	}

	void *finalTexture = (*reinterpret_cast< W3DRadarTextureObject ** >( m_bfmeHead ))->resource->d3dTexture;
	(*reinterpret_cast< Rva0090DF10TextureVTable ** >( finalTexture ))->slot54( finalTexture, 0 );
}
