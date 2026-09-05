// BFME 1.03 Object::checkIgnoreAICommandStatus at RVA 0x001CE7B0.

enum ObjectStatusTypes
{
	OBJECT_STATUS_IGNORE_AI_COMMAND = 73
};

class GameLogic
{
private:
	unsigned char m_beforeFrame[0x3C];

public:
	unsigned int m_frame;
	unsigned int getFrame(void) const { return m_frame; }
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	void clearStatus(ObjectStatusTypes status);
	void checkIgnoreAICommandStatus(void);

private:
	unsigned char m_beforeIgnoreAICommandUntil[0x338];
	unsigned int m_ignoreAICommandUntil;
};

void Object::checkIgnoreAICommandStatus(void)
{
	unsigned int until = m_ignoreAICommandUntil;
	if (until > 0 && TheGameLogic->getFrame() > until)
	{
		clearStatus(OBJECT_STATUS_IGNORE_AI_COMMAND);
		m_ignoreAICommandUntil = 0;
	}
}
