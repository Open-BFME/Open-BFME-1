// Open-BFME: Xfer::xferMapName, the portable save-game map path helper.
// The implementation follows the reference Xfer.cpp contract: save paths are
// made portable before transfer and portable paths are made real after load.

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Snapshot;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
struct XferReservedTag;
class UnicodeString;

class Xfer
{
public:
	virtual ~Xfer();
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;
	virtual void ReservedVirtual1();
	virtual void ReservedVirtual2();
	virtual void ReservedVirtual3();
	virtual void SkipBadBlock( Snapshot &snapshot, unsigned int size );
	virtual Xfer &XferRawBytes( void *data, unsigned int size );
	virtual Xfer &operator==( bool &value );
	virtual Xfer &operator==( char &value );
	virtual Xfer &operator==( unsigned char &value );
	virtual Xfer &operator==( short &value );
	virtual Xfer &operator==( unsigned short &value );
	virtual Xfer &operator==( int &value );
	virtual Xfer &operator==( unsigned int &value );
	virtual Xfer &operator==( __int64 &value );
	virtual Xfer &operator==( float &value );
	virtual Xfer &operator==( AsciiString &value );
	virtual Xfer &operator==( UnicodeString &value );
	virtual Xfer &operator==( Coord3DBase &value );
	virtual Xfer &operator==( ICoord3D &value );
	virtual Xfer &operator==( Region3D &value );
	virtual Xfer &operator==( IRegion3D &value );
	virtual Xfer &operator==( Coord2D &value );
	virtual Xfer &operator==( ICoord2D &value );
	virtual Xfer &operator==( Region2D &value );
	virtual Xfer &operator==( IRegion2D &value );
	virtual Xfer &operator==( RealRange &value );
	virtual Xfer &operator==( RGBColor &value );
	virtual Xfer &operator==( RGBAColorReal &value );
	virtual Xfer &operator==( RGBAColorInt &value );
	virtual Xfer &operator==( Snapshot &value );
	virtual Xfer &operator==( XferReservedTag &value );
	virtual Xfer &operator==( unsigned char (&version)[2] );
	virtual void ReservedVirtual4();
	virtual Xfer &XferEnum( const char *name, void *data, unsigned int size );

	void xferAsciiString( AsciiString *value ) { *this == *value; }
};

class GameState
{
public:
	AsciiString realMapPathToPortableMapPath( const AsciiString &path ) const;
	AsciiString portableMapPathToRealMapPath( const AsciiString &path ) const;
};

extern GameState *TheGameState;

void __cdecl xferMapName( Xfer *xfer, AsciiString *mapNameData )
{
	if ( xfer->IsStoring() )
	{
		AsciiString tmp = TheGameState->realMapPathToPortableMapPath( *mapNameData );
		xfer->xferAsciiString( &tmp );
	}
	else
	{
		xfer->xferAsciiString( mapNameData );
		*mapNameData = TheGameState->portableMapPathToRealMapPath( *mapNameData );
	}
}
