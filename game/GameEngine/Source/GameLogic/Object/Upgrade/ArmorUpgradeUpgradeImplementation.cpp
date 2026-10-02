// cl: /DNDEBUG /MD /EHsc
// ArmorUpgrade::upgradeImplementation at retail 0x002D2C20, 199 bytes: slot 9
// of the UpgradeMux table 0x010CBA40, reached only through ILT 0x0001366A (its
// VA appears once in the image). ArmorUpgrade's registered constructor
// 0x002D2AB0 stores that table at +0x10. Slot 9 is the upgradeImplementation
// call in UpgradeMux::attemptUpgrade (0x002D9AD0).
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md
//
// The body mirrors the slot-7 body 0x002D2D20 (ArmorUpgradeRva002D2D20.cpp): it
// first calls the module helper at 0x002D9F30, then applies the armor set flag
// with the KillArmorUpgrade sense swapped relative to slot 7, and tail-calls
// notifyModelConditionChanged.

typedef unsigned int UnsignedInt;
typedef int ArmorSetType;

extern UnsignedInt g_012B2C98[];


class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void setArmorSetFlag(ArmorSetType flag);	// +0x30 (ActiveBody 0x0020FB70: or)
	virtual void clearArmorSetFlag(ArmorSetType flag);	// +0x34 (ActiveBody 0x0020FB90: and-not)
};

class Object
{
public:
	void notifyModelConditionChanged();

	UnsignedInt *modelConditionFlags()
	{
		return reinterpret_cast<UnsignedInt *>(
			reinterpret_cast<char *>(this) + 0x110);
	}

	BodyModuleInterface *bodyModule()
	{
		return *reinterpret_cast<BodyModuleInterface **>(
			reinterpret_cast<char *>(this) + 0x200);
	}

	__forceinline bool hasModelCondition(UnsignedInt condition) const
	{
		UnsignedInt *word = reinterpret_cast<UnsignedInt *>(
			reinterpret_cast<char *>(const_cast<Object *>(this)) + 0x110) +
			(condition >> 5);
		return (*word & (1u << (condition & 0x1f))) != 0;
	}

	__forceinline void clearModelCondition(UnsignedInt condition)
	{
		UnsignedInt *word = modelConditionFlags() + (condition >> 5);
		*word &= ~(1u << (condition & 0x1f));
	}

	__forceinline void setModelCondition(UnsignedInt condition)
	{
		UnsignedInt *word = modelConditionFlags() + (condition >> 5);
		*word |= 1u << (condition & 0x1f);
	}
};

struct ArmorUpgradeModuleData
{
	unsigned char pad00[0x70];
	unsigned char killArmorUpgrade;
	unsigned char ignoreArmorUpgrade;
	unsigned char pad72[2];
	ArmorSetType armorSetFlag;
};

// ILT 0x0000835F -> 0x002D9F30; the same pinned spelling AttributeModifierUpgrade
// and the banked attempt use.
class BfmeBaseTCB
{
public:
	void bfmeInitTCB();
};

class ArmorUpgrade
{
protected:
	virtual void upgradeImplementation();
};

void ArmorUpgrade::upgradeImplementation()
{
	Object *object = *(Object **)((char *)this - 8);

	if (!object)
		return;

	ArmorUpgradeModuleData *data =
		*(ArmorUpgradeModuleData **)((char *)this - 0xc);
	if (!data || data->ignoreArmorUpgrade)
		return;

	((BfmeBaseTCB *)((char *)this - 0x10))->bfmeInitTCB();

	BodyModuleInterface *body = object->bodyModule();
	if (!body)
		return;

	if (data->killArmorUpgrade)
	{
		body->clearArmorSetFlag(data->armorSetFlag);

		UnsignedInt condition =
			g_012B2C98[data->armorSetFlag];
		if (object->hasModelCondition(condition))
		{
			object->clearModelCondition(condition);
			object->notifyModelConditionChanged();
		}
	}
	else
	{
		body->setArmorSetFlag(data->armorSetFlag);

		UnsignedInt condition =
			g_012B2C98[data->armorSetFlag];
		if (!object->hasModelCondition(condition))
		{
			object->setModelCondition(condition);
			object->notifyModelConditionChanged();
		}
	}
}
