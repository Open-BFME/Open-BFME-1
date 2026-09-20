// ?bfmeGetYA@BfmeHostYA@@QAEMXZ
// The BfmeHostYA vtable and the LocomotorOverridable fields at +0x04 and
// +0x23c prove the identity. Retail calls getControllingPlayer, follows the
// override chain through getFinalOverride, then calls ThingTemplate's
// calcTimeToBuild with mode -1.

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

	int buildTime;
	if (m_bfme04YA == 0)
	{
		buildTime = ((ThingTemplate *)0)->calcTimeToBuild(pl, -1);
	}
	else
	{
		ThingTemplate *finalOverride = (ThingTemplate *)m_bfme04YA;
		if (finalOverride->m_bfme04YA != 0)
			finalOverride = (ThingTemplate *)finalOverride->m_bfme04YA->friend_getFinalOverride();
		buildTime = finalOverride->calcTimeToBuild(pl, -1);
	}
	return g_bfmeDefaultBU / (float)buildTime;
}
