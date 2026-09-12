// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the two AIGroup lookups that answer "which member should carry out
// this order" by returning the first one that can.
//
//   ?getSpecialPowerSourceObject@   0x001513D0,  77 bytes
//   ?getCommandButtonSourceObject@  0x00151430, 112 bytes
//
// Adjacent in the retail image and the same question asked two ways. Both walk
// m_memberList at this+0x04 -- the STLport sentinel ring, payload at node+0x08
// -- and return the first member that passes a test, or null.
//
// The 35-byte difference is entirely the test. getSpecialPowerSourceObject
// resolves the template once before the loop and then asks each member for a
// special power module, one call per member. getCommandButtonSourceObject has
// no such handle: for every member it looks up the command set by name and then
// scans all twenty buttons for a matching command type, so the walk is nested.
//
// Two BFME departures from the reference live in the second one, and they are
// both in that inner loop: MAX_COMMANDS_PER_SET is 20 rather than 18, so the
// scan stops at 0x14; and getCommandType() is not a call -- the type is read
// straight out of the button at +0x10.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;

enum { MAX_COMMANDS_PER_SET = 20 };

enum GUICommandType {};

class AsciiString;
class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	GUICommandType getCommandType(void) const { return m_command; }

private:
	unsigned char m_thingTemplate[0x10];			// +0x00 .. +0x0F
	GUICommandType m_command;				// +0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandSet
{
public:
	const CommandButton *getCommandButton(Int i) const;	// ILT 0x00003F80
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);	// ILT 0x00048CCA
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplateByID(UnsignedInt id);	// ILT 0x000034B8
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *spTemplate) const;	// ILT 0x000401BF
	const AsciiString &getCommandSetString(void) const;	// ILT 0x00029DC0
};

extern ControlBar *TheControlBar;
extern SpecialPowerStore *TheSpecialPowerStore;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	Object *getSpecialPowerSourceObject(UnsignedInt specialPowerID);
	Object *getCommandButtonSourceObject(GUICommandType type);

private:
	unsigned char m_thingTemplate[4];			// this+0x00, untouched
	_STL::list<Object *> m_memberList;			// this+0x04
};

// The reference's body unchanged: look the template up by id once, then hand
// back the first member that has a special power module for it.
Object *AIGroup::getSpecialPowerSourceObject( UnsignedInt specialPowerID )
{
	_STL::list<Object *>::iterator i;
	const SpecialPowerTemplate *spTemplate = TheSpecialPowerStore->findSpecialPowerTemplateByID( specialPowerID );
	if( spTemplate )
	{
		for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
		{
			Object *object = (*i);
			SpecialPowerModuleInterface *mod = object->getSpecialPowerModule( spTemplate );
			if( mod )
				return object;
		}
	}
	return 0;
}

Object *AIGroup::getCommandButtonSourceObject( GUICommandType type )
{
	_STL::list<Object *>::iterator it;

	for( it = m_memberList.begin(); it != m_memberList.end(); ++it )
	{
		Object *object = (*it);
		if (!object) {
			continue;
		}

		const CommandSet *commandSet = TheControlBar->findCommandSet( object->getCommandSetString() );
		if (!commandSet) {
			continue;
		}

		const CommandButton *commandButton;
		for(Int i = 0; i < MAX_COMMANDS_PER_SET; ++i)
		{
			commandButton = commandSet->getCommandButton(i);
			if(commandButton && (commandButton->getCommandType() == type)) {
				return object;
			}
		}
	}

	return 0;
}
