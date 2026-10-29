extern "C" long __ftol2( double value );

struct PalantirPoint
{
	float x;
	float y;
};

class AptPalantirGlobeRenderer
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual void unused3();
	virtual void unused4();
	virtual void unused5();
	virtual void unused6();
	virtual void unused7();
	virtual void unused8();
	virtual void drawLine( int x0, int y0, int x1, int y1 );
};

class Rva002EECE0;
// Retail 0x012F4B98 is ?TheAptPalantir@@3PAVAptPalantir@@A (data_rows.csv,
// GUI/AptPalantirConstructor.cpp); g_rva002eece0 was only a pin.
class AptPalantir;
extern AptPalantir *TheAptPalantir;
#define g_rva002eece0 ( *(Rva002EECE0 **)&TheAptPalantir )
#define g_bfmeDrawVHP ((AptPalantirGlobeRenderer *)g_rva002eece0)

// ?aptPalantirRenderGlobe@@YAXPBUPalantirPoint@@0@Z
void __cdecl aptPalantirRenderGlobe( const PalantirPoint *from, const PalantirPoint *to )
{
	g_bfmeDrawVHP->drawLine(
		(int)(from->x + 0.5f),
		(int)(from->y + 0.5f),
		(int)(to->x + 0.5f),
		(int)(to->y + 0.5f) );
}
