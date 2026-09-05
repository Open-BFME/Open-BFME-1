// cl: /DNDEBUG /MD /EHsc
// ScriptConditions::evaluateCanBuildObjectTypeAtBase, retail 0x00323E50.
// Template 169 CAN_BUILD_OBJECTTYPE_AT_BASE: player, named castle, object type.

typedef bool Bool;
typedef unsigned short UnsignedShort;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class AsciiString
{
public:
	char *m_data;
};

class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class ThingTemplate;
class Player;
class Object;
class CastleBehavior;

class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class PlayerList
{
public:
	Player *getPlayerFromMask(UnsignedShort mask);
};

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
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(Parameter *) = 0;
	UnsignedShort unidentified_0034DB40(Parameter *);
};

class Module;

class Object
{
public:
	Player *getControllingPlayer(void) const;
	Module *findModule(NameKeyType key) const;
};

class CastleBehavior
{
public:
	Bool hasIncompleteStructure(const ThingTemplate *tmplate);
};

extern ThingFactory *TheThingFactory;
extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern NameKeyGenerator *TheNameKeyGenerator;

class ScriptConditions
{
protected:
	Bool evaluateCanBuildObjectTypeAtBase(Parameter *, Parameter *, Parameter *);
};

// ?evaluateCanBuildObjectTypeAtBase@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluateCanBuildObjectTypeAtBase(
	Parameter *pPlayerParm, Parameter *pUnitParm, Parameter *pTypeParm)
{
	ThingTemplate *tmplate = TheThingFactory->findTemplate(
		pTypeParm->getString());
	if (tmplate) {
		Object *theUnit = TheScriptEngine->getUnitNamed(pUnitParm);
		if (theUnit) {
			UnsignedShort mask = TheScriptEngine->unidentified_0034DB40(pPlayerParm);
			if (mask) {
				Player *player = ThePlayerList->getPlayerFromMask(mask);
				if (player) {
					if (theUnit->getControllingPlayer() == player) {
						if (player == theUnit->getControllingPlayer()) {
							static NameKeyType key = TheNameKeyGenerator->nameToKey(
								"CastleBehavior");
							CastleBehavior *castle =
								(CastleBehavior *)theUnit->findModule(key);
							if (castle) {
								if (castle->hasIncompleteStructure(tmplate))
									return true;
							}
						}
					}
				}
			}
		}
	}

	return false;
}
