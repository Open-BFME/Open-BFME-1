// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h

typedef unsigned int UnsignedInt;

class UpgradeTemplate
{
};

class Upgrade
{
public:
	const UpgradeTemplate *getTemplate() const { return m_upgradeTemplate; }
	Upgrade *friend_getNext() { return m_next; }

private:
	void *m_vtable;
	const UpgradeTemplate *m_upgradeTemplate;
	int m_status;
	Upgrade *m_next;
	Upgrade *m_prev;
};

class Player
{
public:
	Upgrade *findUpgrade(const UpgradeTemplate *upgradeTemplate);

private:
	unsigned char m_unreconstructed[0x54];
	Upgrade *m_upgradeList;
};

// ?findUpgrade@Player@@QAEPAVUpgrade@@PBVUpgradeTemplate@@@Z
Upgrade *Player::findUpgrade(const UpgradeTemplate *upgradeTemplate)
{
	Upgrade *upgrade;

	for (upgrade = m_upgradeList; upgrade; upgrade = upgrade->friend_getNext())
		if (upgrade->getTemplate() == upgradeTemplate)
			return upgrade;

	return 0;
}
