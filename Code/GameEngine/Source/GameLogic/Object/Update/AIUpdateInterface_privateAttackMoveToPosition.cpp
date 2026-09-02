// cl: /DNDEBUG /MD
//
// Retail 0x00279050: AIUpdateInterface::privateAttackMoveToPosition.
// m_isAiDead, isMobile, weapon-set bit 8, setGoalPositionClipped,
// setState(0x21), max-shot count, move voice for cmd sources 0 and 1.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 1
};

enum StateID
{
	BFME_AI_ATTACK_MOVE_TO = 0x21
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

struct Coord3D
{
	float x, y, z;
};

class WeaponSetFlags
{
public:
	Bool test(Int type) const { return (m_words[0] & (1U << type)) != 0; }

	UnsignedInt m_words[1];
};

class Weapon
{
public:
	unsigned char m_unmodelled_00[0x20];
	Int m_shotsFired;
	unsigned char m_unmodelled_24[0x34 - 0x24];
	Int m_maxShotCount;
};

class Object
{
public:
	Bool isMobile() const;
	const WeaponSetFlags &getWeaponSetFlags() const;
	Weapon *getCurrentWeapon(WeaponSlotType *wslot);
};

class StateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void clear();
	virtual void slot18();
	virtual void slot1C();
	virtual void setState(StateID state);
};

class AIUpdateInterface
{
public:
	void setGoalPositionClipped(const Coord3D *pos, CommandSourceType cmdSource);

protected:
	virtual void privateAttackMoveToPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource);
	void playMoveVoiceResponse(const Coord3D *position);

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
	unsigned char m_unmodelled_4C[0x32B - 0x4C];
	unsigned char m_isAiDead;
};

void AIUpdateInterface::privateAttackMoveToPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource)
{
	if (m_isAiDead)
		return;
	if (!m_object->isMobile())
		return;
	if (m_object->getWeaponSetFlags().test(8))
		return;

	m_stateMachine->clear();
	setGoalPositionClipped(pos, cmdSource);
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_ATTACK_MOVE_TO);

	Weapon *weapon = m_object->getCurrentWeapon(0);
	if (weapon)
	{
		weapon->m_maxShotCount = maxShotsToFire;
		weapon->m_shotsFired = 0;
	}

	if (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_AI)
		playMoveVoiceResponse(pos);
}
