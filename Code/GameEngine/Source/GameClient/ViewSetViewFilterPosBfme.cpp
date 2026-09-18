// cl: /DNDEBUG /MD /EHsc
// BFME adds an immediate flag to View::setViewFilterPos.

typedef bool Bool;

struct Coord3D;

class View
{
public:
	virtual void setViewFilterPos(const Coord3D *position, Bool immediate);
};

// The CAMERA_MOTION_BLUR_JUMP caller uses View vtable slot 45 at +0xb4.
// Retail 0x0045BC00 is the empty ret-8 body for that slot.
void View::setViewFilterPos(const Coord3D *, Bool)
{
}
