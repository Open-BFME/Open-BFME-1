// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?evaluateCanBuildObjectTypeAtBase@ScriptConditions@@IAE_NPAVParameter@@00@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateCanBuildAtBase@ScriptConditions@@IAE_NPAVParameter@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp

// The two ScriptConditions conditions that ask whether a player may still
// build at a named castle:
//
//   0x00323E50  evaluateCanBuildObjectTypeAtBase  template 169, three args
//   0x0032C460  evaluateCanBuildAtBase            template 127, two args
//
// They are the same walk -- name the unit, resolve the player parameter to a
// single-player mask, confirm the unit is that player's, then look for a
// CastleBehavior module and ask it for an incomplete structure -- and differ
// only at the ends. The three-argument one resolves a ThingTemplate first and
// passes it to hasIncompleteStructure; the two-argument one passes NULL, and
// when there is no CastleBehavior at all it falls back to asking the object
// (0x67) and querying the FoundationAIUpdate interface at module+0x20.
//
// The duplicated `theUnit->getControllingPlayer() == player` test inside its
// own inverted repeat is retail's, in both bodies.
//
// AsciiString is deliberately the bare data pointer here rather than the
// delegating StringBase slice the rest of ScriptConditions uses: nothing in
// either body copies a string by value -- findTemplate takes a const
// reference -- so the shape that forces in-place construction is not what
// these two compile to.
//
// getUnitNamed is spelled taking a Parameter* rather than the const
// AsciiString& the other ScriptConditions TUs give it. Both spellings reach
// slot 26, and a virtual call resolves by slot, so the argument type here is
// only what these two bodies pass.

typedef bool Bool;
typedef unsigned short UnsignedShort;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
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
class Module;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingFactory.h
class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getPlayerFromMask(UnsignedShort mask);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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
	virtual Object *getUnitNamed(Parameter *) = 0;		// slot 26, vtable+0x68
	UnsignedShort unidentified_0034DB40(Parameter *);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer(void) const;
	Module *findModule(NameKeyType key) const;
};

// The 0x67 question the two-argument body asks an object with no
// CastleBehavior; still an address-derived name.
class BfmeThingAIA
{
public:
	Bool bfmeAskAIA(int);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CastleBehavior.h
class CastleBehavior
{
public:
	Bool hasIncompleteStructure(const ThingTemplate *tmplate);
};

// The FoundationAIUpdate module's interface, at module+0x20.
class FoundationIface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual Bool query() = 0;
};

extern ThingFactory *TheThingFactory;
extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	Bool evaluateCanBuildObjectTypeAtBase(Parameter *, Parameter *, Parameter *);
	Bool evaluateCanBuildAtBase(Parameter *, Parameter *);
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
