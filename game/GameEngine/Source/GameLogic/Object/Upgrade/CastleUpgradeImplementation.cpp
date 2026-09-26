// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int ObjectID;
typedef int NameKeyType;

class AsciiString;
class ModuleData;
class UpgradeTemplate;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class Module
{
};

class Object
{
public:
	Module *findModule(NameKeyType key) const;
	void bfmeMarkUpgradeCompleted(const UpgradeTemplate *upgrade);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

class CastleBehavior
{
};

class CastleUpgrade
{
protected:
	virtual void upgradeImplementation();
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameLogic *TheGameLogic;
extern UpgradeCenter *TheUpgradeCenter;
extern void j_0001e35d();

// ?upgradeImplementation@CastleUpgrade@@MAEXXZ
void CastleUpgrade::upgradeImplementation()
{
	unsigned char *self = reinterpret_cast<unsigned char *>(this);
	ModuleData *moduleData = *reinterpret_cast<ModuleData **>(self - 0xc);
	Object *object = *reinterpret_cast<Object **>(self - 8);

	static NameKeyType castleMemberBehaviorKey =
		TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
	Module *member = object->findModule(castleMemberBehaviorKey);
	const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(
		*reinterpret_cast<const AsciiString *>(
			reinterpret_cast<unsigned char *>(moduleData) + 0x70));
	if (member != 0)
	{
		ObjectID castleObjectID = *reinterpret_cast<ObjectID *>(
			reinterpret_cast<unsigned char *>(member) + 0x18);
		Object *castle = TheGameLogic->findObjectByID(
			castleObjectID);
		if (castle != 0)
		{
			static NameKeyType castleBehaviorKey =
				TheNameKeyGenerator->nameToKey("CastleBehavior");
			Module *castleBehavior = castle->findModule(castleBehaviorKey);
			typedef void (CastleBehavior::*ApplyUpgrade)(
				const UpgradeTemplate *);
			union
			{
				void *asVoid;
				ApplyUpgrade asMember;
			} applyUpgrade;
			applyUpgrade.asVoid = (void *)j_0001e35d;
			CastleBehavior *behavior = (CastleBehavior *)castleBehavior;
			(behavior->*applyUpgrade.asMember)(upgrade);
			castle->bfmeMarkUpgradeCompleted(upgrade);
		}
	}
}
