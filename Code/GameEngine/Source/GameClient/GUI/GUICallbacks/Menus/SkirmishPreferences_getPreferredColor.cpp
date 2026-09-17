// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// SkirmishPreferences::getPreferredColor at retail RVA 0x0009E3D0.

extern "C" __declspec(dllimport) int __cdecl atoi(const char *);

class PlayerTemplate
{
	public:
	char m_unreconstructed_00[0xBD];
	unsigned char m_isPlayableSide;
	char m_unreconstructed_BE[0x66];
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(int index) const;

	int getPlayerTemplateCount() const
	{
		return (int)(m_end - m_begin);
	}

private:
	char m_pad[8];
	PlayerTemplate *m_begin;
	PlayerTemplate *m_end;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

class AsciiStringData
{
public:
	char m_pad[8];
	char m_text[1];
};

class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();

	const char *str() const
	{
		return m_data ? m_data->m_text : "";
	}

private:
	AsciiStringData *m_data;
};

struct PreferenceNode
{
	char m_pad[0x14];
	AsciiString m_value;
};

class PreferenceMap
{
public:
	PreferenceNode *find(const AsciiString &) const;
	PreferenceNode *end() const
	{
		return m_end;
	}

private:
	PreferenceNode *m_end;
};

class UserPreferences : public PreferenceMap
{
public:
	virtual ~UserPreferences();
};

class MultiplayerSettings
{
public:
	int getNumColors()
	{
		if (m_numColors == 0)
			m_numColors = m_colorCount;
		return m_numColors;
	}

private:
	char m_pad00[0x10];
	int m_startCountdownTimerSeconds;
	int m_maxBeaconsPerPlayer;
	unsigned char m_isShroudInMultiplayer;
	unsigned char m_showRandomPlayerTemplate;
	unsigned char m_showRandomStartPos;
	unsigned char m_showRandomColor;
	char m_pad1c[0x34 - 0x1c];
	int m_colorCount;
	char m_pad38[4];
	int m_numColors;
};

extern MultiplayerSettings *TheMultiplayerSettings;

class SkirmishPreferences : public UserPreferences
{
public:
	int getPreferredColor();
	int getPreferredFaction();
};

int SkirmishPreferences::getPreferredColor()
{
	PreferenceNode *it;
	{
		AsciiString key("Color");
		it = find(key);
	}

	if (it == end())
		return 0;

	int value = atoi(it->m_value.str());
	if (value < -1 || value >= TheMultiplayerSettings->getNumColors())
		value = -1;
	return value;
}

int SkirmishPreferences::getPreferredFaction()
{
	PreferenceNode *it;
	{
		AsciiString key("PlayerTemplate");
		it = find(key);
	}

	if (it == end())
		return -1;

	int value = atoi(it->m_value.str());
	if (value < -2 || value >= ThePlayerTemplateStore->getPlayerTemplateCount())
		value = -1;

	if (value >= 0)
	{
		const PlayerTemplate *fac = ThePlayerTemplateStore->getNthPlayerTemplate(value);
		if (fac == 0 || !fac->m_isPlayableSide)
			value = -1;
	}

	return value;
}
