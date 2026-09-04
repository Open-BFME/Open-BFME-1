// ?onDelete@BattlePlanUpdate@@UAEXXZ
// partial score=0.92 date=2026-09-04
class BfmeReleasedItem;

class GameLogicFrameSlice
{
public:
	BfmeReleasedItem *bfmeFind(int handle);
	void bfmeDrop(BfmeReleasedItem *item);
};

extern GameLogicFrameSlice *TheGameLogic;

enum BattlePlanStatus
{
	BATTLE_PLAN_NONE = 0
};

class BattlePlanBonuses;

class Player
{
public:
	void changeBattlePlan(BattlePlanStatus status, int mode, BattlePlanBonuses *bonuses);
};

class BfmeResolutionKey
{
public:
	Player *bfmeResolve(void);
};

class BattlePlanUpdate
{
public:
	virtual void onDelete(void);

private:
	char m_bfmeFields[4];
	BfmeResolutionKey *m_bfmeKey;
	char m_bfme0C[0x20];
	BattlePlanStatus m_bfmeStatus;
	char m_bfme30[0x10];
	BattlePlanBonuses *m_bfmeBonuses;
	char m_bfme44[0x700];
	int m_bfmeHandle;
};

void BattlePlanUpdate::onDelete(void)
{
	if (m_bfmeHandle != 0) {
		GameLogicFrameSlice *logic = TheGameLogic;
		BfmeReleasedItem *item = logic->bfmeFind(m_bfmeHandle);
		if (item != 0)
			logic->bfmeDrop(item);
	}

	Player *target = m_bfmeKey->bfmeResolve();
	if (target != 0) {
		BattlePlanStatus status = m_bfmeStatus;
		if (status != BATTLE_PLAN_NONE)
			target->changeBattlePlan(status, -1, m_bfmeBonuses);
	}
}
