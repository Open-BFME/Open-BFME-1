// ?privateCommandButton@AIUpdatePrivateCommandButtonShim@@QAEXPBVCommandButton@@W4CommandSourceType@@@Z
// partial score=0.91 date=2026-09-04
// cl: /DNDEBUG /MD /EHs-c-
// AIUpdatePrivateCommandButtonShim::privateCommandButton — retail 0x0027DF90 / 140B.
// Dump sibling of setAttitude in Code/gen_asm/d_0027db50.asm.
// ZH: AIUpdateInterface::privateCommandButton (AIUpdate.cpp present-unmatched).
// BFME: MAX_COMMANDS_PER_SET is 20; getCommandType is the dword at button+0x10;
// GUI_COMMAND_STOP is 0xD.  The projectile reject is getFinalOverride on the
// ThingTemplate at Object+4, then bit 0x2000000 at template+0xC8.
// upstream: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

enum { MAX_COMMANDS_PER_SET = 20 };

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum GUICommandType
{
	GUI_COMMAND_STOP = 0xD
};

class AsciiString;
class CommandButton;
class CommandSet;
class ControlBar;
class Overridable;
class Object;
class AICommandInterface;

class AIUpdatePrivateCommandButtonShim
{
public:
	void privateCommandButton(const CommandButton *commandButton, CommandSourceType cmdSource);

	unsigned char m_beforeObject[8];
	Object * volatile m_object;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	unsigned char m_beforeNext[4];
	Overridable *m_next;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_beforeKindOf[0xC8 - 8];
	unsigned int m_kindOf;
};

class Object
{
public:
	const AsciiString &getCommandSetString() const;

	unsigned char m_beforeTemplate[4];
	ThingTemplate *m_template;
	unsigned char m_beforeAI[0x204 - 8];
	AICommandInterface *m_ai;
};

class CommandButton
{
public:
	GUICommandType getCommandType() const { return m_command; }

	unsigned char m_beforeType[0x10];
	GUICommandType m_command;
};

inline bool isStopButton(const CommandButton *button)
{
	return button->getCommandType() == GUI_COMMAND_STOP;
}

class CommandSet
{
public:
	const CommandButton *getCommandButton(int i) const;
};

class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmd);
};

ControlBar *TheControlBar;

void AIUpdatePrivateCommandButtonShim::privateCommandButton(const CommandButton *commandButton, CommandSourceType cmdSource)
{
	if (!*(const CommandButton * volatile *)&commandButton)
		return;

	Object *owner = reinterpret_cast<Object *>(reinterpret_cast<unsigned int>(m_object) + 0);
	volatile unsigned char *objectBytes = reinterpret_cast<volatile unsigned char *>(owner);
	objectBytes += 4;
	ThingTemplate *tmpl = *reinterpret_cast<ThingTemplate * volatile *>(objectBytes);
	if (tmpl)
	{
		Overridable *next = tmpl->m_next;
		if (next)
			tmpl = static_cast<ThingTemplate *>(const_cast<Overridable *>(next->getFinalOverride()));
	}
	if (tmpl->m_kindOf & 0x2000000)
		return;
	if (owner)
	{
		const CommandSet *commandSet;
		AICommandInterface *ai = owner->m_ai;
		if (ai)
		{
			commandSet = TheControlBar->findCommandSet(owner->getCommandSetString());
			if (commandSet)
			{
				CommandSourceType src = cmdSource;
				for (int i = 0; i < MAX_COMMANDS_PER_SET; ++i)
				{
					const CommandButton *aCommandButton = commandSet->getCommandButton(i);
					if (aCommandButton == *(const CommandButton * volatile *)&commandButton &&
						isStopButton(*(const CommandButton * volatile *)&commandButton))
						reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(ai) + 0x20)->aiIdle(src);
				}
			}
		}
	}
}
