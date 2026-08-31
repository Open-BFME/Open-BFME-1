// cl: /DNDEBUG /MD /EHsc
//
// Focused retail-layout implementation of UpgradeTemplate's constructor.
// Member names and offsets are corroborated by the matched copy assignment,
// destructor, and the retail INI field table.  BFME constructs both sound
// members with the shared default object at 0x01336E50.

class AsciiString
{
public:
	AsciiString() : m_text(0) {}
	~AsciiString();

private:
	char *m_text;
};

extern int g_bfmeDefaultBG;

class AudioEventRTS
{
public:
	AudioEventRTS(void *event = &g_bfmeDefaultBG, int value = 0);
	virtual ~AudioEventRTS();

private:
	unsigned char m_data[0x6c];
};

class UpgradeTemplate
{
public:
	UpgradeTemplate();

protected:
	virtual ~UpgradeTemplate();

private:
	unsigned int m_type;
	AsciiString m_member08;
	unsigned int m_nameKey;
	AsciiString m_displayNameLabel;
	AsciiString m_member14;
	float m_buildTime;
	int m_cost;
	int m_academyClassificationType;
	AsciiString m_member24;
	AudioEventRTS m_researchSound;
	AudioEventRTS m_unitSpecificSound;
	UpgradeTemplate *m_next;
	UpgradeTemplate *m_prev;
	AsciiString m_buttonImageName;
	unsigned int m_word114;
	AsciiString m_member118;
	bool m_flag11c;
	bool m_flag11d;
};

// ??0UpgradeTemplate@@QAE@XZ
UpgradeTemplate::UpgradeTemplate()
{
	m_cost = 0;
	m_type = 0;
	m_nameKey = 0;
	m_buildTime = 0.0f;
	m_next = 0;
	m_prev = 0;
	m_word114 = 0;
	m_flag11c = false;
	m_flag11d = false;
	m_academyClassificationType = -1;
}
