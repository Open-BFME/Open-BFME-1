// BFME's object iterator checks an integer callback result, so this callback
// returns one to continue the walk.  The Zero Hour source still declares it
// void.  The target also sees the first override-chain step and the 2D center
// distance inline; these small local views expose the same source operations.
// Retail's sole pointer reference to this body is at 0x0020B946, inside the
// SpawnBehavior orphan-reclaim loop that constructs the matched OrphanData.

typedef unsigned int ObjectID;

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride != 0)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	const Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	bool isEquivalentTo(const ThingTemplate *other) const;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	const ThingTemplate *getTemplate() const
	{
		if (m_template == 0)
			return 0;
		return static_cast<const ThingTemplate *>(
			m_template->getFinalOverride());
	}

	const Coord3D *getPosition() const
	{
		return &m_position;
	}

	ObjectID getProducerID() const
	{
		return m_producerID;
	}

private:
	void *m_vtable;
	const ThingTemplate *m_template;
	unsigned char m_unreconstructed08[0x30];
	Coord3D m_position;
	unsigned char m_unreconstructed44[0x34];
	ObjectID m_producerID;
};

class OrphanData
{
public:
	const ThingTemplate *m_matchTemplate;
	Object *m_source;
	Object *m_closest;
	float m_closestDistSq;
};

int findClosestOrphan(Object *obj, void *userData)
{
	OrphanData *orphanData = static_cast<OrphanData *>(userData);

	if (!obj->getTemplate()->isEquivalentTo(orphanData->m_matchTemplate))
		return 1;
	if (obj->getProducerID() != 0)
		return 1;

	Object *source = orphanData->m_source;
	const Coord3D &sourcePosition = *source->getPosition();
	float dx = obj->getPosition()->x - sourcePosition.x;
	float dy = obj->getPosition()->y - sourcePosition.y;
	float distSq = dx * dx + dy * dy;

	if (distSq < orphanData->m_closestDistSq)
	{
		orphanData->m_closest = obj;
		orphanData->m_closestDistSq = distSq;
	}

	return 1;
}
