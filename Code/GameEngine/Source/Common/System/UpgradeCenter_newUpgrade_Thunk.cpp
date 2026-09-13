// cl: /DNDEBUG /MD /EHsc
// readable body of ?newUpgrade@UpgradeCenter@@QAEPAVUpgradeTemplate@@ABVAsciiString@@@Z: Code/GameEngine/Source/Common/System/Upgrade.cpp
// Open-BFME5: lift the retail upgrade allocation/link path to standalone C++.

typedef int NameKeyType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();
	AsciiString &operator=(const AsciiString &other);
	const char *str() const { return m_data ? m_data + 8 : ""; }
private:
	const char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
public:
	UpgradeTemplate();
	virtual ~UpgradeTemplate();
	UpgradeTemplate &operator=(const UpgradeTemplate &other);
private:
	friend class UpgradeCenter;
	int m_type;
	AsciiString m_name;
	NameKeyType m_nameKey;
	char m_pad10[0x20 - 0x10];
	int m_upgradeMaskIndex;
	char m_pad24[0x108 - 0x24];
	UpgradeTemplate *m_next;
	UpgradeTemplate *m_prev;
	char m_tail[0x120 - 0x110];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeCenter
{
public:
	UpgradeTemplate *newUpgrade(const AsciiString &name);
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
private:
	virtual void reserved();
	int m_basePad;
	UpgradeTemplate *m_upgradeList;
	int m_nextTemplateMaskBit;
};

UpgradeTemplate *UpgradeCenter::newUpgrade(const AsciiString &name)
{
	UpgradeTemplate *newUpgrade = new UpgradeTemplate;
	const UpgradeTemplate *defaultUpgrade = findUpgrade("DefaultUpgrade");
	if (defaultUpgrade)
		*newUpgrade = *defaultUpgrade;

	newUpgrade->m_name = name;
	newUpgrade->m_nameKey = TheNameKeyGenerator->nameToKey(name.str());
	newUpgrade->m_upgradeMaskIndex = m_nextTemplateMaskBit++;
	newUpgrade->m_prev = 0;
	newUpgrade->m_next = m_upgradeList;
	if (m_upgradeList)
		m_upgradeList->m_prev = newUpgrade;
	m_upgradeList = newUpgrade;
	return newUpgrade;
}
