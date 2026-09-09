// ?bfmeGetYA@BfmeHostYA@@QAEMXZ
// partial score=0.99 date=2026-09-09
// pin needed: ?bfmeApplyYA@LocomotorOverridable@@QAEHPAVPlayer@@H@Z,0x0004B01F
class Player;

class LocomotorOverridable
{
public:
	LocomotorOverridable *friend_getFinalOverride();
	int bfmeApplyYA(Player *pl, int mode);

	unsigned char m_bfmeHeadYA[4];
	LocomotorOverridable *m_bfme04YA;
};

class Team
{
public:
	Player *getControllingPlayer() const;
};

extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;

static __forceinline LocomotorOverridable *bfmeFinalYA(LocomotorOverridable *p)
{
	LocomotorOverridable *overrideObject;
	if (p == 0)
	{
		overrideObject = 0;
	}
	else
	{
		overrideObject = p->m_bfme04YA;
		if (overrideObject != 0)
			overrideObject = overrideObject->friend_getFinalOverride();
	}
	return overrideObject;
}

class BfmeHostYA
{
public:
	float bfmeGetYA();

	unsigned char m_bfmeHeadYA[4];
	LocomotorOverridable *m_bfme04YA;
	unsigned char m_bfmeMidYA[0x234];
	Team *m_bfme23CYA;
};

float BfmeHostYA::bfmeGetYA()
{
	Team *team = m_bfme23CYA;
	Player *pl = 0;

	if (team != 0)
		pl = team->getControllingPlayer();

	if (pl == 0)
		return BfmeZeroRange;

	return g_bfmeDefaultBU / (float)bfmeFinalYA(m_bfme04YA)->bfmeApplyYA(pl, -1);
}
