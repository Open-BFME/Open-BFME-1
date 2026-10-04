// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// SiegeDeployHordeSpecialPower, retail 0x00265ED0, 659 bytes, ret 0x14.
//
// IDENTITY. The only route to this body is ILT 0x00045D59, slot zero of the
// table 0x010B7100 that the matched SiegeDeployHordeSpecialPower constructor
// (0x00265B20) installs at +0x20; the receiver arrives as that interface and
// reads the module data and object at -0x1C/-0x18. Five stack words and that
// slot are the shape of Zero Hour's SpecialPowerUpdateInterface
// initiateIntentToDoSpecialPower, but this body returns nothing and passes its
// fourth word where that method passes command options, so the method keeps
// an address-derived name. The old destructor row was wrong: it ends ret 0x14.
//
// BODY. Without the module data's flag at +0x1D0 the module only wakes. With
// it, the horde's first member whose template carries KindOf word +0xD0 bit
// 0x10000000 becomes the leader: the horde is told, the leader is deselected,
// idled and given the power at the target. Every member the horde lists
// through its +0x1CC slot is then idled and given the power, and its own
// SiegeDeployHordeSpecialPower module is pointed at the leader's ID and the
// target's position before its AI is set via the shared (0, 2) helper.
#include <list>
#include <vector>

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

class Thing;
class ModuleData;
class SpecialPowerTemplate;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

typedef Int ObjectID;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Lib/BaseType.h
struct Coord3D
{
	Real x, y, z;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Object;

class GameLogic
{
public:
	void deselectObject(Object *object, unsigned short playerMask, Bool affectClient);
};

extern GameLogic *TheGameLogic;

// The shared override walker the matched CrateSystem lookups also inline.
class Overridable
{
public:
	const Overridable *getFinalOverride(void) const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

protected:
	char m_bfme_vptr[4];
	Overridable *m_nextOverride;			// +0x04
};

class ThingTemplate : public Overridable
{
public:
	UnsignedInt isKindOfD0Bit28() const { return m_kindOfWordD0 & 0x10000000; }

private:
	unsigned char m_pad08[0xD0 - 0x08];
	UnsignedInt m_kindOfWordD0;				// +0xD0, one word of the KindOf mask
};

// Existing pin at ILT 0x0001336D for the two-word AI helper on the +0x20 base.
class BfmeRvaAIView
{
public:
	void setHeldState(Int a, Int b);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
	BfmeRvaAIView *view() { return (BfmeRvaAIView *)this; }
};

class AIUpdateInterfaceHead
{
	unsigned char m_pad00[0x20];
};

class AIUpdateInterface : public AIUpdateInterfaceHead, public AICommandInterface
{
};

#define BFME_SLOT(n) virtual void slot##n()

class Module
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03); BFME_SLOT(04);
	BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07); BFME_SLOT(08); BFME_SLOT(09);
	BFME_SLOT(10);
	// slots 11 and 12 of the found SiegeDeployHordeSpecialPower module
	virtual void slot11(ObjectID leader);
	virtual void slot12(const Coord3D *pos);
};

typedef _STL::list<Object *> ObjectList;
typedef _STL::vector<Object *> ObjectVector;

class HordeContainInterface
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03); BFME_SLOT(04);
	BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07); BFME_SLOT(08); BFME_SLOT(09);
	BFME_SLOT(10); BFME_SLOT(11); BFME_SLOT(12); BFME_SLOT(13);
	// slot 14, +0x38: told which member leads
	virtual void slot14(Object *leader);
	BFME_SLOT(15); BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23); BFME_SLOT(24);
	BFME_SLOT(25); BFME_SLOT(26); BFME_SLOT(27); BFME_SLOT(28); BFME_SLOT(29);
	BFME_SLOT(30); BFME_SLOT(31); BFME_SLOT(32); BFME_SLOT(33); BFME_SLOT(34);
	BFME_SLOT(35); BFME_SLOT(36); BFME_SLOT(37); BFME_SLOT(38); BFME_SLOT(39);
	BFME_SLOT(40); BFME_SLOT(41); BFME_SLOT(42); BFME_SLOT(43); BFME_SLOT(44);
	BFME_SLOT(45); BFME_SLOT(46); BFME_SLOT(47); BFME_SLOT(48); BFME_SLOT(49);
	BFME_SLOT(50); BFME_SLOT(51); BFME_SLOT(52); BFME_SLOT(53); BFME_SLOT(54);
	BFME_SLOT(55); BFME_SLOT(56); BFME_SLOT(57); BFME_SLOT(58);
	// slot 59, +0xEC: the member list
	virtual const ObjectList &slot59();
	BFME_SLOT(60); BFME_SLOT(61); BFME_SLOT(62); BFME_SLOT(63); BFME_SLOT(64);
	BFME_SLOT(65); BFME_SLOT(66); BFME_SLOT(67); BFME_SLOT(68); BFME_SLOT(69);
	BFME_SLOT(70); BFME_SLOT(71); BFME_SLOT(72); BFME_SLOT(73); BFME_SLOT(74);
	BFME_SLOT(75); BFME_SLOT(76); BFME_SLOT(77); BFME_SLOT(78); BFME_SLOT(79);
	BFME_SLOT(80); BFME_SLOT(81); BFME_SLOT(82); BFME_SLOT(83); BFME_SLOT(84);
	BFME_SLOT(85); BFME_SLOT(86); BFME_SLOT(87); BFME_SLOT(88); BFME_SLOT(89);
	BFME_SLOT(90); BFME_SLOT(91); BFME_SLOT(92); BFME_SLOT(93); BFME_SLOT(94);
	BFME_SLOT(95); BFME_SLOT(96); BFME_SLOT(97); BFME_SLOT(98); BFME_SLOT(99);
	BFME_SLOT(100); BFME_SLOT(101); BFME_SLOT(102); BFME_SLOT(103); BFME_SLOT(104);
	BFME_SLOT(105); BFME_SLOT(106); BFME_SLOT(107); BFME_SLOT(108); BFME_SLOT(109);
	BFME_SLOT(110); BFME_SLOT(111); BFME_SLOT(112); BFME_SLOT(113); BFME_SLOT(114);
	// slot 115, +0x1CC: fills a vector of members
	virtual void slot115(ObjectVector *out);
};

#undef BFME_SLOT

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
	friend class SiegeDeployHordeSpecialPower;

public:
	const ThingTemplate *getTemplate() const
	{
		if (m_template == 0)
			return 0;
		return (const ThingTemplate *)m_template->getFinalOverride();
	}

	ObjectID getID() const { return m_id; }
	const Coord3D *getPosition() const { return &m_pos; }
	AIUpdateInterface *getAI() const { return m_ai; }

	// address-derived pin: reads +0x1FC and asks it for its horde interface
	void *unidentified_001BFE20() const;
	void doSpecialPowerAtObject(const SpecialPowerTemplate *specialPowerTemplate,
		Object *targetObj, UnsignedInt commandOptions, Bool forced);

protected:
	Module *findModule(NameKeyType key) const;

private:
	char m_bfme_vptr[4];
	ThingTemplate *m_template;				// +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_pos;							// +0x38
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id;							// +0x74
	unsigned char m_pad78[0x204 - 0x78];
	AIUpdateInterface *m_ai;				// +0x204
};

class SiegeDeployHordeSpecialPowerModuleData
{
public:
	unsigned char m_pad00[0x1D0];
	Bool m_flag1D0;							// +0x1D0
};

// The constructor's layout (DynamicGeometryInfoUpdateConstructor.cpp): five
// vptrs at +0x00/+0x0C/+0x10/+0x20/+0x24 over the UpdateModule chain.
class ObjectModuleBase
{
public:
	virtual void objectModuleAnchor();
	const ModuleData *m_moduleData;			// +0x04
	Object *m_object;						// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorAnchor() = 0;
};

class BehaviorModule : public ObjectModuleBase, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual void updateAnchor() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
	Object *getObject() const { return m_object; }
	const ModuleData *getModuleData() const { return m_moduleData; }

	unsigned int m_nextCallFrameAndPhase;	// +0x14
	int m_indexInLogic;						// +0x18
	unsigned int m_updateState;				// +0x1C
};

class SpecialPowerInterface
{
public:
	virtual void rva00265ED0(const SpecialPowerTemplate *specialPowerTemplate,
		Object *targetObj, const Coord3D *targetPos, UnsignedInt commandOptions,
		UnsignedInt word5) = 0;
};

class UpgradeInterface
{
public:
	virtual void upgradeAnchor() = 0;
};

class SiegeDeployHordeSpecialPower
	: public UpdateModule, public SpecialPowerInterface, public UpgradeInterface
{
public:
	virtual void rva00265ED0(const SpecialPowerTemplate *specialPowerTemplate,
		Object *targetObj, const Coord3D *targetPos, UnsignedInt commandOptions,
		UnsignedInt word5);

protected:
	const SiegeDeployHordeSpecialPowerModuleData *getSiegeDeployHordeSpecialPowerModuleData() const
	{
		return (const SiegeDeployHordeSpecialPowerModuleData *)getModuleData();
	}
};

// ?rva00265ED0@SiegeDeployHordeSpecialPower@@UAEXPBVSpecialPowerTemplate@@PAVObject@@PBUCoord3D@@II@Z
void SiegeDeployHordeSpecialPower::rva00265ED0(const SpecialPowerTemplate *specialPowerTemplate,
	Object *targetObj, const Coord3D *targetPos, UnsignedInt commandOptions, UnsignedInt word5)
{
	if (getSiegeDeployHordeSpecialPowerModuleData()->m_flag1D0)
	{
		HordeContainInterface *horde = (HordeContainInterface *)getObject()->unidentified_001BFE20();
		if (horde)
		{
			ObjectList members(horde->slot59());

			Object *leader = 0;
			for (ObjectList::iterator it = members.begin(); it != members.end(); ++it)
			{
				Object *member = *it;
				if (member->getTemplate()->isKindOfD0Bit28())
				{
					leader = member;
					break;
				}
			}

			horde->slot14(leader);
			TheGameLogic->deselectObject(leader, 0xFFFF, true);
			leader->getAI()->aiIdle(CMD_FROM_AI);
			leader->doSpecialPowerAtObject(specialPowerTemplate, targetObj, commandOptions, false);

			ObjectVector others;
			((HordeContainInterface *)getObject()->unidentified_001BFE20())->slot115(&others);
			for (UnsignedInt i = 0; i < others.size(); ++i)
			{
				others[i]->getAI()->aiIdle(CMD_FROM_AI);
				others[i]->doSpecialPowerAtObject(specialPowerTemplate, targetObj, commandOptions, false);

				static NameKeyType key_SiegeDeployHordeSpecialPower =
					TheNameKeyGenerator->nameToKey("SiegeDeployHordeSpecialPower");
				Object *other = others[i];
				Module *module = other->findModule(key_SiegeDeployHordeSpecialPower);
				if (module)
				{
					module->slot11(leader->getID());
					module->slot12(targetObj->getPosition());
				}

				others[i]->getAI()->view()->setHeldState(0, 2);
			}
		}
	}
	else
	{
		setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
	}
}
