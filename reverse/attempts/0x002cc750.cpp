// ?onDockReached@DockUpdate@@UAEXPAVObject@@@Z
// partial score=0.951 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME: DockUpdate::onDockReached, retail 0x002CC750.
//
// The DockUpdateInterface vtable slot pin, the AIDock caller, and the
// Zero Hour DockUpdate implementation establish the method identity.  The
// BFME Object model-condition mask has its 0x20000/0x40000 word at +0x118;
// the retail helper deliberately writes the cleared and set masks separately.

class Object
{
public:
	void notifyModelConditionChanged(void);

	unsigned char m_unmodelled000[0x118];
	volatile unsigned int m_modelConditionFlagsWord;
};

static __forceinline void applyDockCondition(Object *object)
{
	unsigned int flags = object->m_modelConditionFlagsWord;
	if ((flags & 0x20000) != 0 || (flags & 0x40000) == 0)
	{
		unsigned int set;
		unsigned int cleared = object->m_modelConditionFlagsWord & 0xfffdffff;
		set = cleared | 0x40000;
		object->m_modelConditionFlagsWord = cleared;
		object->m_modelConditionFlagsWord = set;
		object->notifyModelConditionChanged();
	}
}

class DockUpdate
{
public:
	virtual void onDockReached(Object *docker);
};

void DockUpdate::onDockReached(Object *docker)
{
	applyDockCondition(*(Object **)((char *)this - 0x18));
	applyDockCondition(docker);
}
