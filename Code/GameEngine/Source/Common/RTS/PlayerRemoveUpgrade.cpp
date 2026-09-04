// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Clean C++ reconstruction of Player::removeUpgrade().

typedef unsigned int UnsignedInt;

class UpgradeTemplate
{
public:
	UnsignedInt getUpgradeMask() const { return m_upgradeMask; }

private:
	unsigned char m_unreconstructed[0x20];
	UnsignedInt m_upgradeMask;

	friend class Player;
};

class Upgrade
{
private:
	void *m_vtable;
	const UpgradeTemplate *m_upgradeTemplate;
	int m_status;
	Upgrade *m_next;
	Upgrade *m_prev;

	friend class Player;
};

class UpgradeMaskType
{
public:
	void clear(const UpgradeTemplate *upgradeTemplate)
	{
		UnsignedInt bit = upgradeTemplate->getUpgradeMask();
		UnsignedInt *word = &m_bits[bit >> 5];
		UnsignedInt mask = 1U << (bit & 31);
		UnsignedInt value = *word & ~mask;
		*word = value;
	}

private:
	UnsignedInt m_bits[6];
};

class Player
{
public:
	void removeUpgrade(const UpgradeTemplate *upgradeTemplate);

private:
	Upgrade *findUpgrade(const UpgradeTemplate *upgradeTemplate)
	{
		for (Upgrade *upgrade = m_upgradeList; upgrade != 0; upgrade = upgrade->m_next)
		{
			if (upgrade->m_upgradeTemplate == upgradeTemplate)
				return upgrade;
		}
		return 0;
	}

	unsigned char m_unreconstructed[0x54];
	Upgrade *m_upgradeList;
	unsigned char m_betweenListAndMasks[0x1c];
	UpgradeMaskType m_upgradesInProgress;
	UpgradeMaskType m_upgradesCompleted;
};

void Player::removeUpgrade(const UpgradeTemplate *upgradeTemplate)
{
	Upgrade *upgrade = findUpgrade(upgradeTemplate);

	if (upgrade != 0)
	{
		if (upgrade->m_next != 0)
			upgrade->m_next->m_prev = upgrade->m_prev;
		if (upgrade->m_prev != 0)
			upgrade->m_prev->m_next = upgrade->m_next;
		else
			m_upgradeList = upgrade->m_next;

		m_upgradesInProgress.clear(upgradeTemplate);
		m_upgradesCompleted.clear(upgradeTemplate);
	}
}
