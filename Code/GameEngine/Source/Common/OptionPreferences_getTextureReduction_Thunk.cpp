// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the OptionPreferences::getTextureReduction naked dump to clean C++.
//
// Preferences getter whose default is computed rather than read: a missing key
// derives a percentage from the texture-reduction level at GlobalData+0x68, so
// both paths join before the shared 0..100 clamp instead of returning early.
// The key lives in its own scope so it dies after the lookup and before the
// end() comparison, which is the order retail uses.
//
// Retail pins the layout: the map is at this+0x04 and its first word is the end
// sentinel, the mapped AsciiString is at node+0x14, and str() inlines to
// "m_data ? m_data+8 : empty".
//
// /EHs-c- because the build default only clears the /EHc half, and the key's
// destructor would otherwise pull in an SEH prologue retail does not have.

extern "C" __declspec(dllimport) int __cdecl atoi(const char *);

class AsciiStringData
{
public:
	unsigned char m_unreconstructed_00[8];
	char m_chars[1];									///< retail this+0x08
};

class AsciiString
{
public:
	AsciiString(const char *);
	~AsciiString();

	const char *str(void) const { return m_data ? m_data->m_chars : ""; }

private:
	AsciiStringData *m_data;
};

struct PreferenceNode
{
	unsigned char m_unreconstructed_00[0x14];
	AsciiString m_value;								///< retail this+0x14
};

class PreferenceMap
{
public:
	PreferenceNode *find(const AsciiString &) const;
	PreferenceNode *end(void) const { return m_end; }

private:
	PreferenceNode *m_end;								///< retail this+0x00
};

class GlobalData
{
public:
	unsigned char m_unreconstructed_00[0x68];
	int m_textureReduction;								///< retail this+0x68
};

extern GlobalData *TheWritableGlobalData;				///< retail [0x012ED5C8]

class OptionPreferences
{
public:
	int getTextureReduction(void);

private:
	unsigned char m_unreconstructed_00[4];
	PreferenceMap m_prefs;								///< retail this+0x04
};

// ?getTextureReduction@OptionPreferences@@QAEHXZ
int OptionPreferences::getTextureReduction(void)
{
	PreferenceNode *it;
	{
		AsciiString key("TextureReduction");
		it = m_prefs.find(key);
	}

	int value;
	if (it == m_prefs.end())
	{
		// Two is the least-reduced setting, so the stored level maps onto a
		// percentage; the 0.5f is the rounding term ahead of the truncation.
		value = (int)((2 - TheWritableGlobalData->m_textureReduction) * 50.0f + 0.5f);
	}
	else
	{
		value = atoi(it->m_value.str());
	}

	if (value < 0)
		return 0;

	if (value > 100)
		return 100;

	return value;
}
