// BFME 1.03 Object::checkNoCollisionsStatus at RVA 0x001CE7F0.

enum ObjectStatusTypes
{
	OBJECT_STATUS_NO_COLLISIONS = 4
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
	void checkNoCollisionsStatus(void);

private:
	unsigned char m_beforeNoCollisionsUntil[0x33C];
	unsigned int m_noCollisionsUntil;
};

void Object::checkNoCollisionsStatus(void)
{
	unsigned int until = m_noCollisionsUntil;
	if (until > 0 && TheGameLogic->getFrame() > until)
	{
		clearStatus(OBJECT_STATUS_NO_COLLISIONS);
		m_noCollisionsUntil = 0;
	}
}
