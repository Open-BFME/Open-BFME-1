// The five-byte ILT at 0x00004D59 forwards to Radar::localPixelToRadar at
// 0x00107AB0. The Radar symbol pin and retail jump target prove the route.
// cl: /O2 /DNDEBUG /MD /EHs-c-

struct ICoord2D;

class Radar
{
public:
	bool localPixelToRadar(const ICoord2D *, ICoord2D *);
};

class Rva00004D59RadarLocalPixelToRadarThunk
{
public:
	bool forward(const ICoord2D *pixel, ICoord2D *radar);
};

bool Rva00004D59RadarLocalPixelToRadarThunk::forward(
	const ICoord2D *pixel, ICoord2D *radar)
{
	return ((Radar *)this)->localPixelToRadar(pixel, radar);
}
