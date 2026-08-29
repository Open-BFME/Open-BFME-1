// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Object;

class ContainModuleInterface
{
};

class ObjectModuleBase
{
public:
	virtual void objectModuleSlot0() = 0;

protected:
	void *m_moduleData;
	Object *m_object;

	friend class Object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorSlot0() = 0;
	virtual void behaviorSlot1() = 0;
	virtual ContainModuleInterface *getContain() = 0;
};

class BehaviorModule : public ObjectModuleBase, public BehaviorModuleInterface
{
};

class Object
{
public:
	void bfmeSwapContainModule(Object *other);

private:
	unsigned char m_pad000[0x1f0];
	BehaviorModule **m_behaviors;
	unsigned char m_pad1f4[8];
	ContainModuleInterface *m_contain;
};

void Object::bfmeSwapContainModule(Object *other)
{
	BehaviorModule **mine = m_behaviors;
	while (*mine != 0)
	{
		if ((*mine)->getContain() == m_contain)
			break;
		++mine;
	}

	BehaviorModule **theirs = other->m_behaviors;
	while (*theirs != 0)
	{
		if ((*theirs)->getContain() == other->m_contain)
			break;
		++theirs;
	}

	if (*theirs != 0)
	{
		BehaviorModule *temporary = *mine;
		*mine = *theirs;
		*theirs = temporary;

		ContainModuleInterface *temporaryContain = m_contain;
		m_contain = other->m_contain;
		other->m_contain = temporaryContain;

		(*mine)->m_object = this;
		(*theirs)->m_object = other;
	}
}
