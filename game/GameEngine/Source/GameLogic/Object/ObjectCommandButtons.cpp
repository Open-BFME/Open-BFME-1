// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// The two Object bodies that walk this object's command set:
//
//   bfmeCanUseCommandButton   0x001C4A30  is this exact button in our set
//   bfmeHasMineClearingCommand 0x001C4780  does our set hold a mine-clearing one
//
// Both ask TheControlBar for the command set by name and then scan the same
// twenty slots. They sat in two files with two accounts of everything they share.
//
// CommandButton was the clearest case of the shape this tree keeps producing:
// each file padded blindly to the one field it wanted and stopped.
// bfmeCanUseCommandButton declared `unsigned char m_unreconstructed[0x34]` and
// then m_specialPower; bfmeHasMineClearingCommand declared
// `unsigned char m_unmodelled_000[0x18]` and then m_options. Neither is wrong and
// neither could see the other, because a pad is not a claim. One CommandButton
// here names m_options at +0x18 and m_specialPower at +0x34, with the pad only
// between them.
//
// AsciiString went the same way: an empty `class AsciiString {}` in one file, and
// a fully written-out refcount/length/capacity buffer in the other. The buffer is
// here once.
//
// The interesting difference is that these two bodies get the command-set NAME
// differently, and that is retail's doing, not the files'. bfmeCanUseCommandButton
// calls Object::getCommandSetString() out of line; bfmeHasMineClearingCommand
// carries that accessor's body inlined, which is what exposes the three fields it
// picks between -- the override at +0x32C, the fallback at +0x328, and, when
// neither has a length, the name at +0x2C of the template's final override, reached
// from m_template at +0x04. So the merged Object declares the accessor AND names
// the fields it reads, which is more than either file could say on its own.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
struct AsciiStringBuffer
{
	UnsignedInt m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	const Overridable *bfmeFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	void *m_vtable;
	Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	UnsignedInt getOptions() const
	{
		return m_options;
	}

	const SpecialPowerTemplate *getSpecialPowerTemplate() const
	{
		return m_specialPower;
	}

private:
	unsigned char m_unmodelled_000[0x18];
	UnsignedInt m_options;				// +0x18
	unsigned char m_unmodelled_01c[0x34 - 0x1c];
	const SpecialPowerTemplate *m_specialPower;	// +0x34
};

// The mine-clearing bit in CommandButton::getOptions.
enum { COMMAND_OPTION_MINE_CLEARING = 0x00200000 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandSet
{
public:
	const CommandButton *getCommandButton(Int index) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);
};

extern ControlBar *TheControlBar;

// Both bodies scan exactly this many slots.
enum { MAX_COMMANDS_PER_SET = 20 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool b_001c4710() const;
	Bool bfmeCanUseCommandButton(const CommandButton *button) const;
	Bool bfmeHasMineClearingCommand() const;

	// Called out of line by the first body and carried inlined by the second.
	const AsciiString &getCommandSetString() const;

	SpecialPowerModuleInterface *getSpecialPowerModule(
		const SpecialPowerTemplate *specialPowerTemplate) const;

private:
	void *m_vtable;
	Overridable *m_template;			// +0x004
	unsigned char m_unmodelled_008[0x28c - 0x08];
	volatile UnsignedInt m_28c;
	unsigned char m_unmodelled_290[0x328 - 0x290];
	AsciiStringBuffer *m_commandSetFallback;	// +0x328
	AsciiStringBuffer *m_commandSetOverride;	// +0x32C
};

// The caller in Rva00459060SelectionFlags.cpp names this as an Object method.
// The command-set and command-button thunks provide the remaining call-site evidence.
Bool Object::b_001c4710() const
{
	unsigned int flags = m_28c;
	unsigned char shifted = (unsigned char)(flags >> 6);
	if (shifted & 1)
		return true;

	const CommandSet *set = TheControlBar->findCommandSet(getCommandSetString());
	if (set != 0)
	{
		for (Int index = 0; index < MAX_COMMANDS_PER_SET; ++index)
		{
			const CommandButton *button = set->getCommandButton(index);
			if (button != 0 && (*((const unsigned char *)button + 0x18) & 0x10) != 0)
				return true;
		}
	}
	return false;
}

// ?bfmeCanUseCommandButton@Object@@QBE_NPBVCommandButton@@@Z
//
// A button with a special-power template must have a matching module on this
// Object, and the exact button pointer must be present in the current set.
Bool Object::bfmeCanUseCommandButton(const CommandButton *button) const
{
	const SpecialPowerTemplate *power = button->getSpecialPowerTemplate();
	if (power != 0 && getSpecialPowerModule(power) == 0)
		return false;

	const CommandSet *set = TheControlBar->findCommandSet(getCommandSetString());
	if (set != 0)
	{
		for (Int index = 0; index < MAX_COMMANDS_PER_SET; ++index)
		{
			if (set->getCommandButton(index) == button)
				return true;
		}
	}
	return false;
}

// ?bfmeHasMineClearingCommand@Object@@QBE_NXZ
//
// The command-set name is chosen here rather than through the accessor: override
// first, then fallback, then the template's final override.
Bool Object::bfmeHasMineClearingCommand() const
{
	const AsciiString *commandSetName;
	if (m_commandSetOverride && m_commandSetOverride->m_length != 0)
	{
		commandSetName = reinterpret_cast<const AsciiString *>(
			&m_commandSetOverride);
	}
	else if (m_commandSetFallback && m_commandSetFallback->m_length != 0)
	{
		commandSetName = reinterpret_cast<const AsciiString *>(
			&m_commandSetFallback);
	}
	else
	{
		const Overridable *templateObject = m_template;
		if (templateObject)
			templateObject = templateObject->bfmeFinalOverride();
		commandSetName = reinterpret_cast<const AsciiString *>(
			reinterpret_cast<const char *>(templateObject) + 0x2c);
	}

	const CommandSet *commandSet =
		TheControlBar->findCommandSet(*commandSetName);
	if (commandSet)
	{
		for (Int index = 0; index < MAX_COMMANDS_PER_SET; ++index)
		{
			const CommandButton *button = commandSet->getCommandButton(index);
			if (button && (button->getOptions() & COMMAND_OPTION_MINE_CLEARING) != 0)
				return true;
		}
	}
	return false;
}
