// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// ABI-local reconstruction of OptionPreferences::getCampaignDifficulty.
// The public OptionsMenu declaration uses the game's full headers; this TU
// keeps the retail preference-node and StringBase layout explicit so MSVC 7.1
// emits the out-of-line AsciiString constructor/destructor calls used here.

typedef int Int;

extern "C" __declspec(dllimport) int __cdecl bfmeAtoi1027(char *text);

class AsciiStringData
{
public:
	unsigned char m_unreconstructed_00[8];
	char m_chars[1];
};

class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();

	const char *str(void) const { return m_data ? m_data->m_chars : ""; }

private:
	AsciiStringData *m_data;
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
	PreferenceNode *end(void) const { return m_end; }

private:
	PreferenceNode *m_end;
};

class ScriptEngine
{
public:
	unsigned char m_unreconstructed_00[0x17620];
	Int m_globalDifficulty;

	Int getGlobalDifficulty(void) const { return m_globalDifficulty; }
};

extern ScriptEngine *TheScriptEngine;

class OptionPreferences
{
public:
	Int getCampaignDifficulty(void);

private:
	unsigned char m_unreconstructed_00[4];
	PreferenceMap m_prefs;
};

// ?getCampaignDifficulty@OptionPreferences@@QAEHXZ
Int OptionPreferences::getCampaignDifficulty(void)
{
	PreferenceNode *it;
	{
		AsciiString key("CampaignDifficulty");
		it = m_prefs.find(key);
	}

	if (it == m_prefs.end())
		return TheScriptEngine->getGlobalDifficulty();

	Int factor = bfmeAtoi1027((char *)it->m_value.str());
	if (factor < 0)
		return 0;
	if (factor > 2)
		return 2;
	return factor;
}
