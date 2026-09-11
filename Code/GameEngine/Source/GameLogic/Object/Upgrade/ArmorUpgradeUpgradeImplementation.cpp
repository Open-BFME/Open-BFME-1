// cl: /DNDEBUG /MD /EHsc
// ArmorUpgrade::upgradeImplementation at retail 0x002D2D20, 213 bytes.
// ArmorUpgrade's constructor at 0x002D2AB0 installs the vtable at
// 0x010CBA40, whose slot 7 points to this body through ILT 0x0000986D.

typedef unsigned int UnsignedInt;
typedef int ArmorSetType;

#pragma comment(linker, "/alternatename:?notifyModelConditionChanged@Object@@QAEXXZ=?j_0002191d@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeClearZJ@BfmeBaseZJ@@QAEXXZ=?j_00041970@@YAXXZ")

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
	virtual void clearArmorSetFlag(ArmorSetType flag);
	virtual void setArmorSetFlag(ArmorSetType flag);
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

class BfmeBaseZJ
{
public:
	void bfmeClearZJ();
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

	BodyModuleInterface *body = object->bodyModule();
	if (body)
	{
		if (!data->killArmorUpgrade)
		{
			body->setArmorSetFlag(data->armorSetFlag);

			UnsignedInt condition =
				reinterpret_cast<const UnsignedInt *>(0x012B2C98)[data->armorSetFlag];
			if (object->hasModelCondition(condition))
			{
				object->clearModelCondition(condition);
				object->notifyModelConditionChanged();
			}
		}
		else
		{
			body->clearArmorSetFlag(data->armorSetFlag);

			UnsignedInt condition =
				reinterpret_cast<const UnsignedInt *>(0x012B2C98)[data->armorSetFlag];
			if (!object->hasModelCondition(condition))
			{
				object->setModelCondition(condition);
				object->notifyModelConditionChanged();
			}
		}
	}
	((BfmeBaseZJ *)((char *)this - 0x10))->bfmeClearZJ();
}
