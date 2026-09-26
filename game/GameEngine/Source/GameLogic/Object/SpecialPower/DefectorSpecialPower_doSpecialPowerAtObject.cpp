// cl: /DNDEBUG /MD /EHsc
//
// DefectorSpecialPower::doSpecialPowerAtObject, retail RVA 0x0025A0E0.
// The Defector vtable routes this override through the special-power interface.
// The retail body rejects a disabled owner, a null target, and a null owner,
// then tail-calls SpecialPowerModuleInterface::doSpecialPowerAtObject.

class Object;

struct ObjectFields
{
	unsigned char m_pad00[0x1a4];
	int m_disabledMask;
};

class SpecialPowerModuleInterface
{
public:
	void doSpecialPowerAtObject(Object *target, unsigned int commandOptions);
};

class DefectorSpecialPower
{
public:
	Object *getObject() const
	{
		return *(Object **)((char *)this - 8);
	}

	virtual void doSpecialPowerAtObject(Object *target, unsigned int commandOptions);
};

void DefectorSpecialPower::doSpecialPowerAtObject(Object *target,
	unsigned int commandOptions)
{
	ObjectFields *owner = (ObjectFields *)getObject();
	if (owner->m_disabledMask != 0)
		return;
	if (target == 0)
		return;
	const Object *self = getObject();
	if (self == 0)
		return;
	((SpecialPowerModuleInterface *)this)->doSpecialPowerAtObject(target, commandOptions);
}
