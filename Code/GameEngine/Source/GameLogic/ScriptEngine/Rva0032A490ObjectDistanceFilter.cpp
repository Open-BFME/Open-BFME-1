// BFME object-distance visitor at retail 0x0032A490.
//
// Player::iterateObjects calls this visitor for the condition that counts a
// player's objects beyond a supplied distance.  The visitor keeps objects
// whose final template passes the BFME template predicate, then stops the
// walk after the count exceeds the inclusive limit.

typedef float Real;
typedef int Int;

class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
	const Overridable *getFinalOverride() const;
};

class ThingTemplate : public Overridable
{
public:
	bool bfmeTemplatePredicate() const;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) {}

	void sub(const Coord3D *other)
	{
		x -= other->x;
		y -= other->y;
		z -= other->z;
	}

	Real lengthSqr(void) const
	{
		return x * x + y * y + z * z;
	}
};

class Object
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_padding[0x30];
	Coord3D m_position;
};

struct Rva0032A490Context
{
	Coord3D m_center;
	Real m_radiusSquared;
	Int m_count;
	Int m_maxCount;
};

int rva0032a490(Object *object, Rva0032A490Context *context)
{
	ThingTemplate *thingTemplate = object->m_template;
	if (thingTemplate == 0)
		goto failure;

	Overridable *nextOverride = thingTemplate->m_nextOverride;
	ThingTemplate *finalTemplate = thingTemplate;
	if (nextOverride != 0)
		finalTemplate = (ThingTemplate *)nextOverride->getFinalOverride();
	if (finalTemplate == 0)
		goto failure;
	if (!finalTemplate->bfmeTemplatePredicate())
		goto failure;

	Coord3D delta = object->m_position;
	delta.sub(&context->m_center);
	Real distanceSquared = delta.lengthSqr();
	if (!(distanceSquared > context->m_radiusSquared))
		goto failure;

	++context->m_count;
	if (context->m_count > context->m_maxCount)
		return 0;

failure:
	return 1;
}
