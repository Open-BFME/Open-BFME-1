typedef bool Bool;

class GameMessage
{
public:
	void appendBooleanArgument(Bool value);
};

class MessageStream
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12();
	virtual GameMessage *appendMessage(int type);
};

class InGameUI
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57();
	virtual void clearAttackMoveToMode();

	void setInputEnabled(Bool enabled);

private:
	unsigned char m_fields[0x12B0 - 4];

public:
	Bool m_waypointMode;
};

class Mouse
{
public:
	void setVisibility(Bool visible);
};

class ControlBar
{
public:
	void deleteBuildTooltipLayout();
};

class LookAtTranslator
{
public:
	void resetModes();
};

extern InGameUI *TheInGameUI;
extern Mouse *TheMouse;
extern MessageStream *TheMessageStream;
extern ControlBar *TheControlBar;
extern LookAtTranslator *TheLookAtTranslator;

class ScriptActions
{
protected:
	void doDisableInput();
};

void ScriptActions::doDisableInput()
{
	TheInGameUI->setInputEnabled(false);
	TheMouse->setVisibility(false);
	GameMessage *message = TheMessageStream->appendMessage(0x3EB);
	message->appendBooleanArgument(true);
	TheInGameUI->clearAttackMoveToMode();
	TheInGameUI->m_waypointMode = false;
	TheControlBar->deleteBuildTooltipLayout();
	TheLookAtTranslator->resetModes();
}
