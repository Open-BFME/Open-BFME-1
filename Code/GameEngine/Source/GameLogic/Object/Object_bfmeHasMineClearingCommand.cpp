// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
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

struct AsciiStringBuffer
{
	UnsignedInt m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
private:
	AsciiStringBuffer *m_buffer;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	UnsignedInt getOptions() const
	{
		return m_options;
	}

private:
	unsigned char m_unmodelled_000[0x18];
	UnsignedInt m_options;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandSet
{
public:
	const CommandButton *getCommandButton(Int index) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);
};

extern ControlBar *TheControlBar;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool bfmeHasMineClearingCommand() const;

private:
	void *m_vtable;
	Overridable *m_template;
	unsigned char m_unmodelled_008[0x328 - 0x08];
	AsciiStringBuffer *m_commandSetFallback;
	AsciiStringBuffer *m_commandSetOverride;
};

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
		for (Int index = 0; index < 20; ++index)
		{
			const CommandButton *button = commandSet->getCommandButton(index);
			if (button && (button->getOptions() & 0x00200000) != 0)
				return true;
		}
	}
	return false;
}
