class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();

private:
	void *m_data;
};

struct PreferenceNode
{
	unsigned char m_unreconstructed_00[0x14];
	AsciiString m_value;
};

class PreferenceMap
{
public:
	PreferenceNode *find(const AsciiString &) const;
	PreferenceNode *end() const { return m_end; }

private:
	PreferenceNode *m_end;
};

class GameLODManager
{
public:
	int getAudioLODIndex(const AsciiString &name);
};

extern GameLODManager *TheGameLODManager;

class OptionPreferences
{
public:
	int getAudioLOD();

private:
	unsigned char m_unreconstructed_00[4];
	PreferenceMap m_prefs;
};

int OptionPreferences::getAudioLOD()
{
	PreferenceNode *it;
	{
		AsciiString key("AudioLOD");
		it = m_prefs.find(key);
	}

	if (it == m_prefs.end())
		return -1;

	return TheGameLODManager->getAudioLODIndex(it->m_value);
}

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /O2 /Ob2
