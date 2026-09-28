// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?buildUpgrade@AIPlayer@@QAEXABVAsciiString@@@Z: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
//
// AIPlayer::buildUpgrade, 0x001636D0, 1089 bytes.
// Identity: the body is Zero Hour's buildUpgrade message for message -- the
// seven debug strings "Upgrade " / " does not exist.  Ignoring request.",
// "Player build upgrade: Upgrade " / " is an object, not a player upgrade.
// Ignoring request.", " already has upgrade " with " queued." and
// " completed.", " lacks money to build upgrade ", " queues " / " at " and
// " lacks factory to build upgrade " (VA 0x01096AB4..0x01096C40) -- and the
// same callee order: findUpgrade, hasUpgradeInProduction, hasUpgradeComplete,
// canAffordUpgrade, findCommandSet/getCommandButton, queueUpgrade.
//
// BFME differences: the factory search walks every live object the player
// controls instead of the build list, the command-set scan covers 20 buttons
// and remembers the matching button's resolved thing template, which
// queueUpgrade (ProductionUpdateInterface slot 3) takes as a second argument,
// and canAffordUpgrade takes (player, upgrade, NULL, false). The first two
// messages are built with StringBase<char>::concat(const char *, int) inline;
// the later ones call the out-of-line concat overloads, as retail does.
//
// The SOLD status test is read into a Bool local first; canUpgradeHere is
// assigned from that local after the guard, which is the spelling that puts
// the `mov [esp+0x13],al` store after `mov ecx,ebp` and keeps factory in EBP.
//
// Layout: AIPlayer m_player +0x0C; Player name key +0x20; UpgradeTemplate
// type +0x04 (UPGRADE_TYPE_OBJECT 1), name +0x08; Object next +0x88;
// CommandButton name +0x0C, upgrade template +0x20.
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;

#define NULL 0
#define FALSE 0

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum UpgradeType { UPGRADE_TYPE_PLAYER = 0, UPGRADE_TYPE_OBJECT = 1 };
enum { OBJECT_STATUS_UNDER_CONSTRUCTION = 2, OBJECT_STATUS_SOLD = 19 };
enum { MAX_COMMANDS_PER_SET = 20 };

// StringBase<char>'s buffer header: refcount, length, capacity, data.
struct BfmeAsciiHeader
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_data[1];
};

// Retail inlines AsciiString::concat(const AsciiString &) as
// concat(str(), getLength()), each accessor with its own null test.
class BfmeAsciiView
{
public:
	int getLength() const { return m_data ? m_data->m_length : 0; }
	const char *str() const { return m_data ? m_data->m_data : ""; }
private:
	const BfmeAsciiHeader *m_data;
};

static inline void bfmeConcat(AsciiString &dst, const AsciiString &src)
{
	const BfmeAsciiView &s = *(const BfmeAsciiView *)&src;
	((StringBase<char> *)&dst)->concat(s.str(), s.getLength());
}

class ThingTemplate;
class Player;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	AsciiString keyToName(NameKeyType key);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
public:
	UpgradeType getUpgradeType() const { return m_type; }
	const AsciiString &getUpgradeName() const { return m_name; }
private:
	void *m_vptr;
	UpgradeType m_type;						// +0x04
	AsciiString m_name;						// +0x08
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
	Bool canAffordUpgrade(Player *player, const UpgradeTemplate *upgradeTemplate,
		const ThingTemplate *thing, Bool displayReason) const;
};

extern UpgradeCenter *TheUpgradeCenter;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	NameKeyType getPlayerNameKey() const { return m_playerNameKey; }
	Bool hasUpgradeInProduction(const UpgradeTemplate *upgradeTemplate);
	Bool hasUpgradeComplete(const UpgradeTemplate *upgradeTemplate);
private:
	char m_unmodelled000[0x20];
	NameKeyType m_playerNameKey;					// +0x20
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProductionUpdate.h
class ProductionUpdateInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual Bool queueUpgrade(const UpgradeTemplate *upgrade, const ThingTemplate *thing);	// slot 3
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const ThingTemplate *getTemplate() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_nameString; }
private:
	char m_unmodelled000[0x20];
	AsciiString m_nameString;					// +0x20
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	Bool testStatus(Int bit) const;
	const AsciiString &getCommandSetString() const;
	ProductionUpdateInterface *getProductionUpdateInterface();
	Object *getNextObject() const { return m_next; }
private:
	char m_unmodelled000[0x88];
	Object *m_next;							// +0x88
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *getFirstObject();
};

extern GameLogic *TheGameLogic;

class BfmeCommandButtonDispatchILT;

// Retail 0x0049B2A0 (ILT 0x000205CC) returns the button's override-resolved
// thing template; its owner name stays address-derived in the ledger.
class BfmeCommandButtonResolveILT
{
public:
	BfmeCommandButtonDispatchILT *resolve();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	const AsciiString &getName() const { return m_name; }
	const UpgradeTemplate *getUpgradeTemplate() const { return m_upgradeTemplate; }
	const ThingTemplate *getThingTemplate() const
	{
		return (const ThingTemplate *)((BfmeCommandButtonResolveILT *)this)->resolve();
	}
private:
	char m_unmodelled000[0x0c];
	AsciiString m_name;						// +0x0C
	char m_unmodelled010[0x20 - 0x10];
	const UpgradeTemplate *m_upgradeTemplate;			// +0x20
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandSet
{
public:
	const CommandButton *getCommandButton(Int i) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);
};

extern ControlBar *TheControlBar;

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &strToAdd, Bool mustAdd);
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
public:
	void buildUpgrade(const AsciiString &upgrade);
private:
	void *m_vptr;
	void *m_dlinkhead_TeamBuildQueue;				// +0x04
	void *m_dlinkhead_TeamReadyQueue;				// +0x08
	Player *m_player;						// +0x0C
};

void AIPlayer::buildUpgrade(const AsciiString &upgrade)
{
	Object *factory;
	const UpgradeTemplate *curUpgrade = TheUpgradeCenter->findUpgrade(upgrade);
	if (curUpgrade==NULL) {
		AsciiString msg = "Upgrade ";
		bfmeConcat(msg, upgrade);
		((StringBase<char> *)&msg)->concat(" does not exist.  Ignoring request.", 35);
		TheScriptEngine->AppendDebugMessage( msg, false);
		return;
	}
 	if (curUpgrade->getUpgradeType()==UPGRADE_TYPE_OBJECT) {
		AsciiString msg = "Player build upgrade: Upgrade ";
		bfmeConcat(msg, upgrade);
		((StringBase<char> *)&msg)->concat(" is an object, not a player upgrade.  Ignoring request.", 55);
		TheScriptEngine->AppendDebugMessage( msg, false);
		return;
	}
	// See if it is in progress.
	if (m_player->hasUpgradeInProduction(curUpgrade)) {
		AsciiString msg = TheNameKeyGenerator->keyToName(m_player->getPlayerNameKey());
		msg.concat(" already has upgrade ");
		msg.concat(upgrade);
		msg.concat(" queued.  Ignoring request.");
		TheScriptEngine->AppendDebugMessage( msg, false);
		return;
	}
	// See if it is in progress.
	if (m_player->hasUpgradeComplete(curUpgrade)) {
		AsciiString msg = TheNameKeyGenerator->keyToName(m_player->getPlayerNameKey());
		msg.concat(" already has upgrade ");
		msg.concat(upgrade);
		msg.concat(" completed.  Ignoring request.");
		TheScriptEngine->AppendDebugMessage( msg, false);
		return;
	}


	// No money.
	if( TheUpgradeCenter->canAffordUpgrade( m_player, curUpgrade, NULL, FALSE ) == FALSE ) {
		AsciiString msg = TheNameKeyGenerator->keyToName(m_player->getPlayerNameKey());
		msg.concat(" lacks money to build upgrade ");
		msg.concat(upgrade);
		msg.concat(" at this time.  Ignoring request.");
		TheScriptEngine->AppendDebugMessage( msg, false);
		return;
	}
	// Find a production queue.
	for( factory = TheGameLogic->getFirstObject(); factory; factory = factory->getNextObject() )
	{
		if( factory->getControllingPlayer() != m_player )
			continue;
		if( factory->testStatus( OBJECT_STATUS_UNDER_CONSTRUCTION ) )
			continue;
		Bool canUpgradeHere;
		Bool sold = factory->testStatus( OBJECT_STATUS_SOLD );
		if( sold )
			continue;
		canUpgradeHere = sold;
		const CommandSet *commandSet = TheControlBar->findCommandSet( factory->getCommandSetString() );
		const ThingTemplate *buttonThing = NULL;
		if( commandSet == NULL) continue;
		for( Int j = 0; j < MAX_COMMANDS_PER_SET; j++ )
		{
			//Get the command button.
			const CommandButton *commandButton = commandSet->getCommandButton(j);
			if (commandButton==NULL) continue;
			if (commandButton->getName().isEmpty() )	continue;
			if (commandButton->getUpgradeTemplate() == NULL )	continue;
 			if (commandButton->getUpgradeTemplate()->getUpgradeName() == curUpgrade->getUpgradeName()) {
				canUpgradeHere = true;
				buttonThing = commandButton->getThingTemplate();
			}
		}
		if (!canUpgradeHere) continue;
		ProductionUpdateInterface *pu = factory->getProductionUpdateInterface();
		// If it doesn't produce, continue.
		if (!pu) continue;
		// Try to queue it.
		if (pu->queueUpgrade(curUpgrade, buttonThing)) {
			AsciiString msg = TheNameKeyGenerator->keyToName(m_player->getPlayerNameKey());
			msg.concat(" queues ");
			msg.concat(curUpgrade->getUpgradeName());
			msg.concat(" at ");
			msg.concat(factory->getTemplate()->getName());
			TheScriptEngine->AppendDebugMessage( msg, false);
			return;
		}
	}  // end for

	AsciiString msg = TheNameKeyGenerator->keyToName(m_player->getPlayerNameKey());
	((StringBase<char> *)&msg)->concat(" lacks factory to build upgrade ", 32);
	msg.concat(upgrade);
	((StringBase<char> *)&msg)->concat(" at this time.  Ignoring request.", 33);
	TheScriptEngine->AppendDebugMessage( msg, false);
	return;
}
