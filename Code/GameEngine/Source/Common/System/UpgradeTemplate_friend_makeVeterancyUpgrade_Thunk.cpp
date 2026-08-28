// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Verbatim Zero Hour Upgrade.cpp. The reference comment explains the gap in the
// stores: m_upgradeMask at +0x14 is deliberately left alone, so retail writes
// +0x18 and +0x1c and skips over it.
//
// getVetUpgradeName returns AsciiString by value, so the hidden result pointer
// is the first cdecl argument -- the lea pushed after the level, not a second
// parameter. The temporary is released immediately after the assignment, which
// is what the state variable stepping back to -1 marks.
//
// nameToKey takes const char*, and the conversion operator supplies retail's
// inline test: the data pointer plus eight, or the empty literal when null.
// NameKeyType is an enum, not an integer typedef. nameToKey mangles its return
// as ?AW4NameKeyType@@ and a typedef to unsigned int gives I instead, which
// leaves the call unresolved with a zero displacement.
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum VeterancyLevel
{
	LEVEL_REGULAR = 0
};

enum UpgradeType
{
	UPGRADE_TYPE_PLAYER = 0,
	UPGRADE_TYPE_OBJECT = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(void);
	AsciiString(const AsciiString &other);
	~AsciiString(void);

	AsciiString &operator=(const AsciiString &other);

	operator const char *(void) const
	{
		return m_data ? m_data + 8 : "";
	}

	void clear(void)
	{
		releaseBuffer();
	}

private:
	void releaseBuffer(void);

	char *m_data;
};

AsciiString getVetUpgradeName(VeterancyLevel level);

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
	void friend_makeVeterancyUpgrade(VeterancyLevel v);

private:
	void *m_next;
	UpgradeType m_type;
	AsciiString m_name;
	NameKeyType m_nameKey;
	AsciiString m_displayNameLabel;
	int m_upgradeMask;
	float m_buildTime;
	float m_cost;
};

// ?friend_makeVeterancyUpgrade@UpgradeTemplate@@QAEXW4VeterancyLevel@@@Z
void UpgradeTemplate::friend_makeVeterancyUpgrade(VeterancyLevel v)
{
	m_type = UPGRADE_TYPE_OBJECT;
	m_name = getVetUpgradeName(v);
	m_nameKey = TheNameKeyGenerator->nameToKey(m_name);
	m_displayNameLabel.clear();
	m_buildTime = 0.0f;
	m_cost = 0.0f;
}
