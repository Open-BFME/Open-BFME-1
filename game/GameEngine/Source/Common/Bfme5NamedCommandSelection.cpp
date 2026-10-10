struct BfmeAsciiData
{
	char m_bfmeFields[4];
	unsigned short m_bfmeLength;
};

// retail 0x28B360 assigns the name with a direct call to 0x887C90
// ?set@?$StringBase@D@@QAEXABV1@@Z
template <class T>
class StringBase
{
public:
	void set(const StringBase &other);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : public StringBase<char>
{
public:
	int compare(const AsciiString &other) const;

	bool bfmeHasText(void) const
	{
		return m_bfmeData != 0 && m_bfmeData->m_bfmeLength != 0;
	}

private:
	BfmeAsciiData *m_bfmeData;
};

#include "../GameLogic/command_source_type.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const AsciiString &getCommandSetString(void) const;

	char m_bfmeFields[0x204];
	BfmeAIHolder *m_bfmeAI;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	char m_bfmeFields[0x0C];
	AsciiString m_bfmeName;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandSet
{
public:
	const CommandButton *getCommandButton(int index) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
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

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 0
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
protected:
	// retail 0x28B360 calls ILT 0x157DA -> 0x2B2040 ?setWakeFrame@UpdateModule@@IAEXPAVObject@@W4UpdateSleepTime@@@Z
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
};

class Gen_0028B360 : public UpdateModule
{
public:
	void bfmeSelect(const AsciiString &name);

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
	m_bfmeName.set(name);
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
		object->m_bfmeAI->m_bfmeCommands.aiIdle(CMD_FROM_AI);
		m_bfmeReset.bfmeReset();
		setWakeFrame(object, (UpdateSleepTime)1);
	}
}
