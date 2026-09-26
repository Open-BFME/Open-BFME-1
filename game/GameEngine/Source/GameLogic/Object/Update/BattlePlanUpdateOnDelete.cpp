// cl: /DNDEBUG /MD /EHsc

// BattlePlanUpdate::onDelete. Ported from the Zero Hour source of the same
// class onto the BFME object layout: the vision object is released through
// TheGameLogic and the plan bonus is withdrawn from the controlling player.

class Object;
class Player;
class BattlePlanBonuses;

enum BattlePlanStatus
{
	PLANSTATUS_NONE = 0
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
	void destroyObject(Object *obj);
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	Player *getControllingPlayer(void) const;
};

class Player
{
public:
	void changeBattlePlan(BattlePlanStatus plan, int count, BattlePlanBonuses *bonuses);
};

class BattlePlanUpdate
{
public:
	virtual void onDelete(void);

private:
	Object *getObject(void) const { return m_object; }

	int m_pad04;
	Object *m_object;
	char m_pad0C[0x20];
	BattlePlanStatus m_planAffectingArmy;
	char m_pad30[0x10];
	BattlePlanBonuses *m_bonuses;
	char m_pad44[0x700];
	int m_visionObjectID;
};

void BattlePlanUpdate::onDelete(void)
{
	Object *obj;
	if (m_visionObjectID != 0)
	{
		GameLogic *logic = TheGameLogic;

		obj = logic->findObjectByID(m_visionObjectID);
		if (obj)
			logic->destroyObject(obj);
	}

	Player *player = getObject()->getControllingPlayer();
	if (player && m_planAffectingArmy != PLANSTATUS_NONE)
	{
		player->changeBattlePlan(m_planAffectingArmy, -1, m_bonuses);
	}
}
