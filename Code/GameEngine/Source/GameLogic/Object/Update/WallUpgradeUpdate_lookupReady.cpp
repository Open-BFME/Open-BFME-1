// cl: /DNDEBUG /MD /EHsc
// Retail 0x002B25A0: look up the object id at +0x28, reject a missing or
// effectively-dead object, then return the inverse of model-condition bit 4.

typedef int ObjectID;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	unsigned char m_pad000[0x118];
	unsigned int m_modelCondition;	// +0x118
	unsigned char m_pad11c[0x344 - 0x11C];
	unsigned char m_privateStatus;	// +0x344
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class WallUpgradeUpdate
{
public:
	bool isPartnerReady(void) const;

private:
	unsigned char m_pad[0x28];
	ObjectID m_id;	// +0x28
};

bool WallUpgradeUpdate::isPartnerReady(void) const
{
	Object *obj = TheGameLogic->findObjectByID(m_id);
	if (obj)
	{
		if ((obj->m_privateStatus & 1) == 0)
			return (~(obj->m_modelCondition >> 4)) & 1;
	}
	return false;
}
