// ?d_0049b9b0@@YAXXZ
// partial score=0.95 date=2026-09-16
// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
private:
	unsigned char m_padding[4];
};

class UpgradeTemplate
{
public:
	unsigned int getUpgradeMask() const { return m_upgradeMask; }

private:
	unsigned char m_padding[0x20];
	unsigned int m_upgradeMask;
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

struct UpgradeMaskType
{
	unsigned int m_bits[6];

	UpgradeMaskType &operator=(const UpgradeMaskType &other)
	{
		m_bits[0] = other.m_bits[0];
		m_bits[1] = other.m_bits[1];
		m_bits[2] = other.m_bits[2];
		m_bits[3] = other.m_bits[3];
		m_bits[4] = other.m_bits[4];
		m_bits[5] = other.m_bits[5];
		return *this;
	}

	void set(unsigned int bit)
	{
		m_bits[bit >> 5] |= 1U << (bit & 31);
	}
};

class CommandButton
{
public:
	void getBuildUpgradeMask(UpgradeMaskType &mask) const;

private:
	unsigned char m_padding[0x28];
	AsciiString *m_buildUpgradesFirst;
	AsciiString *m_buildUpgradesLast;
	AsciiString *m_buildUpgradesEnd;
};

// ?getBuildUpgradeMask@CommandButton@@QBEXAAUUpgradeMaskType@@@Z
void CommandButton::getBuildUpgradeMask(UpgradeMaskType &mask) const
{
	UpgradeMaskType buildMask = {};
	const CommandButton *button = this;
	AsciiString *upgrade = button->m_buildUpgradesFirst;

	while (upgrade != button->m_buildUpgradesLast)
	{
		const UpgradeTemplate *upgradeTemplate = TheUpgradeCenter->findUpgrade(*upgrade);
		if (upgradeTemplate != 0)
			buildMask.set(upgradeTemplate->getUpgradeMask());
		++upgrade;
	}

	mask = buildMask;
}
