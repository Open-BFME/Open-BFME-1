

struct PalantirPoint
{
	float x;
	float y;
};

extern int g_aptPalantirRadarLeft;
// Retail's clip rectangle has four consecutive, zero-initialized int edges.
// The left edge is owned by AptPalantirRenderRadar.cpp.
int g_aptPalantirRadarTop = 0;
int g_aptPalantirRadarRight = 0;
int g_aptPalantirRadarBottom = 0;

// ?aptPalantirClipRadar@@YAXPBUPalantirPoint@@0@Z
void __cdecl aptPalantirClipRadar( const PalantirPoint *origin, const PalantirPoint *extent )
{
	g_aptPalantirRadarLeft = (int)(origin->x + 0.5f);
	g_aptPalantirRadarTop = (int)(origin->y + 0.5f);
	g_aptPalantirRadarRight = g_aptPalantirRadarLeft + (int)(extent->x + 0.5f);
	g_aptPalantirRadarBottom = g_aptPalantirRadarTop + (int)(extent->y + 0.5f);
}
