// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef unsigned short UnsignedShort;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class AsciiString
{
	void *m_data;
};

class Parameter;
class Player;
class Object;
class Module;
class BfmeThingLU;

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

class PlayerList
{
public:
	Player *getPlayerFromMask(UnsignedShort);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *);
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Module *findModule(NameKeyType) const;
	const AsciiString &getCommandSetString() const;
};

class Rva0036E420Castle
{
public:
	Bool canUnpack(Bool);
};

class CastleBehavior
{
public:
	Bool isPlayerAllowedToPackOrUnpack(Player *, Bool);
	Bool canPlayerAffordUnpack(Player *) const;
};

class Rva0036BA60Cost
{
};

class Rva0036BA60PurchaseContext
{
public:
	Bool canAfford(Player *, const Rva0036BA60Cost *) const;
};

class CommandButton
{
public:
	char m_pad00[0x10];
	int m_command;
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int) const;
};

class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &);
};

class CommandButtonResolveTarget
{
};

typedef BfmeThingLU *(CommandButtonResolveTarget::*ResolveCommandButtonCall)(void);

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern NameKeyGenerator *TheNameKeyGenerator;
extern ControlBar *TheControlBar;
extern void j_000205cc(void);

class ScriptConditions
{
protected:
	Bool evaluateNamedBaseUnpackableForPlayer(Parameter *, Parameter *);
};

Bool ScriptConditions::evaluateNamedBaseUnpackableForPlayer(
	Parameter *baseParm, Parameter *playerParm)
{
	Object *baseObject = TheScriptEngine->getUnitNamed(baseParm);
	if (baseObject) {
		UnsignedShort mask = TheScriptEngine->unidentified_0034DB40(playerParm);
		if (mask) {
			Player *player = ThePlayerList->getPlayerFromMask(mask);
			if (player) {
				if (baseObject->getControllingPlayer() == player) {
					static volatile NameKeyType baseModuleKey =
						TheNameKeyGenerator->nameToKey((const char *)0x01083c50);
					CastleBehavior *castle = (CastleBehavior *)baseObject->findModule(
						baseModuleKey);
					if (castle &&
						((Rva0036E420Castle *)castle)->canUnpack(true) &&
						castle->isPlayerAllowedToPackOrUnpack(player, true) &&
						castle->canPlayerAffordUnpack(player))
						return true;

					const CommandSet *commandSet = TheControlBar->findCommandSet(
						baseObject->getCommandSetString());
					if (commandSet) {
						for (int i = 0; i < 20; ++i) {
							const CommandButton *button =
								commandSet->getCommandButton(i);
							if (button && button->m_command == 0x30) {
								union {
									void (*raw)(void);
									ResolveCommandButtonCall member;
								} resolveCommandButton;
								resolveCommandButton.raw = j_000205cc;
								BfmeThingLU *thing =
									(reinterpret_cast<CommandButtonResolveTarget *>(
										const_cast<CommandButton *>(button))->*
									resolveCommandButton.member)();
								if (thing && castle &&
									((Rva0036E420Castle *)castle)->canUnpack(true) &&
									castle->isPlayerAllowedToPackOrUnpack(player, true) &&
									((Rva0036BA60PurchaseContext *)castle)->canAfford(
										player, (const Rva0036BA60Cost *)thing))
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
