// ObjectCreationList::createInternal(const Object*, const Object*, unsigned),
// retail RVA 0x001D6810, 52 bytes. The named SlowDeathBehavior phase dispatcher
// selects its OCL and calls ILT 0x000160D1, which reaches this body. Zero Hour
// declares the same three-argument OCL creation path; BFME dispatches every
// element and has no Object* return value. The old BfmeThingFJ label carried
// the vector ABI only, not the recovered OCL identity.
class Object;

class ObjectCreationListElement
{
public:
	virtual void unknownSlot0(void) = 0;
	virtual void unknownSlot1(void) = 0;
	virtual void create(const Object *primary, const Object *secondary, unsigned int lifetimeFrames) = 0;
};

class ObjectCreationList
{
public:
	void createInternal(const Object *primary, const Object *secondary, unsigned int lifetimeFrames) const;

private:
	ObjectCreationListElement **m_begin;
	ObjectCreationListElement **m_end;
};

void ObjectCreationList::createInternal(const Object *primary, const Object *secondary, unsigned int lifetimeFrames) const
{
	ObjectCreationListElement **at = m_begin;

	while (at != m_end)
	{
		(*at)->create(primary, secondary, lifetimeFrames);

		++at;
	}
}
