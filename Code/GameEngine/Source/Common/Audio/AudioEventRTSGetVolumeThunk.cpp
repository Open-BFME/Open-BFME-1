// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AudioEventRTS::getVolume, retail 0x000B4960.

struct AudioEventInfoSlice
{
	char m_pad[0x18];
	float m_volume;
};

class Object
{
public:
	char m_pad[0x94];
	unsigned int m_statusFlags;
};

class Drawable
{
public:
	char m_pad[0x143];
	bool m_audible;
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
	float getVolume() const;
private:
	char m_pad0[8];
	const AudioEventInfoSlice *m_eventInfo;
	char m_pad1[0x18];
	float m_volume;
	char m_pad2[4];
	unsigned int m_ownerID;
	int m_ownerType;
};

float AudioEventRTS::getVolume() const
{
	switch (m_ownerType)
	{
		case 2:
		{
			Object *object = TheGameLogic->findObjectByID(m_ownerID);
			if (object != 0 && (object->m_statusFlags & 0x00080000) != 0)
				return 0.0f;
			break;
		}
		case 1:
		{
			Drawable *drawable = TheGameClient->findDrawableByID(m_ownerID);
			if (drawable != 0 && !drawable->m_audible)
				return 0.0f;
			break;
		}
	}

	if (m_volume == -1.0f)
	{
		if (m_eventInfo != 0)
			return m_eventInfo->m_volume;
		return 0.0f;
	}
	return m_volume;
}
