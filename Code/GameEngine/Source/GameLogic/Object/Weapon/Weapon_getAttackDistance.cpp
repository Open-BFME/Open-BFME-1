// cl: /DNDEBUG /MD /EHsc

typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }

private:
	char m_fields[0x38];
	Coord3D m_position;
	char m_geometryFields[0x7c];
	Real m_boundingCircleRadius;
};

class Weapon
{
public:
	Real getAttackRange(const Object *source, Real heightDifference) const;
	Real getAttackDistance(const Object *source, const Object *victim,
		const Coord3D *victimPosition) const;
};

Real Weapon::getAttackDistance(const Object *source, const Object *victim,
	const Coord3D *victimPosition) const
{
	if (victim)
	{
		Real range = getAttackRange(source,
			victim->getPosition()->z - source->getPosition()->z);
		range += source->getBoundingCircleRadius();
		range += victim->getBoundingCircleRadius();
		return range;
	}

	if (victimPosition)
		return getAttackRange(source,
			victimPosition->z - source->getPosition()->z);

	return getAttackRange(source, 0.0f);
}
