// ?doRemoveCommandBarButton@ScriptActions@@IAEXABVAsciiString@@0@Z
// partial score=0.78 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// Clean C++ recovery of REMOVE_COMMANDBAR_BUTTON.
// Retail RVA 0x002FC570 (463 bytes); executeAction's
// COMMANDBAR_REMOVE_BUTTON_OBJECTTYPE arm names this body.  BFME removes
// matching buttons from the primary command set and from related behavior
// module command sets.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;

class CommandButton;
class CommandSet;
class ThingTemplate;
class ThingFactory;

class CommandSetShim
{
public:
	const CommandButton *getCommandButton(Int index) const;
};

// BFME stores a CommandButton's name at +0x0c (the ZH layout is different).
class BfmeCommandButtonName
{
public:
	const AsciiString &getName() const { return m_name; }

private:
	unsigned char m_beforeName[0x0c];
	AsciiString m_name;
};

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

class GameLogic
{
public:
	void setControlBarOverride(const AsciiString &commandSetName, Int slot,
		const CommandButton *commandButton);
};

extern ThingFactory *TheThingFactory;
extern ControlBar *TheControlBar;
extern GameLogic *TheGameLogic;

// ModuleInfo::Nugget is private in the reference headers.  This is the
// proven BFME storage view: two AsciiStrings, the ModuleData pointer at +8,
// and 0x14-byte records.  Only the vector bounds and the data pointer are
// used here; the remaining fields are deliberately not interpreted.
struct BfmeModuleInfoNugget
{
	AsciiString m_name;
	AsciiString m_moduleTag;
	const void *m_moduleData;
	Int m_interfaceMask;
	Bool m_copiedFromDefault;
	Bool m_inheritable;
	Bool m_overrideableByLikeKind;
};

struct BfmeModuleInfo
{
	BfmeModuleInfoNugget *m_begin;
	BfmeModuleInfoNugget *m_finish;
	BfmeModuleInfoNugget *m_capacity;
};

// The retail call is a virtual at vtable byte offset +0x3c on the module
// data.  Its result is an object whose command-set anchor is at +0x70.  The
// anchor itself is the base used by this view: its AsciiString is at offset
// zero and its behavior ModuleInfo begins at +0x294.  This names only the
// observed ABI, not an invented BFME module class.
class BfmeModuleDataView
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
	virtual const void *getRelatedOwner() const = 0;
};

class BfmeModuleOwner
{
public:
	const AsciiString &commandSetName() const { return m_commandSetName; }
	const BfmeModuleInfo &behaviorModuleInfo() const { return m_behavior; }

private:
	AsciiString m_commandSetName;
	char m_padToBehavior[0x290];
	BfmeModuleInfo m_behavior;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class BfmeThingTemplate
{
public:
	const AsciiString &commandSetName() const { return m_commandSetName; }
	const BfmeModuleInfo &behaviorModuleInfo() const { return m_behavior; }

private:
	char m_padToCommandSet[0x2c];
	AsciiString m_commandSetName;
	char m_padToBehavior[0x264];
	BfmeModuleInfo m_behavior;
};

struct BfmeAsciiStringData
{
	unsigned int m_refCount;
	unsigned short m_numChars;
	unsigned short m_numCharsAllocated;
};

extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);

// The related-set path uses the BFME inline string representation directly:
// data+4 is the character count and data+8 is the character storage.  The
// fixed empty-string address and length subtraction are visible in retail.
static __forceinline Int bfmeCompareButtonName(const AsciiString &buttonName,
	const AsciiString &requestedName)
{
	const BfmeAsciiStringData *buttonData =
		*(const BfmeAsciiStringData * const *)&buttonName;
	const BfmeAsciiStringData *requestedData =
		*(const BfmeAsciiStringData * const *)&requestedName;
	unsigned int buttonLength = buttonData ? buttonData->m_numChars : 0;
	unsigned int requestedLength = requestedData ? requestedData->m_numChars : 0;
	const char *buttonText = buttonData ? (const char *)(buttonData + 1)
		: (const char *)0x0107388b;
	const char *requestedText = requestedData ? (const char *)(requestedData + 1)
		: (const char *)0x0107388b;
	unsigned int commonLength = buttonLength < requestedLength
		? buttonLength : requestedLength;
	Int result = memcmp(buttonText, requestedText, commonLength);
	if (result != 0)
		return result;
	return (Int)buttonLength - (Int)requestedLength;
}

// Keep the button subobject address live until after the second lookup.  The
// retail sequence adds +0x0c to that pointer before loading its AsciiString
// data, rather than materializing the reference through a C++ accessor first.
static __forceinline Int bfmeCompareCommandButton(const CommandButton *button,
	const AsciiString &requestedName)
{
	const AsciiString *buttonName =
		(const AsciiString *)((const char *)button + 0x0c);
	const BfmeAsciiStringData *requestedData =
		*(const BfmeAsciiStringData * const *)&requestedName;
	unsigned int requestedLength = requestedData
		? requestedData->m_numChars : 0;
	const char *requestedText = requestedData
		? (const char *)(requestedData + 1)
		: (const char *)0x0107388b;
	const BfmeAsciiStringData *buttonData =
		*(const BfmeAsciiStringData * const *)buttonName;
	unsigned int buttonLength = buttonData ? buttonData->m_numChars : 0;
	const char *buttonText = buttonData ? (const char *)(buttonData + 1)
		: (const char *)0x0107388b;
	unsigned int commonLength = buttonLength < requestedLength
		? buttonLength : requestedLength;
	Int result = memcmp(buttonText, requestedText, commonLength);
	if (result != 0)
		return result;
	return (Int)buttonLength - (Int)requestedLength;
}

class ScriptActions
{
protected:
	void doRemoveCommandBarButton(const AsciiString &, const AsciiString &);
};

// ?doRemoveCommandBarButton@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doRemoveCommandBarButton(const AsciiString &buttonName,
	const AsciiString &objectType)
{
	Int offset;
	const AsciiString *commandSetNamePtr;
	const BfmeThingTemplate *thingTemplate =
		(const BfmeThingTemplate *)((BfmeThingFactory *)TheThingFactory)->findTemplate(objectType);
	if (!thingTemplate)
		return;

	commandSetNamePtr = &thingTemplate->commandSetName();
	const AsciiString &commandSetName = *commandSetNamePtr;
	const CommandSet *commandSet = TheControlBar->findCommandSet(commandSetName);
	if (commandSet)
	{
		for (Int slot = 0; slot < 20; ++slot)
		{
			if (((const CommandSetShim *)commandSet)->getCommandButton(slot) &&
				((const AsciiStringCompareShim *)&((const BfmeCommandButtonName *)
					((const CommandSetShim *)commandSet)->getCommandButton(slot))->getName())
					->compare(buttonName) == 0)
			{
				TheGameLogic->setControlBarOverride(commandSetName, slot, 0);
			}
		}
	}

	BfmeModuleInfoNugget *nugget =
		thingTemplate->behaviorModuleInfo().m_begin;
	BfmeModuleInfoNugget *end =
		thingTemplate->behaviorModuleInfo().m_finish;
	Int count = end - nugget;
	Int index = 0;
	offset = 0;
	while (offset >= 0 && index < count)
	{
		const BfmeModuleDataView *moduleData =
			*(const BfmeModuleDataView **)(offset + (unsigned int)nugget + 8);
		if (moduleData)
		{
			const char *ownerBase =
				(const char *)moduleData->getRelatedOwner();
			if (ownerBase)
			{
				const AsciiString &relatedName =
					*(const AsciiString *)(ownerBase + 0x70);
				const CommandSet *relatedSet =
					TheControlBar->findCommandSet(relatedName);
				if (relatedSet)
				{
					for (Int slot = 0; slot < 20; ++slot)
					{
						if (((const CommandSetShim *)relatedSet)->getCommandButton(slot) &&
							bfmeCompareCommandButton(
								((const CommandSetShim *)relatedSet)->getCommandButton(slot),
								buttonName) == 0)
						{
							TheGameLogic->setControlBarOverride(relatedName, slot, 0);
						}
					}
				}
			}
		}

		++index;
		offset += sizeof(BfmeModuleInfoNugget);
	}
}


