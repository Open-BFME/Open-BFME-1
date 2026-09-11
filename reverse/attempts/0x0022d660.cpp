// ?update@TransportContain@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.75 date=2026-09-11
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned char Bool;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 0 };

class Object;

struct ContainedNode
{
	ContainedNode *m_next;
	ContainedNode *m_previous;
	Object *m_object;
};

struct ContainedItemsList
{
	ContainedNode *m_head;
};

class ContainModuleInterface
{
public:
	ContainedItemsList *getContainedItemsList()
	{
		typedef ContainedItemsList *(ContainModuleInterface::*Call)();
		union { void *raw; Call method; } call;
		call.raw = (*(void ***)this)[65];
		return (this->*call.method)();
	}
};

class BodyModuleInterface
{
public:
	float getHealth()
	{
		typedef float (BodyModuleInterface::*Call)();
		union { void *raw; Call method; } call;
		call.raw = (*(void ***)this)[4];
		return (this->*call.method)();
	}

	float getMaxHealth()
	{
		typedef float (BodyModuleInterface::*Call)();
		union { void *raw; Call method; } call;
		call.raw = (*(void ***)this)[6];
		return (this->*call.method)();
	}
};

extern void j_0002191d();

class Object
{
public:
	void attemptHealing(float amount, Object *source)
	{
		typedef void (Object::*Call)(float, Object *);
		union { void *raw; Call method; } call;
		call.raw = (*(void ***)this)[16];
		(this->*call.method)(amount, source);
	}

	void notifyModelConditionChange()
	{
		typedef void (Object::*Call)();
		union { void *raw; Call method; } call;
		call.raw = (void *)j_0002191d;
		(this->*call.method)();
	}

	void *m_vtable;
	unsigned char m_unknown004[0x110];
	unsigned int m_ownerStatusBits;
	unsigned int m_passengerStatusBits;
	unsigned char m_unknown11c[0xe0];
	ContainModuleInterface *m_contain;
	BodyModuleInterface *m_body;
};

struct TransportContainModuleData
{
	unsigned char m_unknown000[0x178];
	float m_healthRegen;
};

class OpenContain
{
public:
	virtual UpdateSleepTime update();
};

class TransportContain : public OpenContain
{
public:
	virtual UpdateSleepTime update();

private:
	TransportContainModuleData *getModuleData() const
	{
		return *(TransportContainModuleData *const *)((const char *)this - 0xc);
	}

	Object *getObject() const
	{
		return *(Object *const *)((const char *)this - 8);
	}

	unsigned char m_unknown004[0xcc];
	Bool m_propagatedCondition;
};

UpdateSleepTime TransportContain::update()
{
	TransportContainModuleData *moduleData = getModuleData();
	if (moduleData != 0 && moduleData->m_healthRegen > *(const float *)0x01075350)
	{
		ContainModuleInterface *contain = getObject()->m_contain;
		if (contain != 0)
		{
			ContainedItemsList *items = contain->getContainedItemsList();
			if (items != 0)
			{
				ContainedNode *it = items->m_head->m_next;
				while (it != items->m_head)
				{
					Object *passenger = it->m_object;
					BodyModuleInterface *body = passenger->m_body;
					it = it->m_next;
					if (body->getHealth() < body->getMaxHealth())
					{
						float regen = body->getMaxHealth() *
							*(const float *)0x012aee3c * moduleData->m_healthRegen *
							*(const float *)0x01076c24;
						passenger->attemptHealing(regen, getObject());
					}
				}
			}
		}
	}

	Bool ownerCondition = (getObject()->m_ownerStatusBits & 0x10000000) != 0;
	if (m_propagatedCondition != ownerCondition)
	{
		m_propagatedCondition = ownerCondition;
		ContainModuleInterface *contain = getObject()->m_contain;
		if (contain != 0)
		{
			ContainedItemsList *items = contain->getContainedItemsList();
			if (items != 0)
			{
				ContainedNode *it = items->m_head->m_next;
				while (it != items->m_head)
				{
					Object *passenger = it->m_object;
					if (passenger != 0)
					{
						unsigned int bits = passenger->m_passengerStatusBits;
						if (m_propagatedCondition)
							bits |= 0x01000000;
						else
							bits &= 0xfeffffff;
						if (bits != passenger->m_passengerStatusBits)
						{
							passenger->m_passengerStatusBits = bits;
							passenger->notifyModelConditionChange();
						}
					}
					it = it->m_next;
				}
			}
		}
	}

	return OpenContain::update();
}
