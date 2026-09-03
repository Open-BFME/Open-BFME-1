// cl: /DNDEBUG /MD /EHsc
//
// LaserUpdate helper — retail 0x00604460 (80B).
// If both drawable args are live, store their IDs at +0x4C/+0x50 and forward
// arg1, parent position, target position, arg4 into the 776-byte body at
// 0x00603FE0 (ILT 0x00024FC3).

struct Coord3D
{
	float x, y, z;
};

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};

class Drawable
{
public:
	DrawableID getID() const;
	const Coord3D *getPosition() const;
};

class LaserUpdate
{
public:
	void initFromDrawables(void *a, Drawable *parent, Drawable *target, void *d);

private:
	char m_pad00[0x4C];
	unsigned m_parentID;
	unsigned m_targetID;

	void initLaserInner(void *a, const Coord3D *parentPos, const Coord3D *targetPos, void *d);
};

// ?initFromDrawables@LaserUpdate@@QAEXPAXPAVDrawable@@1PAX@Z
void LaserUpdate::initFromDrawables(void *a, Drawable *parent, Drawable *target, void *d)
{
	if (parent)
	{
		if (target)
		{
			m_parentID = parent->getID();
			m_targetID = target->getID();
			initLaserInner(a, parent->getPosition(), target->getPosition(), d);
		}
	}
}
