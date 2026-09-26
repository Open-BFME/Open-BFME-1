// ?resolveOwnerPosition@AudioEventRTS@@QAEXPAUCoord3D@@PA_N@Z
// partial score=0.78 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Open-BFME5: AudioEventRTS::resolveOwnerPosition, retail 0x000B4020.
// The owner constructors at 0x000B4350, 0x000B44F0, and 0x000B4690 all call
// this body, as do their outlined twins.  Keep the retail owner-position
// layout local to this TU; the common AudioEventRTS header is intentionally
// not changed for a single recovered body.

typedef int ObjectID;

struct Coord3D
{
	float x, y, z;

	void set(const Coord3D *other)
	{
		x = other->x;
		y = other->y;
		z = other->z;
	}

	void set(float xValue, float yValue, float zValue)
	{
		x = xValue;
		y = yValue;
		z = zValue;
	}
};

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_position;

	const Coord3D *getPosition() const { return &m_position; }
};

class Drawable
{
public:
	const Coord3D *getPosition() const;
};

class GameClient
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual Drawable *findDrawableByID(ObjectID id);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

class LivingWorldOwner
{
public:
	char m_pad00[0x0c];
	float m_x;
	float m_y;
};

class LivingWorldOwnerLookup
{
public:
	void *findOwnerByID(ObjectID id);
};

extern GameLogic *TheBfmeGameLogic;
extern GameClient *TheGameClient;
extern void *Glo012F1028;

class AudioEventRTS
{
public:
	void resolveOwnerPosition(Coord3D *pos, bool *found);

private:
	char m_pad00[0x2c];
	ObjectID m_ownerID;
	int m_ownerType;
	Coord3D m_position;
	volatile bool m_found;
};

void AudioEventRTS::resolveOwnerPosition(Coord3D *pos, bool *found)
{
	volatile Coord3D ownerPosition;

	switch (m_ownerType)
	{
	case 0:
		*found = true;
		pos->x = m_position.x;
		pos->y = m_position.y;
		pos->z = m_position.z;
		return;

	case 2:
		{
			Object *object = TheBfmeGameLogic->findObjectByID(m_ownerID);
			if (object != 0)
			{
				m_found = 1;
				m_position.set(object->getPosition());
				*found = m_found;
				pos->x = m_position.x;
				pos->y = m_position.y;
				pos->z = m_position.z;
				return;
			}
		}
		break;

	case 1:
		{
			Drawable *drawable = TheGameClient->findDrawableByID(m_ownerID);
			if (drawable != 0)
			{
				m_found = 1;
				m_position.set(drawable->getPosition());
				*found = m_found;
				pos->x = m_position.x;
				pos->y = m_position.y;
				pos->z = m_position.z;
				return;
			}
		}
		break;

	case 5:
		if (Glo012F1028 != 0)
		{
			LivingWorldOwner *owner = (LivingWorldOwner *)
				((LivingWorldOwnerLookup *)Glo012F1028)->findOwnerByID(m_ownerID);
			if (owner != 0)
			{
				m_found = 1;
				m_position.x = owner->m_x;
				ownerPosition.x = m_position.x;
				ownerPosition.z = 0.0f;
				m_position.y = owner->m_y;
				ownerPosition.y = m_position.y;
				m_position.z = ownerPosition.z;
				*found = m_found;
				pos->x = m_position.x;
				pos->y = m_position.y;
				pos->z = m_position.z;
				return;
			}
		}
		break;
	}

	*found = false;
	pos->x = 0.0f;
	pos->y = 0.0f;
	pos->z = 0.0f;
}
