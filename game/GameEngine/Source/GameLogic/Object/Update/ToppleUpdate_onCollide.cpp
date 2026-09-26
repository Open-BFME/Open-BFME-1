// cl: /DNDEBUG /MD /EHsc

// ?onCollide@ToppleUpdate@@UAEXPAVObject@@PBUCoord3D@@1@Z
// Retail RVA 0x002B12C0, 161 bytes.  The collide interface is the secondary
// ToppleUpdate subobject; its owning Object pointer is at this-0x18.  BFME
// Matched constructor2B1060 stores Collide vtableVA10C4E20 at+20;
// slot0 is ILT28948 to thisbody. Fullret12 at2B135E ends2B1361.
// The complete object owner pointer is+8, hence interface-this minus18.
// BFME compares the incoming crusher against the owner's runtime crushable level,
// then uses the colliding object's preferred locomotor height as topple speed.

typedef bool Bool;
typedef float Real;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

extern const Real BfmeZeroRange;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object
{
public:
	UnsignedByte getCrusherLevel() const;
	UnsignedByte getCrushableLevel() const;
	Real bfmeGetNonnegativePreferredLocomotorHeight() const;
	void topple(const Coord3D *direction, Real speed, UnsignedInt options);

	const Coord3D *getPosition() const
	{
		return &m_position;
	}

private:
	unsigned char m_unmodelled_000[0x38];
	Coord3D m_position;
	unsigned char m_unmodelled_044[0x214 - 0x44];

public:
	Object *m_containedBy;
};

typedef char Coord3DSize12[(sizeof(Coord3D) == 12) ? 1 : -1];
typedef char ObjectViewSize218[(sizeof(Object) == 0x218) ? 1 : -1];

class ToppleUpdate
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc,
		const Coord3D *normal);

protected:
	Object *getObject() const
	{
		return *(Object *const *)((const char *)this - 0x18);
	}
};

void ToppleUpdate::onCollide(Object *other, const Coord3D *, const Coord3D *)
{
	if (other == 0)
		return;

	const UnsignedByte crusherLevel = other->getCrusherLevel();
	if ((signed char)crusherLevel >
		(signed char)getObject()->getCrushableLevel())
	{
		Coord3D toppleVector;
		const Coord3D *position = getObject()->getPosition();
		toppleVector.x = position->x;
		toppleVector.y = position->y;
		toppleVector.x -= other->getPosition()->x;
		toppleVector.y -= other->getPosition()->y;
		toppleVector.z = 0.0f;

		Real toppleSpeed = other->bfmeGetNonnegativePreferredLocomotorHeight();
		if (toppleSpeed == BfmeZeroRange && other->m_containedBy != 0)
			toppleSpeed = other->m_containedBy->bfmeGetNonnegativePreferredLocomotorHeight();

		getObject()->topple(&toppleVector, toppleSpeed, 0);
	}
}
