// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::getCommandButtonSourceObject, retail 0x00151430, 112 bytes.
//
// The reference's body with two BFME changes:
//
//   - MAX_COMMANDS_PER_SET is 20, not the reference's 18 -- the inner loop
//     stops at 0x14.
//   - getCommandType() is not a call: the command type is read straight out of
//     the button at +0x10 and compared against the argument.
//
// m_memberList is at this+0x04, the same STLport sentinel walk the other
// AIGroup loops measured, payload at node+0x08.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;

enum { MAX_COMMANDS_PER_SET = 20 };

enum GUICommandType {};

class AsciiString;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	GUICommandType getCommandType(void) const { return m_command; }

private:
	unsigned char m_unmodelled_000[0x10];			// +0x00 .. +0x0F
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

extern ControlBar *TheControlBar;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const AsciiString &getCommandSetString(void) const;	// ILT 0x00029DC0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	Object *getCommandButtonSourceObject(GUICommandType type);

private:
	unsigned char m_unmodelled_000[4];			// this+0x00, untouched
	_STL::list<Object *> m_memberList;			// this+0x04
};

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
