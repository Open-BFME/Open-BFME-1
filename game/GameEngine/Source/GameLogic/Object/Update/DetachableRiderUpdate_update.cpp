// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// DetachableRiderUpdate::update, retail 0x0028DFF0, 720 bytes; slot 0 of the class's
// +0x10 vtable 0x010BDBBC (installed by ctor 0x0028D580) reaches it through ILT 0x00013EE9.

#include "ascii_string.h"
#include <string.h>
#include <vector>

typedef unsigned int UnsignedInt;
typedef int Int;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum DisabledType
{
	DISABLED_DETACHABLE_RIDER = 4
};

enum CommandSourceType
{
	COMMAND_SOURCE_AI = 2
};

// Bit indices read off the retail masks: status word 1 bit 6, condition word 8 bit 8.
enum
{
	OBJECT_STATUS_BIT_38 = 38,
	MODELCONDITION_BIT_264 = 264
};

template <int NUMBITS>
class BitFlags
{
public:
	BitFlags(Int bit)
	{
		memset(m_bits, 0, sizeof(m_bits));
		m_bits[bit >> 5] |= 1 << (bit & 31);
	}
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

// 320-bit model-condition mask, zeroed wholesale like the 0x0028DDC0 parser's.
class BfmeConditionFlags
{
public:
	BfmeConditionFlags()
	{
		memset(m_bits, 0, sizeof(m_bits));
	}
	UnsignedInt m_bits[10];
};

class S4Sink004135C0
{
public:
	void invoke(const AsciiString &name, bool active, Int a, Int b, Int c);
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType source);
};

class Object;

class ObjectCreationList
{
public:
	void createInternal(const Object *primary, const Object *secondary, UnsignedInt frame) const;
};

class BfmeUnitCN
{
public:
	bool bfmeDoneCN();
};

class BfmeItem1005
{
public:
	void bfmeDoD1005(Int value);
};

class RiderCarrier;

class Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual S4Sink004135C0 *getSink();

	bool clearDisabled(DisabledType type);
	void clearAndSetModelConditionFlags(const BfmeConditionFlags &clear,
		const BfmeConditionFlags &set);
	void setWeaponLock(Int weaponSlot, Int lockType);
	void setStatus(const BitFlags<86> &status, bool set);
	void notifyModelConditionChanged();
	RiderCarrier *getContain() const { return m_contain; }

	struct ModelConditionFlags
	{
		UnsignedInt test(Int i) const { return m_bits[i >> 5] & (1u << (i & 31)); }
		void set(Int i) { m_bits[i >> 5] |= (1u << (i & 31)); }
		void reset(Int i) { m_bits[i >> 5] &= ~(1u << (i & 31)); }
		UnsignedInt m_bits[10];
	};

	unsigned char m_pad000[0x110 - 4];
	ModelConditionFlags m_modelConditionFlags;
	unsigned char m_pad138[0x1fc - 0x138];
	RiderCarrier *m_contain;
	unsigned char m_pad200[0x204 - 0x200];
	AICommandInterface *m_ai;
	unsigned char m_pad208[0x214 - 0x208];
	Object *m_containedBy;
};

class RiderFlagObject
{
public:
	unsigned char m_pad000[0x94];
	unsigned char m_riderFlag94;
};

class RiderAction
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void apply(Object *object) = 0;
};

class RiderListNode
{
public:
	RiderListNode *m_next;
	unsigned char m_pad04[4];
	Object *m_object;
};

class RiderList
{
public:
	RiderListNode *m_sentinel;
};

class RiderCarrier
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5c() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual RiderAction *getRiderAction() = 0;
	virtual void slot6c() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7c() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8c() = 0;
	virtual void notifyRider(Object *object, Int mode) = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual void slot9c() = 0;
	virtual void slota0() = 0;
	virtual void slota4() = 0;
	virtual void slota8() = 0;
	virtual void slotac() = 0;
	virtual void slotb0() = 0;
	virtual void slotb4() = 0;
	virtual void slotb8() = 0;
	virtual void slotbc() = 0;
	virtual void slotc0() = 0;
	virtual void slotc4() = 0;
	virtual void slotc8() = 0;
	virtual void slotcc() = 0;
	virtual void slotd0() = 0;
	virtual void slotd4() = 0;
	virtual void slotd8() = 0;
	virtual void slotdc() = 0;
	virtual void slote0() = 0;
	virtual void slote4() = 0;
	virtual void slote8() = 0;
	virtual void slotec() = 0;
	virtual void slotf0() = 0;
	virtual void slotf4() = 0;
	virtual void slotf8() = 0;
	virtual void slotfc() = 0;
	virtual Int getRiderCount(Int mode) = 0;
	virtual RiderList *getRiderList() = 0;
};

// 48-byte rider record (AnimState, AnimTime, RiderOCL) parsed by 0x0028DDC0.
class DetachableRiderRecord
{
public:
	BfmeConditionFlags m_conditionData;
	UnsignedInt m_animTime;
	const ObjectCreationList *m_riderOCL;
};

class DetachableRiderUpdateModuleData
{
public:
	unsigned char m_pad000[8];
	std::vector<DetachableRiderRecord> m_riderRecords;
	std::vector<AsciiString> m_riderSubObjects;
	Int m_weaponLock;
	bool m_ejectRiderIfApplicable;
	bool m_riderlessDeathChance;
};

class GameLogic
{
public:
	void deselectObject(Object *object, unsigned short playerMask, bool affectClient);
};

extern GameLogic *TheGameLogic;

class DetachableRiderUpdate
{
public:
	virtual UpdateSleepTime update();
	DetachableRiderUpdateModuleData *getData() const
	{
		return *(DetachableRiderUpdateModuleData **)((char *)this - 0x0c);
	}
	Object *getObject() const
	{
		return *(Object **)((char *)this - 0x08);
	}
	unsigned char m_pad000[0x0c];
	unsigned char m_flag20;
	unsigned char m_flag21;
};

// ?update@DetachableRiderUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime DetachableRiderUpdate::update()
{
	DetachableRiderUpdateModuleData *data = getData();
	Object *object = getObject();
	S4Sink004135C0 *sink = object->getSink();
	object->clearDisabled(DISABLED_DETACHABLE_RIDER);

	if (m_flag20)
	{
		if (sink)
		{
			for (UnsignedInt i = 0; i < data->m_riderSubObjects.size(); ++i)
				sink->invoke(data->m_riderSubObjects[i], false, 0, 0, 0);
		}

		if (data->m_riderRecords[m_flag21].m_riderOCL)
			data->m_riderRecords[m_flag21].m_riderOCL->createInternal(object, object, 0);

		object->clearAndSetModelConditionFlags(
			data->m_riderRecords[m_flag21].m_conditionData, BfmeConditionFlags());
		object->setWeaponLock(data->m_weaponLock, 2);
		object->setStatus(BitFlags<86>(OBJECT_STATUS_BIT_38), true);

		if (!object->m_modelConditionFlags.test(MODELCONDITION_BIT_264))
		{
			object->m_modelConditionFlags.set(MODELCONDITION_BIT_264);
			object->notifyModelConditionChanged();
		}

		if (data->m_riderlessDeathChance)
		{
			Object *container = object->m_containedBy;
			if (container)
			{
				RiderAction *action;
				if (container->getContain() && (action = container->getContain()->getRiderAction()) != 0)
					action->apply(object);
				else if (container->getContain())
					container->getContain()->notifyRider(object, 0);

				if (object->m_ai)
				{
					AICommandInterface *ai =
						(AICommandInterface *)((unsigned char *)object->m_ai + 0x20);
					ai->aiIdle(COMMAND_SOURCE_AI);
				}
			}
			TheGameLogic->deselectObject(object, 0xffff, true);
			return UPDATE_SLEEP_FOREVER;
		}

		if (data->m_ejectRiderIfApplicable)
		{
			Object *container = object->m_containedBy;
			if (container != 0)
			{
				if (container->getContain() && container->getContain()->getRiderAction())
				{
					Int expected = container->getContain()->getRiderCount(0);
					Int matching = 0;
					RiderList *list = container->getContain()->getRiderList();
					RiderListNode *it;
					for (it = list->m_sentinel->m_next; it != list->m_sentinel; it = it->m_next)
					{
						if ((reinterpret_cast<RiderFlagObject *>(it->m_object)->m_riderFlag94 & 0x40) != 0)
							++matching;
					}

					if (matching == expected)
					{
						for (it = list->m_sentinel->m_next; it != list->m_sentinel; )
						{
							Object *rider = it->m_object;
							it = it->m_next;
							((BfmeUnitCN *)rider)->bfmeDoneCN();
						}
						return UPDATE_SLEEP_FOREVER;
					}
				}
			}
			else
			{
				((BfmeUnitCN *)object)->bfmeDoneCN();
				return UPDATE_SLEEP_FOREVER;
			}
		}
	}
	else
	{
		if (sink)
		{
			for (UnsignedInt i = 0; i < data->m_riderSubObjects.size(); ++i)
				sink->invoke(data->m_riderSubObjects[i], true, 0, 0, 0);
		}

		((BfmeItem1005 *)object)->bfmeDoD1005(2);
		object->setStatus(BitFlags<86>(OBJECT_STATUS_BIT_38), false);

		if (object->m_modelConditionFlags.test(MODELCONDITION_BIT_264))
		{
			object->m_modelConditionFlags.reset(MODELCONDITION_BIT_264);
			object->notifyModelConditionChanged();
		}
	}

	return UPDATE_SLEEP_FOREVER;
}
