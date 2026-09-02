// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef int ObjectID;

class Drawable;
class Object;

class GameClient
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual Drawable *findDrawableByID(ObjectID id);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

class LivingWorldOwnerLookup
{
public:
	void *findOwnerByID(ObjectID id);
};

extern GameClient *TheGameClient;
extern GameLogic *TheGameLogic;
extern LivingWorldOwnerLookup *TheLivingWorldOwnerLookup;

class AudioEventRTS
{
public:
	bool isDead() const;

private:
	unsigned char m_pad00[0x2C];
	ObjectID m_ownerID;
	int m_ownerType;
};

bool AudioEventRTS::isDead() const
{
	switch (m_ownerType)
	{
	case 1:
		return TheGameClient->findDrawableByID(m_ownerID) == 0;
	case 2:
		return TheGameLogic->findObjectByID(m_ownerID) == 0;
	case 5:
		return TheLivingWorldOwnerLookup == 0 ||
			TheLivingWorldOwnerLookup->findOwnerByID(m_ownerID) == 0;
	default:
		return false;
	}
}
