// cl: /DNDEBUG /MD /EHsc

typedef int Bool;

class W3DRopeDraw
{
public:
	virtual void setShadowsEnabled(Bool enable);
};

// W3DRopeDraw's primary vtable slot points through ILT 0x0000DFC6 to
// 0x0075A550. The override is intentionally empty: rope lines cast no shadow.
void W3DRopeDraw::setShadowsEnabled(Bool enable)
{
}
