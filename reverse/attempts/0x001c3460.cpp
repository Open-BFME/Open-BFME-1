// ?bfmeGetYA@BfmeHostYA@@QAEMXZ
// partial score=0.99 date=2026-09-09
// pin needed: ?bfmeApplyYA@LocomotorOverridable@@QAEHPAVPlayer@@H@Z,0x0004B01F
class Player;

class LocomotorOverridable
{
public:
	LocomotorOverridable *friend_getFinalOverride();

	unsigned char m_bfmeHeadYA[4];
	LocomotorOverridable *m_bfme04YA;
};

class ThingTemplate : public LocomotorOverridable
{
public:
	int calcTimeToBuild(const Player *pl, int mode) const;
};

class Team
{
public:
	Player *getControllingPlayer() const;
};

extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;

static __forceinline ThingTemplate *bfmeFinalYA(LocomotorOverridable *p)
{
	ThingTemplate *overrideObject;
	if (p == 0)
	{
		overrideObject = 0;
	}
	else
	{
		LocomotorOverridable *next = p->m_bfme04YA;
		if (next == 0)
			overrideObject = (ThingTemplate *)p;
		else
			overrideObject = (ThingTemplate *)next->friend_getFinalOverride();
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

	ThingTemplate *finalOverride = bfmeFinalYA(m_bfme04YA);
	return g_bfmeDefaultBU / (float)finalOverride->calcTimeToBuild(pl, -1);
}
