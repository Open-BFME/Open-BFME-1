// ??0AptPalantir@@QAE@XZ
// partial score=0.99 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// The installed vtables match the AptPalantir destructor at 0x0079D1D0.
// RadarViewBoxEdge and the registered callback names independently identify this class.
// The destructor witnesses the base size, texture field, and three Coord2D arrays.
class AsciiString
{
public:
	AsciiString() {}
	~AsciiString() { releaseBuffer(); }
	void releaseBuffer();
	void *m_data;
};

class BFMERetailAsciiString : public AsciiString
{
public:
	BFMERetailAsciiString( const char *text );
};

#pragma comment(linker, "/alternatename:?releaseBuffer@AsciiString@@AAEXXZ=?releaseBuffer@BFMERetailAsciiString@@AAEXXZ")

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual bool loadIniFilesFromLegend();

private:
	void *m_name;
};

class Snapshot
{
public:
	virtual ~Snapshot();
};

class GameClient : public SubsystemInterface, public Snapshot
{
public:
	GameClient();
	virtual ~GameClient();

private:
	char m_base[0x504];
};

#pragma comment(linker, "/alternatename:??0GameClient@@QAE@XZ=?j_0000da58@@YAXXZ")

class Image;
class ImageCollection
{
public:
	const Image *findImageByName( const AsciiString &name );
};

extern ImageCollection *TheMappedImageCollection;

class Image
{
public:
	AsciiString getFilename() const;

private:
	char m_prefix[8];
	AsciiString m_filename;
};

#pragma comment(linker, "/alternatename:?findImageByName@ImageCollection@@QAEPBVImage@@ABVAsciiString@@@Z=?j_0001d606@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFilename@Image@@QBE?AVAsciiString@@XZ=?j_000336ae@@YAXXZ")

class Rva0079D9F0ImageSlot
{
public:
	__forceinline Rva0079D9F0ImageSlot()
	{
		BFMERetailAsciiString name( "RadarViewBoxEdge" );
		m_image = TheMappedImageCollection->findImageByName(
			*(const AsciiString *)&name );
	}

	const Image *m_image;
};

class TextureClass
{
public:
	void Release_Ref();
	void *m_vtable;
	unsigned short m_refCount;
};

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;
	~BFMEWaterTrackTextureHandle()
	{
		if( m_texture )
			m_texture->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	char *name, int mipCount, int format );

class AptPalantirTextureRef
{
public:
	AptPalantirTextureRef() : m_texture( 0 ) {}
	~AptPalantirTextureRef()
	{
		if( m_texture )
			m_texture->Release_Ref();
	}
	AptPalantirTextureRef &operator=( const BFMEWaterTrackTextureHandle &other )
	{
		if( other.m_texture )
			++other.m_texture->m_refCount;
		if( m_texture )
			m_texture->Release_Ref();
		m_texture = other.m_texture;
		return *this;
	}
	TextureClass *m_texture;
};

struct Coord2D
{
	Coord2D();
	~Coord2D();
	float x;
	float y;
};

class Rva0079D1D0AptPalantir : public GameClient
{
public:
	virtual ~Rva0079D1D0AptPalantir();
	Rva0079D1D0AptPalantir();

private:
	void *m_510;
	void *m_514;
	void *m_518;
	Rva0079D9F0ImageSlot m_image51c;
	AptPalantirTextureRef m_texture520;
	Coord2D m_coords524[4];
	Coord2D m_coords544[4];
	Coord2D m_coords564[4];
};

static char *bfmeString( const AsciiString &value )
{
	char *data = *(char **)&value;
	return data ? data + 8 : (char *)0x0107388b;
}

// ??0AptPalantir@@QAE@XZ present-unmatched
Rva0079D1D0AptPalantir::Rva0079D1D0AptPalantir()
	: GameClient()
	, m_510( 0 )
	, m_514( 0 )
	, m_518( 0 )
	, m_image51c()
	, m_texture520()
{
	if( m_image51c.m_image )
	{
		m_texture520 = BFMEGetWaterTrackTexture(
			bfmeString( m_image51c.m_image->getFilename() ), 1, 0 );
	}
}
