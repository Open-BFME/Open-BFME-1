// BFME's ExperienceTracker value query.  The ally guard and its typed
// Object::getRelationship call uniquely locate this body at 0x001B1FC0.

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Object
{
public:
	Relationship getRelationship(const Object *that) const;
};

class ExperienceTracker
{
public:
	int getExperienceValue(const Object *killer) const;

private:
	void *m_vtable;
	Object *m_parent;
	char m_unreconstructed08[8];
	int m_currentLevel;
	int m_unreconstructed14;
};

int ExperienceTracker::getExperienceValue(const Object *killer) const
{
	if (killer->getRelationship(m_parent) == ALLIES)
		return 0;

	int value = m_unreconstructed14;
	if (value == -1)
		value = m_currentLevel;
	return value;
}
