// ??0AptPalantir@@QAE@XZ
// partial score=0.99 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// The installed vtables match the AptPalantir destructor at 0x0079D1D0.
// RadarViewBoxEdge and the registered callback names independently identify this class.
// The destructor witnesses the base size, texture field, and three Coord2D arrays.
#include "ascii_string.h"

extern void j_0001d606();
extern void j_000336ae();

// Empty routes for the two image ILT thunks: a member-pointer call through one
// of these keeps the direct `call <thunk>` shape retail has, which a
// pointer-to-member of a polymorphic class does not.
class Route0001D606 {};
class Route000336AE {};

class BFMERetailAsciiString : public AsciiString
{
public:
	BFMERetailAsciiString( const char *text );
};

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

class Rva00597FC0Client : public SubsystemInterface, public Snapshot
{
public:
	Rva00597FC0Client();
	virtual ~Rva00597FC0Client();

private:
	char m_base[0x504];
};

// Still needed: retail reaches the base ctor through ILT 0x0000DA58, but a
// mem-initializer can only ever name a constructor, so the compiler emits the
// only relocation it can there.  Routing the thunk through a member-pointer
// union means inlining the base ctor, which moves MSVC's two base-subobject
// vptr stores (0x01127A48 / 0x01127A34) ahead of the call and shifts the rest
// of the body; defining the ctor out of line would add a new retail-looking
// symbol.
#pragma comment(linker, "/alternatename:??0Rva00597FC0Client@@QAE@XZ=?j_0000da58@@YAXXZ")

class Image;
class ImageCollection
{
public:
	// retail calls this through ILT 0x0001D606, see Rva0079D9F0ImageSlot
	const Image *findImageByName( const AsciiString &name );
};

extern ImageCollection *TheMappedImageCollection;

class Image
{
public:
	// retail calls this through ILT 0x000336AE, see AptPalantir::AptPalantir
	AsciiString getFilename() const;

private:
	char m_prefix[8];
	AsciiString m_filename;
};

class Rva0079D9F0ImageSlot
{
public:
	__forceinline Rva0079D9F0ImageSlot()
	{
		BFMERetailAsciiString name( "RadarViewBoxEdge" );
		// retail calls ImageCollection::findImageByName through ILT
		// 0x0001D606; the route keeps that a plain `call <thunk>`.
		typedef const Image *(Route0001D606::*Find)( const AsciiString & );
		union
		{
			void (*fn)();
			Find call;
		} u = { j_0001d606 };
		m_image = (((Route0001D606 *)TheMappedImageCollection)->*u.call)(
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

class TextureBaseClass { public: void Release_Ref(); };

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;
	~BFMEWaterTrackTextureHandle()
	{
		if( m_texture )
			((TextureBaseClass *)m_texture)->Release_Ref();
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

class AptPalantir : public Rva00597FC0Client
{
public:
	virtual ~AptPalantir();
	AptPalantir();

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

AptPalantir *TheAptPalantir = 0;

static char *bfmeString( const AsciiString &value )
{
	char *data = *(char **)&value;
	return data ? data + 8 : (char *)"";
}

AptPalantir::AptPalantir()
	: Rva00597FC0Client()
	, m_510( 0 )
	, m_514( 0 )
	, m_518( 0 )
	, m_image51c()
	, m_texture520()
{
	if( m_image51c.m_image )
	{
		// j_000336AE is the ILT thunk retail calls for Image::getFilename; the
		// by-value AsciiString it fills has to be consumed inside this
		// expression or the compiler destroys it before the call below.
		typedef AsciiString (Route000336AE::*Get)() const;
		union
		{
			void (*fn)();
			Get call;
		} u = { j_000336ae };
		m_texture520 = BFMEGetWaterTrackTexture(
			bfmeString(
				((Route000336AE *)m_image51c.m_image->*u.call)() ), 1, 0 );
	}
}
