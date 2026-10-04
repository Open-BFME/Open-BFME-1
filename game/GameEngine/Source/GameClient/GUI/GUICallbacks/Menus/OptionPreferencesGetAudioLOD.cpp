#include "ascii_string.h"

struct PreferenceNode
{
	unsigned char m_unreconstructed_00[0x14];
	AsciiString m_value;
};

// 0x0000AEAC is a 5-byte ILT thunk (?j_0000aeac@@YAXXZ) to the preferences
// map find at 0x00480600; the ?find@PreferenceMap pin has no definition, so
// call through the thunk's own name.
extern void j_0000aeac();

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
		union FindRoute
		{
			void (*raw)();
			PreferenceNode *(PreferenceMap::*member)(const AsciiString &) const;
		} route;
		route.raw = j_0000aeac;
		it = ( ( &m_prefs )->*route.member )( key );
	}

	if (it == m_prefs.end())
		return -1;

	return TheGameLODManager->getAudioLODIndex(it->m_value);
}

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
