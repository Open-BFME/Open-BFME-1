// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift UpgradeTemplate's retail copy assignment from the MASM dump.
//
// The named members come from retail's own INI field table at 0x00C88B60, which
// gives each UpgradeTemplate key a binary-proven offset; upstream's
// m_upgradeFieldParseTable says which member that key writes. The offsets are
// retail's and only the vocabulary is Zero Hour's. Each one's type here already
// agreed with the parser upstream uses for its key -- parseReal/parseInt on the
// 4-byte scalars, parseAsciiString on the AsciiStrings, parseAudioEventRTS on
// the two AudioEventRTS -- which is the independent check on the join. A member
// retail's table gives no key keeps its offset name.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	virtual ~AudioEventRTS();
	AudioEventRTS &operator=(const AudioEventRTS &other);

private:
	unsigned char m_data[0x6c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
public:
	UpgradeTemplate &operator=(const UpgradeTemplate &other);

protected:
	virtual ~UpgradeTemplate();

private:
	unsigned int m_type;
	AsciiString m_member08;
	unsigned int m_word0c;
	AsciiString m_displayNameLabel;
	AsciiString m_member14;
	unsigned int m_buildTime;
	unsigned int m_cost;
	unsigned int m_word20;
	AsciiString m_member24;
	AudioEventRTS m_researchSound;
	AudioEventRTS m_unitSpecificSound;
	unsigned int m_word108;
	unsigned int m_word10c;
	AsciiString m_buttonImageName;
	unsigned int m_word114;
	AsciiString m_member118;
	unsigned char m_flag11c;
	unsigned char m_flag11d;
};

// ??4UpgradeTemplate@@QAEAAV0@ABV0@@Z
UpgradeTemplate &UpgradeTemplate::operator=(const UpgradeTemplate &other)
{
	m_type = other.m_type;
	m_member08 = other.m_member08;
	m_word0c = other.m_word0c;
	m_displayNameLabel = other.m_displayNameLabel;
	m_member14 = other.m_member14;
	m_buildTime = other.m_buildTime;
	m_cost = other.m_cost;
	m_word20 = other.m_word20;
	m_member24 = other.m_member24;
	m_researchSound = other.m_researchSound;
	m_unitSpecificSound = other.m_unitSpecificSound;
	m_word108 = other.m_word108;
	m_word10c = other.m_word10c;
	m_buttonImageName = other.m_buttonImageName;
	m_word114 = other.m_word114;
	m_member118 = other.m_member118;
	m_flag11c = other.m_flag11c;
	m_flag11d = other.m_flag11d;
	return *this;
}
