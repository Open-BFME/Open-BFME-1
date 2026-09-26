extern "C" long __ftol2( double value );

struct PalantirPoint
{
	float x;
	float y;
};

class GameWindow
{
public:
	int winGetPosition( int *x, int *y );
	int winSetPosition( int x, int y );
	int winGetSize( int *width, int *height );
	int winSetSize( int width, int height );
};

class Radar
{
public:
	virtual void unused00();
	virtual void unused04();
	virtual void unused08();
	virtual void unused0c();
	virtual void unused10();
	virtual void unused14();
	virtual void unused18();
	virtual void draw( int x, int y, int width, int height, int unknown );
};

struct RadarClipThunk
{
	void call( int *clipRectangle );
};

struct RadarClearClipThunk
{
	void call();
};

extern void j_000234de();
extern void j_0001cd50();

class AptPalantir
{
public:
	void renderRadar( int x0, int y0, int x1, int y1, int *clipRectangle );

private:
	unsigned char m_unmodelled00[ 0x0c ];
	GameWindow *m_window;
};

extern AptPalantir *TheAptPalantir;
extern Radar *TheRadar;
extern int g_aptPalantirRadarLeft;

// ?aptPalantirRenderRadar@@YAXPBUPalantirPoint@@0@Z
void __cdecl aptPalantirRenderRadar( const PalantirPoint *from, const PalantirPoint *to )
{
	TheAptPalantir->renderRadar(
		(int)(from->x + 0.5f),
		(int)(from->y + 0.5f),
		(int)(to->x + 0.5f),
		(int)(to->y + 0.5f),
		&g_aptPalantirRadarLeft );
}

// ?renderRadar@AptPalantir@@QAEXHHHHPAH@Z
void AptPalantir::renderRadar( int x0, int y0, int x1, int y1,
	int *clipRectangle )
{
	int windowX;
	int windowY;
	m_window->winGetPosition( &windowX, &windowY );

	if( clipRectangle[ 0 ] != windowX || clipRectangle[ 1 ] != windowY )
	{
		m_window->winSetPosition( clipRectangle[ 0 ], clipRectangle[ 1 ] );
	}

	int windowWidth;
	int windowHeight;
	m_window->winGetSize( &windowWidth, &windowHeight );

	if( clipRectangle[ 2 ] - clipRectangle[ 0 ] != windowWidth ||
		clipRectangle[ 3 ] - clipRectangle[ 1 ] != windowHeight )
	{
		m_window->winSetSize( clipRectangle[ 2 ] - clipRectangle[ 0 ],
			clipRectangle[ 3 ] - clipRectangle[ 1 ] );
	}

	if( x0 == clipRectangle[ 0 ] && y0 == clipRectangle[ 1 ] &&
		x1 == clipRectangle[ 2 ] - clipRectangle[ 0 ] &&
		y1 == clipRectangle[ 3 ] - clipRectangle[ 1 ] )
	{
		TheRadar->draw( x0, y0, x1, y1, -1 );
	}
	else
	{
		union
		{
			void *asVoid;
			void (RadarClipThunk::*asMember)( int * );
		} setClip;
		setClip.asVoid = (void *)j_000234de;
		(reinterpret_cast<RadarClipThunk *>( TheRadar )->*setClip.asMember)( clipRectangle );
		TheRadar->draw( x0, y0, x1, y1, -1 );
		union
		{
			void *asVoid;
			void (RadarClearClipThunk::*asMember)();
		} clearClip;
		clearClip.asVoid = (void *)j_0001cd50;
		(reinterpret_cast<RadarClearClipThunk *>( TheRadar )->*clearClip.asMember)();
	}
}
