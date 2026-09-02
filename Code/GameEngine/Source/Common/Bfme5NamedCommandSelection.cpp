struct BfmeAsciiData
{
	char m_bfmeFields[4];
	unsigned short m_bfmeLength;
};

class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);
	int compare(const AsciiString &other) const;

	bool bfmeHasText(void) const
	{
		return m_bfmeData != 0 && m_bfmeData->m_bfmeLength != 0;
	}

private:
	BfmeAsciiData *m_bfmeData;
};

enum CommandSourceType
{
	COMMAND_SOURCE_SCRIPT = 2
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

class Object
{
public:
	const AsciiString &getCommandSetString(void) const;

	char m_bfmeFields[0x204];
	BfmeAIHolder *m_bfmeAI;
};

class CommandButton
{
public:
	char m_bfmeFields[0x0C];
	AsciiString m_bfmeName;
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

class BfmeResetInterface
{
public:
	virtual void bfmeReset(void);
};

class Gen_0028B360
{
public:
	void bfmeSelect(const AsciiString &name);
	void bfmeFinish(Object *object, int enabled);

private:
	char m_bfmeFields[8];
	Object *m_bfmeObject;
	char m_bfme0C[4];
	BfmeResetInterface m_bfmeReset;
	char m_bfme14[0x0C];
	AsciiString m_bfmeName;
	const CommandButton *m_bfmeSelected;
};

// ?bfmeSelect@Gen_0028B360@@QAEXABVAsciiString@@@Z
void Gen_0028B360::bfmeSelect(const AsciiString &name)
{
	Object *object = m_bfmeObject;
	m_bfmeName = name;
	m_bfmeSelected = 0;

	const AsciiString &commandSetName = object->getCommandSetString();
	const CommandSet *commandSet = TheControlBar->findCommandSet(commandSetName);
	if (commandSet != 0) {
		for (int index = 0; index < 20; ++index) {
			m_bfmeSelected = commandSet->getCommandButton(index);
			if (m_bfmeSelected != 0 && m_bfmeSelected->m_bfmeName.bfmeHasText() &&
				m_bfmeSelected->m_bfmeName.compare(m_bfmeName) == 0)
				break;
			m_bfmeSelected = 0;
		}
	}

	if (m_bfmeSelected != 0 && object->m_bfmeAI != 0) {
		object->m_bfmeAI->m_bfmeCommands.aiIdle(COMMAND_SOURCE_SCRIPT);
		m_bfmeReset.bfmeReset();
		bfmeFinish(object, 1);
	}
}
