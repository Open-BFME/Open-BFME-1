extern "C" long __ftol2( double value );

struct PalantirPoint
{
	float x;
	float y;
};

class AptPalantir
{
public:
	void renderMovie( int x0, int y0, int x1, int y1 );
};

extern AptPalantir *TheAptPalantir;

// ?aptPalantirRenderMovie@@YAXPBUPalantirPoint@@0@Z
void __cdecl aptPalantirRenderMovie( const PalantirPoint *from, const PalantirPoint *to )
{
	TheAptPalantir->renderMovie(
		(int)from->x,
		(int)from->y,
		(int)to->x,
		(int)to->y );
}
