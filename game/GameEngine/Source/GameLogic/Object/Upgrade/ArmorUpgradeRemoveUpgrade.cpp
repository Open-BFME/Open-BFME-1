// cl: /DNDEBUG /MD /EHsc
// ArmorUpgrade::removeUpgrade (UpgradeMux slot 7) at retail 0x002D2D20, 213 bytes.
// ArmorUpgrade's constructor at 0x002D2AB0 installs the vtable at
// 0x010CBA40, whose slot 7 points to this body through ILT 0x0000986D.
// Slot 7 is EA's removeUpgrade (BFME2/RotWK WorldBuilder labels, matching slot),
// a virtual that UpgradeMux::attemptUpgrade (0x002D9AD0)
// never calls; slot 9 is upgradeImplementation (0x002D2C20), which this
// body undoes.
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot7-removeupgrade.md
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md

typedef unsigned int UnsignedInt;
typedef int ArmorSetType;

extern UnsignedInt g_012B2C98[];

// Retail routes both calls through ILT thunks 0x0002191D (Object's
// notifyModelConditionChanged) and 0x00041970 (BfmeBaseZJ's bfmeClearZJ).
// Reference the thunks directly through a member-pointer union so the emitted
// bytes are identical without a linker alias.
extern void j_0002191d();
extern void j_00041970();

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

class BfmeBaseZJ
{
};

struct ArmorUpgradeModuleData
{
	unsigned char pad00[0x70];
	unsigned char killArmorUpgrade;
	unsigned char ignoreArmorUpgrade;
	unsigned char pad72[2];
	ArmorSetType armorSetFlag;
};

class ArmorUpgrade
{
public:
	virtual void removeUpgrade();
};

void ArmorUpgrade::removeUpgrade()
{
	Object *object = *(Object **)((char *)this - 8);

	if (!object)
		return;

	ArmorUpgradeModuleData *data =
		*(ArmorUpgradeModuleData **)((char *)this - 0xc);
	if (!data || data->ignoreArmorUpgrade)
		return;

	typedef void (Object::*NotifyChanged)();
	union { void (*fn)(); NotifyChanged call; } notifyChanged = { j_0002191d };

	BodyModuleInterface *body = object->bodyModule();
	if (body)
	{
		if (!data->killArmorUpgrade)
		{
			body->clearArmorSetFlag(data->armorSetFlag);

			UnsignedInt condition =
				g_012B2C98[data->armorSetFlag];
			if (object->hasModelCondition(condition))
			{
				object->clearModelCondition(condition);
				(object->*notifyChanged.call)();
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
				(object->*notifyChanged.call)();
			}
		}
	}

	typedef void (BfmeBaseZJ::*Clear)();
	union { void (*fn)(); Clear call; } clear = { j_00041970 };
	(((BfmeBaseZJ *)((char *)this - 0x10))->*clear.call)();
}
