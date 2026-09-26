extern "C" long __ftol2( double value );

struct PalantirPoint
{
	float x;
	float y;
};

extern int g_aptPalantirRadarLeft;
extern int g_aptPalantirRadarTop;
extern int g_aptPalantirRadarRight;
extern int g_aptPalantirRadarBottom;

// ?aptPalantirClipRadar@@YAXPBUPalantirPoint@@0@Z
void __cdecl aptPalantirClipRadar( const PalantirPoint *origin, const PalantirPoint *extent )
{
	g_aptPalantirRadarLeft = (int)(origin->x + 0.5f);
	g_aptPalantirRadarTop = (int)(origin->y + 0.5f);
	g_aptPalantirRadarRight = g_aptPalantirRadarLeft + (int)(extent->x + 0.5f);
	g_aptPalantirRadarBottom = g_aptPalantirRadarTop + (int)(extent->y + 0.5f);
}
