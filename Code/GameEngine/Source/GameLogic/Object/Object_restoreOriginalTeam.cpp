// cl: /DNDEBUG /MD /EHsc
// readable body of ?restoreOriginalTeam@Object@@QAEXXZ: Code/GameEngine/Source/GameLogic/Object/Object.cpp

// Open-BFME5: Object::restoreOriginalTeam, retail 0x001C4670, 118 bytes.
// The first half is the surviving Zero Hour routine.  BFME adds a safeguard
// after setTeam: if the restored owner is dead, kill the object with
// unresistable damage rather than leave a useful unit under that player.

typedef bool Bool;

enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};

enum DeathType
{
	DEATH_NORMAL = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
private:
	struct SharedBuffer
	{
		unsigned int m_refCount;
		unsigned short m_length;
	};

	SharedBuffer *m_buffer;

public:
	Bool isEmpty() const
	{
		return m_buffer == 0 || m_buffer->m_length == 0;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Bool isPlayerDead() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Player *getControllingPlayer() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamFactory
{
public:
	Team *findTeam(const AsciiString &name);
};

extern TeamFactory *TheTeamFactory;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	virtual void bfmeSlot00() = 0;
	virtual void bfmeSlot01() = 0;
	virtual void bfmeSlot02() = 0;
	virtual void bfmeSlot03() = 0;
	virtual void bfmeSlot04() = 0;
	virtual void bfmeSlot05() = 0;
	virtual void bfmeSlot06() = 0;
	virtual void bfmeSlot07() = 0;
	virtual void bfmeSlot08() = 0;
	virtual void bfmeSlot09() = 0;
	virtual void bfmeSlot10() = 0;
	virtual void bfmeSlot11() = 0;
	virtual void bfmeSlot12() = 0;
	virtual void bfmeSlot13() = 0;
	virtual void bfmeSlot14() = 0;
	virtual void bfmeSlot15() = 0;
	virtual void bfmeSlot16() = 0;
	virtual void bfmeSlot17() = 0;
	virtual void bfmeSlot18() = 0;
	virtual void bfmeSlot19() = 0;
	virtual void setTeam(Team *team) = 0;

	void restoreOriginalTeam();
	Player *getControllingPlayer() const;
	void kill(DamageType damageType, DeathType deathType);

private:
	unsigned char m_unmodelled004[0x23c - 4];
	Team *m_team;
	AsciiString m_originalTeamName;
};

// ?restoreOriginalTeam@Object@@QAEXXZ
void Object::restoreOriginalTeam()
{
	if (m_team == 0 || m_originalTeamName.isEmpty())
		return;

	Team *originalTeam = TheTeamFactory->findTeam(m_originalTeamName);
	if (originalTeam == 0)
		return;

	if (m_team == originalTeam)
		return;

	setTeam(originalTeam);

	if (m_team != 0 && m_team->getControllingPlayer() != 0 &&
		getControllingPlayer()->isPlayerDead())
	{
		kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
	}
}
