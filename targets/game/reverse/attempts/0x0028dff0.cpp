// ?update@DetachableRiderUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.45 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// DetachableRiderUpdate::update, retail 0x0028DFF0, 720 bytes.
//
// The retail entry is the UpdateModuleInterface subobject at complete-object
// offset +0x10.  Consequently the module-data and ObjectModule pointers are
// at this-0x0c and this-0x08, while the two per-instance flags are at +0x10
// and +0x11 in this interface view.  The module-data record array is a
// 0x30-byte BFME extension; its +0x2c field is the optional rider OCL.

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

template <int NUMBITS>
class BitFlags
{
public:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

class AsciiString
{
public:
	unsigned char m_data[4];
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

class BfmeSubBPB
{
public:
	void bfmeDoBPB(void *a, void *b, void *c);
};

class BfmeUnitCN
{
public:
	void bfmeDoneCN();
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
	void clearAndSetModelConditionFlags(const BitFlags<320> &clear,
		const BitFlags<320> &set);
	void setWeaponLock(Int weaponSlot, Int lockType);
	void setStatus(const BitFlags<86> &status, bool set);
	void notifyModelConditionChanged();

	unsigned char m_pad000[0x130 - 4];
	UnsignedInt m_modelConditionFlags;
	unsigned char m_pad134[0x1fc - 0x134];
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
	virtual void slot90() = 0;
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

class DetachableRiderRecord
{
public:
	unsigned char m_conditionData[0x2c];
	BfmeSubBPB *m_riderOCL;
};

class DetachableRiderUpdateModuleData
{
public:
	unsigned char m_pad000[8];
	DetachableRiderRecord *m_riderRecords;
	unsigned char m_pad00c[8];
	AsciiString *m_riderSubObjectsBegin;
	AsciiString *m_riderSubObjectsEnd;
	unsigned char m_pad01c[4];
	Int m_weaponLock;
	bool m_ejectRiderIfApplicable;
	bool m_riderlessDeathChance;
};

union DetachableRiderLocalFlags
{
	BitFlags<320> m_modelConditions;
	BitFlags<86> m_status;
};

class BfmeItem1005
{
public:
	void bfmeDoD1005(Int value);
};

class GameLogic
{
public:
	void deselectObject(Object *object, unsigned short playerMask, bool affectClient);
};

#define TheGameLogic (*(GameLogic **)0x012f0898)

class DetachableRiderUpdate
{
public:
	virtual UpdateSleepTime update();
	unsigned char m_pad000[0x0c];
	unsigned char m_flag20;
	unsigned char m_flag21;
};

// ?update@DetachableRiderUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime DetachableRiderUpdate::update()
{
	register S4Sink004135C0 *sink;
	DetachableRiderUpdate *update = this;
	unsigned char *self = (unsigned char *)update;
	DetachableRiderUpdateModuleData *data =
		*(DetachableRiderUpdateModuleData * volatile *)(self - 0x0c);
	Object *object = *(Object * volatile *)(self - 0x08);
	sink = object->getSink();
	object->clearDisabled(DISABLED_DETACHABLE_RIDER);

	if (update->m_flag20 != 0)
	{
		if (sink != 0)
		{
			for (Int i = 0; i < data->m_riderSubObjectsEnd -
				data->m_riderSubObjectsBegin; ++i)
				sink->invoke(data->m_riderSubObjectsBegin[i], false, 0, 0, 0);
		}

		unsigned char riderIndex = update->m_flag21;
		DetachableRiderRecord *record = data->m_riderRecords + riderIndex;
		if (record->m_riderOCL != 0)
			record->m_riderOCL->bfmeDoBPB(object, object, 0);

		{
			DetachableRiderLocalFlags flags = {};
			object->clearAndSetModelConditionFlags(
				*reinterpret_cast<const BitFlags<320> *>(record),
				flags.m_modelConditions);
		}
		object->setWeaponLock(data->m_weaponLock, 2);

		{
			DetachableRiderLocalFlags flags;
			flags.m_status.m_bits[0] = 0;
			flags.m_status.m_bits[1] = 0x40;
			flags.m_status.m_bits[2] = 0;
			object->setStatus(flags.m_status, true);
		}

		if ((object->m_modelConditionFlags & 0x100) == 0)
		{
			object->m_modelConditionFlags |= 0x100;
			object->notifyModelConditionChanged();
		}

		if (data->m_riderlessDeathChance)
		{
			Object *container = object->m_containedBy;
			RiderCarrier *carrier = container->m_contain;
			if (carrier != 0)
			{
				RiderAction *action = carrier->getRiderAction();
				if (action != 0)
					action->apply(object);
				else
					carrier->notifyRider(object, 0);
			}

			if (object->m_ai != 0)
			{
				AICommandInterface *ai =
					(AICommandInterface *)((unsigned char *)object->m_ai + 0x20);
				ai->aiIdle(COMMAND_SOURCE_AI);
			}
		}

		TheGameLogic->deselectObject(object, 0xffff, true);
		return UPDATE_SLEEP_FOREVER;
	}

	if (sink != 0)
	{
		for (Int i = 0; i < data->m_riderSubObjectsEnd -
			data->m_riderSubObjectsBegin; ++i)
			sink->invoke(data->m_riderSubObjectsBegin[i], true, 0, 0, 0);
	}

	((BfmeItem1005 *)object)->bfmeDoD1005(2);

	{
		DetachableRiderLocalFlags flags;
		flags.m_status.m_bits[0] = 0;
		flags.m_status.m_bits[1] = 0x40;
		flags.m_status.m_bits[2] = 0;
		object->setStatus(flags.m_status, true);
	}

	if ((object->m_modelConditionFlags & 0x100) != 0)
	{
		object->m_modelConditionFlags &= ~0x100;
		object->notifyModelConditionChanged();
	}

	if (data->m_ejectRiderIfApplicable)
	{
		Object *container = object->m_containedBy;
		if (container == 0)
		{
			((BfmeUnitCN *)object)->bfmeDoneCN();
			return UPDATE_SLEEP_FOREVER;
		}

		RiderCarrier *carrier = container->m_contain;
		if (carrier != 0 && carrier->getRiderAction() != 0)
		{
			Int expected = carrier->getRiderCount(0);
			RiderList *list = carrier->getRiderList();
			RiderListNode *end = list->m_sentinel;
			RiderListNode *first = end->m_next;
			RiderListNode *it = first;
			Int matching = 0;
			while (it != end)
			{
				if ((reinterpret_cast<RiderFlagObject *>(it->m_object)->m_riderFlag94 & 0x40) != 0)
					++matching;
				it = it->m_next;
			}

			if (matching == expected && first != end)
			{
				it = first;
				do
				{
					((BfmeUnitCN *)it->m_object)->bfmeDoneCN();
					it = it->m_next;
				} while (it != end);
			}
		}
	}

	return UPDATE_SLEEP_FOREVER;
}
