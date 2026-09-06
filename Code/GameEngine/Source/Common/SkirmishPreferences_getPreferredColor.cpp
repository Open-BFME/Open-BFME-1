// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// SkirmishPreferences::getPreferredColor at retail RVA 0x0009E3D0.

extern "C" __declspec(dllimport) int __cdecl atoi(const char *);

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
	char m_pad[0x34];
	int m_colorCount;
	char m_pad38[4];
	int m_numColors;
};

extern MultiplayerSettings *TheMultiplayerSettings;

class SkirmishPreferences : public UserPreferences
{
public:
	int getPreferredColor();
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
