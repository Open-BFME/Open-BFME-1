// cl: /DNDEBUG /MD /EHsc
// BFME's retail 0x004A3B60 helper is a genuine null overlay body.  The
// 0x004AEC90 inventory callback pushes one Object* for this cdecl call and
// removes it with the overlay-draw arguments after the call.  Keep this
// recovered name tied to the reference ControlBar helper instead of using the
// generated placeholder's unsupported Gen_* identity.

class Image;
class Object;

class ControlBar
{

protected:
	static const Image *calculateVeterancyOverlayForObject(const Object *obj);
};

// ?calculateVeterancyOverlayForObject@ControlBar@@KAPBVImage@@PBVObject@@@Z
__declspec(noinline) const Image *ControlBar::calculateVeterancyOverlayForObject(const Object *)
{
	return 0;
}
