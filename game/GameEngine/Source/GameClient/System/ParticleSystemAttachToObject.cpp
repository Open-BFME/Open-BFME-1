// cl: /DNDEBUG /MD /EHsc
// Open-BFME: ParticleSystem::attachToObject, retail 0x005BE170 (33 bytes).
// The ILT at 0x00013C82 and its matched tossEmitters caller prove identity.

typedef unsigned int ObjectID;

class Object
{
public:
	ObjectID getID() const { return m_id; }

private:
	unsigned char m_unmodelled_000[0x74];
	ObjectID m_id;
};

class ParticleSystem
{
public:
	void attachToObject(const Object *object);

private:
	unsigned char m_unmodelled_000[0xB8];
	ObjectID m_attachedToObjectID;
};

void ParticleSystem::attachToObject(const Object *object)
{
	if (object)
	{
		m_attachedToObjectID = object->getID();
		return;
	}

	m_attachedToObjectID = 0;
}
