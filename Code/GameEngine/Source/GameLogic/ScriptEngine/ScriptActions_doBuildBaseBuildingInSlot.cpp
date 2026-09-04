// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME: retail 0x002F1840, 313 bytes.
// BUILD_BASE_BUILDING_IN_SLOT (action 384): the slot value is supplied to the
// same proven base-building path used by BUILD_BASE_BUILDING (action 383).

typedef bool Bool;
typedef int Int;
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 0x007fffff,
	NAMEKEY_FORCE_LONG = 0x7fffffff
};

template <class T>
class StringBase
{
public:
	Bool isEmpty() const;
};

class AsciiString : private StringBase<char>
{
public:
	Bool isEmpty() const
	{
		return StringBase<char>::isEmpty();
	}

private:
	char *m_text;
};

class Object;
class BfmeY982;
class ThingTemplate;
class Module;

// ScriptActionParameter::getInt() reads the scalar at +0x08.
class ScriptActionParameter
{
public:
	unsigned char m_beforeValue[0x08];
	Int m_value;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Player *unused();
	Bool canAffordBuild(const ThingTemplate *whatToBuild) const;

	unsigned char m_pad00[0x295];
	unsigned char m_isLocallyControlled;
};

// The first method is the already matched body behind retail ILT 0x00009453.
// The second method is the same base-building module call behind ILT 0x0000983B.
class Gen_00371340
{
public:
	Bool hasIncompleteStructure(BfmeY982 *argument);
	Object *build(ThingTemplate *whatToBuild, Int slot, void *argument);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;
	Module *findModule(NameKeyType key) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingFactory.h
class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
};

// BFME's ILT is a five-byte thunk to the retail base-building module body.
#pragma comment(linker, "/alternatename:?build@Gen_00371340@@QAEPAVObject@@PAVThingTemplate@@HPAX@Z=?j_0000983b@@YAXXZ")

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
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
	virtual Player *getCurrentPlayer() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void bindUnitReference(Object *object, const AsciiString &name) = 0;

	void assignUnitReference(const AsciiString &name, Object *object);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern ScriptEngine *TheScriptEngine;
extern ThingFactory *TheThingFactory;
extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doBuildBaseBuildingInSlot(const AsciiString &buildingType,
		ScriptActionParameter *slot, const AsciiString &baseName,
		const AsciiString &referenceName);
};

// ?doBuildBaseBuildingInSlot@ScriptActions@@IAEXABVAsciiString@@PAVScriptActionParameter@@00@Z
void ScriptActions::doBuildBaseBuildingInSlot(const AsciiString &buildingType,
	ScriptActionParameter *slot, const AsciiString &baseName,
	const AsciiString &referenceName)
{
	Object *baseObject = TheScriptEngine->getUnitNamed(baseName);
	if (!baseObject)
		return;

	Player *player = baseObject->getControllingPlayer();
	if (!player)
		return;
	if (!player->m_isLocallyControlled)
		return;
	if (player != TheScriptEngine->getCurrentPlayer())
		return;

	ThingTemplate *templateValue = TheThingFactory->findTemplate(buildingType);
	if (!templateValue)
		return;

	static volatile NameKeyType baseModuleKey =
		TheNameKeyGenerator->nameToKey((const char *)0x01083c50);
	Gen_00371340 *base =
		(Gen_00371340 *)baseObject->findModule(baseModuleKey);
	if (!base)
		return;
	if (!base->hasIncompleteStructure((BfmeY982 *)templateValue))
		return;
	if (!player->canAffordBuild(templateValue))
		return;

	Int slotValue = slot->m_value;
	Object *newObject = base->build(templateValue, slotValue, 0);
	if (!newObject)
		return;
	if (referenceName.isEmpty())
		return;

	TheScriptEngine->assignUnitReference(referenceName, newObject);
	TheScriptEngine->bindUnitReference(newObject, referenceName);
}
