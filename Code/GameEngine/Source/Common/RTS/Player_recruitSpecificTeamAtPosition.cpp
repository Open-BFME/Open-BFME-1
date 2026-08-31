// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

typedef bool Bool;
typedef float Real;

struct Coord3D;
class TeamPrototype;

class AIPlayer
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
	virtual void recruitSpecificAITeam(TeamPrototype *, Real, const Coord3D *);
};

class Player
{
	char m_unreconstructed[0x220];
	AIPlayer *m_ai;

public:
	void recruitSpecificTeam(TeamPrototype *, Real, const Coord3D *);
};

// ?recruitSpecificTeam@Player@@QAEXPAVTeamPrototype@@MPBUCoord3D@@@Z
void Player::recruitSpecificTeam(
	TeamPrototype *teamPrototype, Real recruitRadius, const Coord3D *position)
{
	if (m_ai) {
		m_ai->recruitSpecificAITeam(teamPrototype, recruitRadius, position);
	}
}
