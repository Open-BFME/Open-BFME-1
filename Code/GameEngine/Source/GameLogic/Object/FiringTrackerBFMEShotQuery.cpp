// cl: /DNDEBUG /MD /EHsc

typedef int ObjectID;

class Coord3D
{
public:
	bool IsExactlyEqualTo(const Coord3D &that) const;

	float x;
	float y;
	float z;
};

class Object
{
public:
	ObjectID getID() const { return m_id; }

private:
	unsigned char m_unreconstructed_000[0x74];
	ObjectID m_id;
};

class FiringTracker
{
public:
	int bfmeGetNumConsecutiveShotsAtVictim(
		const Object *victim, const Coord3D *victimPosition) const;

private:
	unsigned char m_unreconstructed_000[0x20];
	int m_consecutiveShots;
	ObjectID m_victimID;
	Coord3D m_victimPosition;
	bool m_victimIsPosition;
};

int FiringTracker::bfmeGetNumConsecutiveShotsAtVictim(
	const Object *victim, const Coord3D *victimPosition) const
{
	if (victim == 0)
	{
		if (m_victimIsPosition && victimPosition != 0 &&
			m_victimPosition.IsExactlyEqualTo(*victimPosition))
			return m_consecutiveShots;
		return 0;
	}

	if (m_victimIsPosition || victim->getID() != m_victimID)
		return 0;

	return m_consecutiveShots;
}
