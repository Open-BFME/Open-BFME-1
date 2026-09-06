// ?getPreferredMap@SkirmishPreferences@@QAE?AVAsciiString@@XZ
// partial score=0.75 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// SkirmishPreferences::getPreferredMap at retail RVA 0x0009E470, 377B.
// Same shape as the ZH source (reference/.../LanLobbyMenu.cpp:160), but the
// retail callee list has no isValidMap call, so BFME dropped that guard:
// only the "not found" and "empty after decode" branches fall back to
// getDefaultMap(TRUE). Model follows the minimal-shim style proven for
// Code/GameEngine/Source/Common/Gen_0009E3D0_SkirmishPreferences_getPreferredColor.cpp.

class AsciiStringData
{
public:
	char m_pad[8];
	char m_text[1];
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const char *text);
	AsciiString(const AsciiString &other);
	~AsciiString();

	AsciiString &operator=(const AsciiString &other);

	bool isEmpty() const
	{
		return m_data == 0;
	}

	void trim();

	const char *str() const
	{
		return m_data ? m_data->m_text : "";
	}

private:
	AsciiStringData *m_data;
};

AsciiString QuotedPrintableToAsciiString(AsciiString original);
AsciiString getDefaultMap(bool useIfNotFound);

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

class SkirmishPreferences : public UserPreferences
{
public:
	AsciiString getPreferredMap(void);
};

// ?getPreferredMap@SkirmishPreferences@@QAE?AVAsciiString@@XZ
AsciiString SkirmishPreferences::getPreferredMap(void)
{
	AsciiString ret;
	PreferenceNode *it = find("Map");
	if (it == end())
	{
		ret = getDefaultMap(true);
		return ret;
	}

	ret = QuotedPrintableToAsciiString(it->m_value);
	ret.trim();
	if (ret.isEmpty())
	{
		ret = getDefaultMap(true);
		return ret;
	}

	return ret;
}
