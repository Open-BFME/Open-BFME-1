// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift UpgradeTemplate's retail copy assignment from the MASM dump.

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
	unsigned int m_pad04;
	AsciiString m_member08;
	unsigned int m_word0c;
	AsciiString m_member10;
	AsciiString m_member14;
	unsigned int m_word18;
	unsigned int m_word1c;
	unsigned int m_word20;
	AsciiString m_member24;
	AudioEventRTS m_member28;
	AudioEventRTS m_member98;
	unsigned int m_word108;
	unsigned int m_word10c;
	AsciiString m_member110;
	unsigned int m_word114;
	AsciiString m_member118;
	unsigned char m_flag11c;
	unsigned char m_flag11d;
};

// ??4UpgradeTemplate@@QAEAAV0@ABV0@@Z
UpgradeTemplate &UpgradeTemplate::operator=(const UpgradeTemplate &other)
{
	m_pad04 = other.m_pad04;
	m_member08 = other.m_member08;
	m_word0c = other.m_word0c;
	m_member10 = other.m_member10;
	m_member14 = other.m_member14;
	m_word18 = other.m_word18;
	m_word1c = other.m_word1c;
	m_word20 = other.m_word20;
	m_member24 = other.m_member24;
	m_member28 = other.m_member28;
	m_member98 = other.m_member98;
	m_word108 = other.m_word108;
	m_word10c = other.m_word10c;
	m_member110 = other.m_member110;
	m_word114 = other.m_word114;
	m_member118 = other.m_member118;
	m_flag11c = other.m_flag11c;
	m_flag11d = other.m_flag11d;
	return *this;
}
