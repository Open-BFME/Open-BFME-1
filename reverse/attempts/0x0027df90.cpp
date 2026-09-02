// ?d_0027df90@@YAXXZ
// partial score=0.85 date=2026-09-03
class AsciiString;

enum CommandSourceType
{
	COMMAND_SOURCE_UNKNOWN = 0
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType source);
};

struct BfmeAIHolder
{
	char m_bfmeFields[0x20];
	AICommandInterface m_bfmeCommands;
};

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride(void);

	char m_bfmeFields[4];
	BfmeOverridable *m_bfmeNext;
	char m_bfme08[0xC0];
	unsigned int m_bfmeFlags;
};

class Object
{
public:
	const AsciiString &getCommandSetString(void) const;

	char m_bfmeFields[4];
	BfmeOverridable *m_bfmeOverride;
	char m_bfme08[0x1FC];
	BfmeAIHolder *m_bfmeAI;
};

class CommandButton
{
	public:
	char m_bfmeFields[0x10];
	int m_bfmeType;
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int index) const;
};

class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);
};

extern ControlBar *TheControlBar;

class Gen_0027DF90
{
public:
	void bfmeIdleForButton(const CommandButton * volatile button, CommandSourceType source);

private:
	char m_bfmeFields[8];
	Object *m_bfmeObject;
};

// ?bfmeIdleForButton@Gen_0027DF90@@QAEXPBVCommandButton@@W4CommandSourceType@@@Z
void Gen_0027DF90::bfmeIdleForButton(const CommandButton * volatile button,
	CommandSourceType source)
{
	if (button == 0)
		return;

	Object *object = m_bfmeObject;
	BfmeOverridable *resolved = object->m_bfmeOverride;
	if (resolved != 0 && resolved->m_bfmeNext != 0)
		resolved = resolved->m_bfmeNext->friend_getFinalOverride();

	if ((resolved->m_bfmeFlags & 0x02000000) || object == 0)
		return;
	BfmeAIHolder *ai = object->m_bfmeAI;
	if (ai == 0)
		return;

	const AsciiString &name = object->getCommandSetString();
	const CommandSet *commandSet = TheControlBar->findCommandSet(name);
	if (commandSet == 0)
		return;

	CommandSourceType idleSource = source;
	for (int index = 0; index < 20; ++index) {
		const CommandButton *candidate = commandSet->getCommandButton(index);
		if (candidate == button && button->m_bfmeType == 13)
			ai->m_bfmeCommands.aiIdle(idleSource);
	}
}
