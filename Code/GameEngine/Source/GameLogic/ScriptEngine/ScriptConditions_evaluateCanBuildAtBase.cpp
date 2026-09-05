// cl: /DNDEBUG /MD /EHsc
// ScriptConditions::evaluateCanBuildAtBase, retail 0x0032C460.
// Template 127 CAN_BUILD_AT_BASE: player, named castle/base. 2-arg sibling of
// evaluateCanBuildObjectTypeAtBase (0x00323E50). Named unit owned by player,
// then CastleBehavior::hasIncompleteStructure(NULL) or FoundationAIUpdate
// iface query after BfmeThingAIA(0x67).

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
class Module;

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

class Object
{
public:
	Player *getControllingPlayer(void) const;
	Module *findModule(NameKeyType key) const;
};

class BfmeThingAIA
{
public:
	Bool bfmeAskAIA(int);
};

class CastleBehavior
{
public:
	Bool hasIncompleteStructure(const ThingTemplate *tmplate);
};

class FoundationIface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual Bool query() = 0;
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern NameKeyGenerator *TheNameKeyGenerator;

class ScriptConditions
{
protected:
	Bool evaluateCanBuildAtBase(Parameter *, Parameter *);
};

// ?evaluateCanBuildAtBase@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateCanBuildAtBase(
	Parameter *pPlayerParm, Parameter *pUnitParm)
{
	Object *theUnit = TheScriptEngine->getUnitNamed(pUnitParm);
	if (theUnit) {
		UnsignedShort mask = TheScriptEngine->unidentified_0034DB40(pPlayerParm);
		if (mask) {
			Player *player = ThePlayerList->getPlayerFromMask(mask);
			if (player) {
				if (theUnit->getControllingPlayer() == player) {
					if (player == theUnit->getControllingPlayer()) {
						static NameKeyType keyCastle =
							TheNameKeyGenerator->nameToKey("CastleBehavior");
						CastleBehavior *castle =
							(CastleBehavior *)theUnit->findModule(keyCastle);
						if (castle) {
							if (castle->hasIncompleteStructure(0))
								return true;
						} else if (((BfmeThingAIA *)theUnit)->bfmeAskAIA(0x67)) {
							static NameKeyType keyFound =
								TheNameKeyGenerator->nameToKey("FoundationAIUpdate");
							Module *mod = theUnit->findModule(keyFound);
							if (mod) {
								if (!((FoundationIface *)((char *)mod + 0x20))->query())
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
