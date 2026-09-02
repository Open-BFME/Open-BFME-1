// ?d_00286140@@YAXXZ
// partial score=0.92 date=2026-09-03
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

class Gen_00286140
{
public:
	void bfmeDispatch(void);

private:
	char m_bfmeFields[8];
	BfmeResolutionKey *m_bfmeKey;
	char m_bfme0C[0x20];
	BattlePlanStatus m_bfmeStatus;
	char m_bfme30[0x10];
	BattlePlanBonuses *m_bfmeBonuses;
	char m_bfme44[0x700];
	int m_bfmeHandle;
};

// ?bfmeDispatch@Gen_00286140@@QAEXXZ
void Gen_00286140::bfmeDispatch(void)
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
		switch (status) {
		case BATTLE_PLAN_NONE:
			break;
		default:
			target->changeBattlePlan(status, -1, m_bfmeBonuses);
			break;
		}
	}
}
