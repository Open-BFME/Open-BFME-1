// cl: /DNDEBUG /MD /EHsc

class Weapon;
class Object;

class ThingTemplate
{
public:
	char m_fields[0xd4];
	unsigned int m_kindOf;
};

class Overridable
{
public:
	Overridable *getFinalOverride();
};

struct ObjectTemplateHandle
{
	char m_fields[4];
	Overridable *m_template;
};

class Object
{
public:
	char m_fields[4];
	ObjectTemplateHandle *m_templateHandle;
};

class PreFireHook
{
public:
	virtual ~PreFireHook() {}
	virtual bool accepts(Weapon *weapon, const Object *object) = 0;
	virtual void slot08() = 0;
	virtual void notify(Weapon *weapon, const Object *object) = 0;
};

struct PreFireHookNode
{
	PreFireHookNode *m_next;
	PreFireHookNode *m_previous;
	PreFireHook *m_hook;
};

class WeaponTemplate
{
public:
	void notifyPreFire(Weapon *weapon, int weaponSlot,
		const Object *object, int commandSource);

private:
	char m_fields[0x538];
	PreFireHookNode *m_preFireHooks;
};

void WeaponTemplate::notifyPreFire(Weapon *weapon, int weaponSlot,
	const Object *object, int commandSource)
{
	for (PreFireHookNode *node = m_preFireHooks->m_next;
		node != m_preFireHooks; node = node->m_next)
	{
		PreFireHook *hook = node->m_hook;
		if (object)
		{
			ThingTemplate *objectTemplate =
				reinterpret_cast<ThingTemplate *>(object->m_templateHandle);
			if (objectTemplate)
			{
				Overridable *overridable = object->m_templateHandle->m_template;
				if (overridable)
				{
					objectTemplate = reinterpret_cast<ThingTemplate *>(
						overridable->getFinalOverride());
				}
			}
			if ((objectTemplate->m_kindOf & 0x00100000) != 0
				&& hook->accepts(weapon, object))
			{
				hook->notify(weapon, object);
			}
		}
	}
}
