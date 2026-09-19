// cl: /O2

typedef float Real;
typedef int Int;

struct Coord3D;

class View
{
public:
	virtual void resetCamera(const Coord3D *location, Int milliseconds,
		Real easeIn, Real easeOut);
};

// ?resetCamera@View@@UAEXPBUCoord3D@@HMM@Z
void View::resetCamera(const Coord3D *, Int, Real, Real)
{
}
