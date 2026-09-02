// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AudioEventRTS::getPlayerIndex, retail 0x000B4290.

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }
private:
	char m_pad[0x24];
	int m_playerIndex;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Drawable
{
public:
	Object *getObject() { return m_object; }
private:
	char m_pad[0xfc];
	Object *m_object;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class GameClient
{
public:
	virtual void vf00() = 0;
	virtual void vf04() = 0;
	virtual void vf08() = 0;
	virtual void vf0c() = 0;
	virtual void vf10() = 0;
	virtual void vf14() = 0;
	virtual void vf18() = 0;
	virtual void vf1c() = 0;
	virtual void vf20() = 0;
	virtual void vf24() = 0;
	virtual void vf28() = 0;
	virtual Drawable *findDrawableByID(unsigned int id) = 0;
};

extern GameLogic *TheGameLogic;
extern GameClient *TheGameClient;

class AudioEventRTS
{
public:
	int getPlayerIndex() const;
private:
	char m_pad0[0x2c];
	unsigned int m_ownerID;
	int m_ownerType;
	char m_pad1[0x28];
	int m_playerIndex;
};

int AudioEventRTS::getPlayerIndex() const
{
	Object *object = 0;
	if (m_ownerType == 2)
	{
		object = TheGameLogic->findObjectByID(m_ownerID);
	}
	else if (m_ownerType == 1)
	{
		Drawable *drawable = TheGameClient->findDrawableByID(m_ownerID);
		if (drawable != 0)
			object = drawable->getObject();
	}

	if (object != 0)
		return object->getControllingPlayer()->getPlayerIndex();
	return m_playerIndex;
}
