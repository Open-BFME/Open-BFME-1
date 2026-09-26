// ?update@TransportContain@@UAE?AW4UpdateSleepTime@@XZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
#include <bitset>

// TransportContain::update, retail RVA 0x0022D660 (365 bytes).
// Identity: TransportContain UpdateModule vtable 0x00CAD410 slot 0,
// and the HordeTransportContain and RiderChangeContain update tail callers.
// The health-regeneration loop extends the pristine Zero Hour implementation;
// BFME additionally mirrors the owner's model-condition bit 60 to passenger
// bit 88 when the cached condition changes.
// BitFlags::set(i, value), including its STLport wrapper, preserves the retail
// test-before-write and mask allocation. reset(i) has a different code shape.
extern float Rva012AEE3CTransportHealthRegenScale;


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
 virtual void slot00() = 0;
 virtual void slot01() = 0;
 virtual void slot02() = 0;
 virtual void slot03() = 0;
 virtual void slot04() = 0;
 virtual void slot05() = 0;
 virtual void slot06() = 0;
 virtual void slot07() = 0;
 virtual void slot08() = 0;
 virtual void slot09() = 0;
 virtual void slot10() = 0;
 virtual void slot11() = 0;
 virtual void slot12() = 0;
 virtual void slot13() = 0;
 virtual void slot14() = 0;
 virtual void slot15() = 0;
 virtual void slot16() = 0;
 virtual void slot17() = 0;
 virtual void slot18() = 0;
 virtual void slot19() = 0;
 virtual void slot20() = 0;
 virtual void slot21() = 0;
 virtual void slot22() = 0;
 virtual void slot23() = 0;
 virtual void slot24() = 0;
 virtual void slot25() = 0;
 virtual void slot26() = 0;
 virtual void slot27() = 0;
 virtual void slot28() = 0;
 virtual void slot29() = 0;
 virtual void slot30() = 0;
 virtual void slot31() = 0;
 virtual void slot32() = 0;
 virtual void slot33() = 0;
 virtual void slot34() = 0;
 virtual void slot35() = 0;
 virtual void slot36() = 0;
 virtual void slot37() = 0;
 virtual void slot38() = 0;
 virtual void slot39() = 0;
 virtual void slot40() = 0;
 virtual void slot41() = 0;
 virtual void slot42() = 0;
 virtual void slot43() = 0;
 virtual void slot44() = 0;
 virtual void slot45() = 0;
 virtual void slot46() = 0;
 virtual void slot47() = 0;
 virtual void slot48() = 0;
 virtual void slot49() = 0;
 virtual void slot50() = 0;
 virtual void slot51() = 0;
 virtual void slot52() = 0;
 virtual void slot53() = 0;
 virtual void slot54() = 0;
 virtual void slot55() = 0;
 virtual void slot56() = 0;
 virtual void slot57() = 0;
 virtual void slot58() = 0;
 virtual void slot59() = 0;
 virtual void slot60() = 0;
 virtual void slot61() = 0;
 virtual void slot62() = 0;
 virtual void slot63() = 0;
 virtual void slot64() = 0;
 virtual ContainedItemsList *getContainedItemsList() = 0;
};

class BodyModuleInterface
{
public:
 virtual void slot00() = 0;
 virtual void slot01() = 0;
 virtual void slot02() = 0;
 virtual void slot03() = 0;
 virtual float getHealth() = 0;
 virtual void slot05() = 0;
 virtual float getMaxHealth() = 0;
};

template<int N> class BitFlags
{
public:
 _STL::bitset<N> m_bits;
 Bool test(int i) const { return m_bits.test(i); }
 void set(int i, int value=1) { m_bits.set(i,value); }
};
class Object
{
public:
 virtual void slot00() = 0;
 virtual void slot01() = 0;
 virtual void slot02() = 0;
 virtual void slot03() = 0;
 virtual void slot04() = 0;
 virtual void slot05() = 0;
 virtual void slot06() = 0;
 virtual void slot07() = 0;
 virtual void slot08() = 0;
 virtual void slot09() = 0;
 virtual void slot10() = 0;
 virtual void slot11() = 0;
 virtual void slot12() = 0;
 virtual void slot13() = 0;
 virtual void slot14() = 0;
 virtual void slot15() = 0;
 virtual void attemptHealing(float amount, Object *source) = 0;
 void notifyModelConditionChanged();
 unsigned char m_unknown004[0x10c];
 BitFlags<128> m_conditions;
 unsigned char m_unknown120[0xdc];
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

#pragma comment(linker, "/alternatename:?update@OpenContain@@UAE?AW4UpdateSleepTime@@XZ=?j_0000c1e9@@YAXXZ")

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
	if (moduleData != 0 && moduleData->m_healthRegen != 0.0f)
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
							Rva012AEE3CTransportHealthRegenScale * moduleData->m_healthRegen / 100.0f;
						passenger->attemptHealing(regen, getObject());
					}
				}
			}
		}
	}

	Bool ownerCondition = getObject()->m_conditions.test(60);
	if (m_propagatedCondition && !ownerCondition)
        m_propagatedCondition = false;
    else if (!m_propagatedCondition && ownerCondition)
        m_propagatedCondition = true;
    else
        goto finished;
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
					if (passenger != 0)
					{
                        if (m_propagatedCondition)
                        {
                            if (!passenger->m_conditions.test(88))
                            {
                                passenger->m_conditions.set(88);
                                passenger->notifyModelConditionChanged();
                            }
                        }
                        else
                        {
                            if (passenger->m_conditions.test(88))
                            {
                                passenger->m_conditions.set(88, 0);
                                passenger->notifyModelConditionChanged();
                            }
                        }
					}
					it = it->m_next;
				}
			}
		}
	}

finished:
	return OpenContain::update();
}
