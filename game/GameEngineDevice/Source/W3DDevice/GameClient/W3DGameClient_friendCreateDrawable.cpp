// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// W3DGameClient::friend_createDrawable, retail 0x006FBB20, 115 bytes.
// BFME adds an integer argument to the drawable factory and passes all three
// arguments to the 0x3d4-byte Drawable constructor.

typedef int Int;

class ThingTemplate;

enum DrawableStatus
{
	DRAWABLE_STATUS_NONE = 0
};

class Drawable
{
public:
	Drawable( const ThingTemplate *, DrawableStatus, Int );

private:
	unsigned char m_retailData[ 0x3d4 ];
};

class W3DGameClient
{
public:
	virtual Drawable *friend_createDrawable( const ThingTemplate *, DrawableStatus, Int );
};

// ?friend_createDrawable@W3DGameClient@@UAEPAVDrawable@@PBVThingTemplate@@W4DrawableStatus@@H@Z
Drawable *W3DGameClient::friend_createDrawable( const ThingTemplate *tmplate,
	DrawableStatus statusBits, Int drawableID )
{
    Drawable *draw = 0;

    if( tmplate == 0 )
        return 0;

	draw = new Drawable( tmplate, statusBits, drawableID );

	return draw;
}
