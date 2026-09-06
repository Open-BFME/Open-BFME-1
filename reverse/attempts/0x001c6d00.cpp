// ?onDestroy@Object@@QAEXXZ
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// BFME Object::onDestroy, retail 0x001C6D00, 194 bytes.

typedef bool Bool;

class Object;

class Player
{
public:
	void bfmeObjectLeavingInfluence(Object *object);
};

class AsciiString
{
private:
	void *m_buffer;
};

class Team
{
public:
	Player *bfmeGetControllingPlayer() const;
};

class TeamFactory
{
public:
	Team *findTeam(const AsciiString &name);
};

extern TeamFactory *TheTeamFactory;

class Drawable
{
public:
	void forward4125F0(int slot, Bool immediately);
};

class ContainModule
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void removeFromContain(Object *object, Bool exposeStealthUnits) = 0;
};

class BehaviorModule
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void onDelete() = 0;
};

class Object
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual Drawable *getDrawable() = 0;

	void onDestroy();
	BehaviorModule **getBehaviorModules() { return m_behaviors; }

private:
	unsigned char m_pad004[0x90];
	unsigned int m_status;
	unsigned char m_pad098[0x158];
	BehaviorModule **m_behaviors;
	unsigned char m_pad1f4[0x08];
	ContainModule *m_contain;
	unsigned char m_pad200[0x14];
	Object *m_containedBy;
	unsigned char m_pad218[0x24];
	Team *m_team;
	AsciiString m_originalTeamName;
	unsigned char m_pad244[0x158];
	Bool m_powerInfluenceActive;
};

void Object::onDestroy()
{
	Player *player;
	BehaviorModule **module;

	if (m_containedBy && m_containedBy->m_contain)
		m_containedBy->m_contain->removeFromContain(this, false);

	if (m_powerInfluenceActive)
	{
		player = m_team ? m_team->bfmeGetControllingPlayer() : 0;
		if ((m_status & 0x20000000) != 0)
		{
			Team *originalTeam = TheTeamFactory->findTeam(m_originalTeamName);
			if (originalTeam)
				player = originalTeam->bfmeGetControllingPlayer();
		}
		if (player)
		{
			player->bfmeObjectLeavingInfluence(this);
			m_powerInfluenceActive = false;
		}
	}

	Drawable *drawable = getDrawable();
	if (drawable)
	{
		for (int slot = 1; slot < 6; ++slot)
			drawable->forward4125F0(slot, true);
	}

	for (module = *reinterpret_cast<BehaviorModule ***>(reinterpret_cast<char *>(this) + 0x1f0);
	     *module;
	     ++module)
		(*module)->onDelete();
}
