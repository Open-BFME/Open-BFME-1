extern "C" long __ftol2( double value );

struct PalantirPoint
{
	float x;
	float y;
};

class AptPalantir
{
public:
	void renderMovie( int x0, int y0, int x1, int y1 ); // retail ILT 0x00018B0B; called via j_00018b0b below
};

extern void j_00018b0b();
typedef void (AptPalantir::*AptPalantirRenderMovieCall)( int x0, int y0, int x1, int y1 );

extern AptPalantir *TheAptPalantir;

// ?aptPalantirRenderMovie@@YAXPBUPalantirPoint@@0@Z
void __cdecl aptPalantirRenderMovie( const PalantirPoint *from, const PalantirPoint *to )
{
	union { void (*raw)(); AptPalantirRenderMovieCall member; } call;
	call.raw = j_00018b0b;
	(TheAptPalantir->*call.member)(
		(int)from->x,
		(int)from->y,
		(int)to->x,
		(int)to->y );
}
