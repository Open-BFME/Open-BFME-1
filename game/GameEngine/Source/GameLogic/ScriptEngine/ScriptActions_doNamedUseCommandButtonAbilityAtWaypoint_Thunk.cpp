// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// Clean C++ recovery of NAMED_USE_COMMANDBUTTON_ABILITY_AT_WAYPOINT.
// Retail RVA 0x002F9F10 (169 bytes); executeAction template 203 reaches this
// body through the BFME dispatch arm and its link thunk.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;

class Object;
class CommandButton;
class CommandSet;

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &other);
};

// BFME's waypoint lookup takes its one-word string view by value.
class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
 	}

	~BfmeAsciiStringArg();

private:
	char *m_text;
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
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Waypoint
{
public:
	const Coord3D *getLocation() const
	{
		return (const Coord3D *)((const char *)this + 0x0c);
	}
};

class TerrainLogic
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
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual Waypoint *getWaypointByName(BfmeAsciiStringArg name) = 0;
};

class CommandSetShim
{
public:
	const CommandButton *getCommandButton(Int index) const;
};

// BFME stores the button name at +0x0C.  Its string data length is the word at
// data+4, rather than the first character used by the ZH inline helper.
class BfmeCommandButtonName
{
public:
	const AsciiString &getName() const { return m_name; }

private:
	unsigned char m_beforeName[0x0c];
	AsciiString m_name;
};

struct BfmeAsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_numChars;
	unsigned short m_unreconstructed06;
};

static Bool bfmeStringIsEmpty(const AsciiString &str)
{
	const BfmeAsciiStringData *data =
		*(const BfmeAsciiStringData * const *)&str;
	return data == 0 || data->m_numChars == 0;
}

class AsciiStringCompareShim
{
public:
	Int compare(const AsciiString &other) const;
};

class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

class Object
{
public:
	const AsciiString &getCommandSetString() const;
	void doCommandButtonAtPosition(const CommandButton *button,
		const Coord3D *position, CommandSourceType source, Bool playVoiceResponse);
};

extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;
extern ControlBar *TheControlBar;

class ScriptActions
{
protected:
	void doNamedUseCommandButtonAbilityAtWaypoint(const AsciiString &unit,
		const AsciiString &ability, const AsciiString &waypoint);
};

// ?doNamedUseCommandButtonAbilityAtWaypoint@ScriptActions@@IAEXABVAsciiString@@00@Z
void ScriptActions::doNamedUseCommandButtonAbilityAtWaypoint(
	const AsciiString &unit, const AsciiString &ability,
	const AsciiString &waypoint)
{
	Object *theObj = TheScriptEngine->getUnitNamed(unit);
	Waypoint *pWaypoint = TheTerrainLogic->getWaypointByName(waypoint);

	if (!theObj || !pWaypoint)
		return;

	const CommandSet *commandSet =
		TheControlBar->findCommandSet(theObj->getCommandSetString());
	if (commandSet)
	{
		for (Int i = 0; i < 20; ++i)
		{
			const CommandButton *commandButton =
				((const CommandSetShim *)commandSet)->getCommandButton(i);
			if (commandButton)
			{
				const AsciiString &name =
					((const BfmeCommandButtonName *)commandButton)->getName();
				if (!bfmeStringIsEmpty(name) &&
					((const AsciiStringCompareShim *)&name)->compare(ability) == 0)
				{
					theObj->doCommandButtonAtPosition(commandButton,
						pWaypoint->getLocation(), CMD_FROM_SCRIPT, false);
				}
			}
		}
	}
}
