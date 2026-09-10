// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

class Player;
class Object;
class Module;

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

	void assignUnitReference(const AsciiString &name, Object *object);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class CastleBehavior
{
public:
	Bool isPlayerAllowedToPackOrUnpack(Player *player, Bool playerAllowed);
	Bool canPlayerAffordUnpack(Player *player) const;
};

extern void j_00019e34(void);
extern void j_0004b268(void);

typedef Bool (CastleBehavior::*BaseUnpackableCall)(Bool);
typedef void (CastleBehavior::*UnpackCall)(Bool, void *);

class Object
{
public:
	Player *getControllingPlayer() const;
	Module *findModule(NameKeyType key) const;
};

class ScriptActions
{
protected:
	void doNamedBaseUnpack(const AsciiString &baseName,
		const AsciiString &referenceName, Bool free);
};

extern ScriptEngine *TheScriptEngine;
extern NameKeyGenerator *TheNameKeyGenerator;

// ?doNamedBaseUnpack@ScriptActions@@IAEXABVAsciiString@@0_N@Z
void ScriptActions::doNamedBaseUnpack(const AsciiString &baseName,
	const AsciiString &referenceName, Bool free)
{
	Object *baseObject = TheScriptEngine->getUnitNamed(baseName);
	if (!baseObject)
		return;

	if (baseObject->getControllingPlayer() != TheScriptEngine->getCurrentPlayer())
		return;

	static volatile NameKeyType baseModuleKey =
		TheNameKeyGenerator->nameToKey((const char *)0x01083c50);
	CastleBehavior *base =
		(CastleBehavior *)baseObject->findModule(baseModuleKey);
	if (!base)
		return;
	union { void *asVoid; BaseUnpackableCall asMember; } unpackableCast;
	unpackableCast.asVoid = (void *)j_00019e34;
	if (!(base->*unpackableCast.asMember)(true))
		return;
	if (!base->isPlayerAllowedToPackOrUnpack(
		baseObject->getControllingPlayer(), true))
		return;

	if (!free && !base->canPlayerAffordUnpack(
		baseObject->getControllingPlayer()))
		return;

	union { void *asVoid; UnpackCall asMember; } unpackCast;
	unpackCast.asVoid = (void *)j_0004b268;
	(base->*unpackCast.asMember)(free, 0);
	if (referenceName.isEmpty())
		return;

	TheScriptEngine->assignUnitReference(referenceName, baseObject);
}
