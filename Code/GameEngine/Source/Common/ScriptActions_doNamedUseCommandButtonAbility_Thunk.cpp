// cl: /DNDEBUG /MD /EHsc
// readable body of ?doNamedUseCommandButtonAbility@ScriptActions@@IAEXABVAsciiString@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// Open-BFME5: lift the ScriptActions::doNamedUseCommandButtonAbility MASM dump
// to clean C++. Zero Hour's body is ScriptActions.cpp:4257 and BFME kept it,
// except doCommandButton takes a third argument here, always zero.
//
// getName() and isEmpty() are inlined -- retail reads the button's AsciiString at
// +0xC and tests the word at data+4 -- while the rest are calls through ILT
// thunks. getCommandButton and compare go through shim classes because their real
// names are matched at the body address, and naming them directly would emit a
// rel32 to the body where retail jumps through the thunk.

class AsciiString;
class CommandButton;
class CommandSet;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
struct AsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_numChars;			///< retail data+0x04
};

class AsciiStringCompareShim
{
public:
	int compare(const AsciiString &other) const;	///< ILT 0x000220C5
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	bool isEmpty(void) const { return m_data == 0 || m_data->m_numChars == 0; }

	int compare(const AsciiString &other) const
	{
		return ((const AsciiStringCompareShim *)this)->compare(other);
	}

	AsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	const AsciiString &getName(void) const { return m_name; }

	unsigned char m_unreconstructed_00[0xC];
	AsciiString m_name;				///< retail button+0x0C
};

class CommandSetShim
{
public:
	const CommandButton *getCommandButton(int index) const;	///< ILT 0x00003F80
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandSet
{
public:
	const CommandButton *getCommandButton(int index) const
	{
		return ((const CommandSetShim *)this)->getCommandButton(index);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const AsciiString &getCommandSetString(void) const;	///< ILT 0x00029DC0
	void doCommandButton(const CommandButton *button, int source, int extra);	///< ILT 0x000063CF
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);	///< ILT 0x00048CCA
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void scriptEngineSlot0();
	virtual void scriptEngineSlot1();
	virtual void scriptEngineSlot2();
	virtual void scriptEngineSlot3();
	virtual void scriptEngineSlot4();
	virtual void scriptEngineSlot5();
	virtual void scriptEngineSlot6();
	virtual void scriptEngineSlot7();
	virtual void scriptEngineSlot8();
	virtual void scriptEngineSlot9();
	virtual void scriptEngineSlot10();
	virtual void scriptEngineSlot11();
	virtual void scriptEngineSlot12();
	virtual void scriptEngineSlot13();
	virtual void scriptEngineSlot14();
	virtual void scriptEngineSlot15();
	virtual void scriptEngineSlot16();
	virtual void scriptEngineSlot17();
	virtual void scriptEngineSlot18();
	virtual void scriptEngineSlot19();
	virtual void scriptEngineSlot20();
	virtual void scriptEngineSlot21();
	virtual void scriptEngineSlot22();
	virtual void scriptEngineSlot23();
	virtual void scriptEngineSlot24();
	virtual void scriptEngineSlot25();
	virtual Object *getUnitNamed(const AsciiString &name);	///< vtable +0x68
};

extern ControlBar *TheControlBar;			///< retail [0x012F33F8]
extern ScriptEngine *TheScriptEngine;		///< retail [0x012F076C]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doNamedUseCommandButtonAbility(const AsciiString &unit, const AsciiString &ability);
};

// ?doNamedUseCommandButtonAbility@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doNamedUseCommandButtonAbility(const AsciiString &unit, const AsciiString &ability)
{
	Object *theObj = TheScriptEngine->getUnitNamed(unit);

	if (!theObj)
	{
		return;
	}

	const CommandSet *commandSet = TheControlBar->findCommandSet(theObj->getCommandSetString());

	if (commandSet)
	{
		for (int i = 0; i < 20; i++)
		{
			const CommandButton *commandButton = commandSet->getCommandButton(i);

			if (commandButton)
			{
				if (!commandButton->getName().isEmpty())
				{
					if (commandButton->getName().compare(ability) == 0)
					{
						theObj->doCommandButton(commandButton, 1, 0);
					}
				}
			}
		}
	}
}
