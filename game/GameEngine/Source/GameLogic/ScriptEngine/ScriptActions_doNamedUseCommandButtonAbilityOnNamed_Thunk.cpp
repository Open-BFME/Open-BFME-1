// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// Clean C++ recovery of NAMED_USE_COMMANDBUTTON_ABILITY_ON_NAMED.
// Retail RVA 0x002F9E40 (166 bytes); executeAction template 202 reaches this
// body through the BFME dispatch arm and its link thunk.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;

class Object;
class CommandButton;
class CommandSet;
class Team;

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &other);
};

// Slot 27 takes the target through BFME's one-word by-value string view.
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
	virtual Object *getUnitNamedByValue(BfmeAsciiStringArg name) = 0;
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
	void doCommandButtonAtObject(const CommandButton *button, Object *target,
		CommandSourceType source, Bool playVoiceResponse);
};

extern ScriptEngine *TheScriptEngine;
extern ControlBar *TheControlBar;

class ScriptActions
{
protected:
	void doNamedUseCommandButtonAbilityOnNamed(const AsciiString &unit,
		const AsciiString &ability, const AsciiString &target);
};

// ?doNamedUseCommandButtonAbilityOnNamed@ScriptActions@@IAEXABVAsciiString@@00@Z
void ScriptActions::doNamedUseCommandButtonAbilityOnNamed(
	const AsciiString &unit, const AsciiString &ability,
	const AsciiString &target)
{
	Object *theObj = TheScriptEngine->getUnitNamed(unit);
	Object *theTarget = TheScriptEngine->getUnitNamedByValue(target);

	if (!theObj || !theTarget)
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
					theObj->doCommandButtonAtObject(commandButton, theTarget,
						CMD_FROM_SCRIPT, false);
				}
			}
		}
	}
}
