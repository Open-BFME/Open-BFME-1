// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

class Player;

class Team
{
public:
	Player *getControllingPlayer() const;
};

class UpgradeModuleInterface
{
public:
	virtual Bool isAlreadyUpgraded() const = 0;
	virtual void bfmeSlot1() = 0;
	virtual void bfmeSlot2() = 0;
	virtual void bfmeSlot3() = 0;
	virtual void bfmeSlot4() = 0;
	virtual void forceRefreshUpgrade() = 0;
};

class BehaviorModuleInterface
{
public:
	virtual void bfmeSlot0() = 0;
	virtual void bfmeSlot1() = 0;
	virtual void bfmeSlot2() = 0;
	virtual void bfmeSlot3() = 0;
	virtual void bfmeSlot4() = 0;
	virtual void bfmeSlot5() = 0;
	virtual void bfmeSlot6() = 0;
	virtual void bfmeSlot7() = 0;
	virtual void bfmeSlot8() = 0;
	virtual UpgradeModuleInterface *getUpgrade() = 0;
};

class BehaviorModule;

class Object
{
public:
	void bfmeRefreshCompletedUpgrades();

private:
	unsigned char m_unmodelled000[0x1f0];
	BehaviorModule **m_behaviors;
	unsigned char m_unmodelled1f4[0x23c - 0x1f4];
	Team *m_team;
};

void Object::bfmeRefreshCompletedUpgrades()
{
	if (m_team == 0 || m_team->getControllingPlayer() == 0)
		return;

	for (BehaviorModule **module = m_behaviors; *module; ++module)
	{
		BehaviorModuleInterface *behavior =
			reinterpret_cast<BehaviorModuleInterface *>(
				reinterpret_cast<unsigned char *>(*module) + 0xc);
		UpgradeModuleInterface *upgrade = behavior->getUpgrade();
		if (upgrade != 0 && upgrade->isAlreadyUpgraded())
			upgrade->forceRefreshUpgrade();
	}
}
