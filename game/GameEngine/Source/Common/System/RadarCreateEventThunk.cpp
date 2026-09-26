// The five-byte ILT at 0x00008B8E forwards to Radar::createEvent at 0x00108140.
// The Radar pin and the retail jump target prove the forwarded method identity.
// cl: /O2 /DNDEBUG /MD /EHs-c-

struct Coord3D;

enum RadarEventType
{
	RadarEventTypeDummy = 0
};

class Radar
{
public:
	void createEvent(const Coord3D *, RadarEventType, float);
};

class Rva00008B8ERadarCreateEventThunk
{
public:
	void forward(const Coord3D *, RadarEventType, float);
};

void Rva00008B8ERadarCreateEventThunk::forward(const Coord3D *world,
	RadarEventType type, float secondsToLive)
{
	((Radar *)this)->createEvent(world, type, secondsToLive);
}
