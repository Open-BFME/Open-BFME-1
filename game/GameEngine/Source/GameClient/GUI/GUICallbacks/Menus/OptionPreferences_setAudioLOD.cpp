// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// OptionPreferences AudioLOD setter at retail RVA 0x00092810.

#include <map>
#include <string.h>

#include "string_base.h"
#include "ascii_string.h"

typedef std::map<AsciiString, AsciiString> PreferenceMap;

class UserPreferences : public PreferenceMap
{
public:
	virtual ~UserPreferences();
};

class GameLODManager
{
public:
	const char *getRva0007C4D0(int value);
};

extern GameLODManager *TheGameLODManager;

class OptionPreferences : public UserPreferences
{
public:
	void setAudioLOD(int value);
};

void OptionPreferences::setAudioLOD(int value)
{
	AsciiString key("AudioLOD");
	const char *text = TheGameLODManager->getRva0007C4D0(value);
	AsciiString &slot = (*this)[key];
	((StringBase<char> *)&slot)->set(text, text ? (int)strlen(text) : 0);
}
