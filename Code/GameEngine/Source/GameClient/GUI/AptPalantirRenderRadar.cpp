extern "C" long __ftol2( double value );

struct PalantirPoint
{
	float x;
	float y;
};

class AptPalantir
{
public:
	void renderRadar( int x0, int y0, int x1, int y1, int *clipRectangle );
};

extern AptPalantir *TheAptPalantir;
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
