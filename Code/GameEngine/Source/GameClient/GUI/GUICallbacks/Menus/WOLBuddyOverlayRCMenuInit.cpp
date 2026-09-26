// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// WOLBuddyOverlayRCMenuInit retail 0x004EADD0 649 bytes; ZH twin in
// WOLBuddyOverlay.cpp. The five format strings "%s:ButtonAdd" .. "%s:ButtonStats"
// and the five name-key stores at 0x012F424C..0x012F425C follow the ZH body
// line for line.

#include "string_base.h"
#include "ascii_string.h"

// Retail inlines the null-checked data pointer read at every str() site.
template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }

inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
	NameKeyType nameToKey(const AsciiString &name) { return nameToKey(name.str()); }
};

extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowLayout.h
class WindowLayout
{
public:
	AsciiString getFilename(void);
};

static NameKeyType buttonAddID = NAMEKEY_INVALID;
static NameKeyType buttonDeleteID = NAMEKEY_INVALID;
static NameKeyType buttonPlayID = NAMEKEY_INVALID;
static NameKeyType buttonIgnoreID = NAMEKEY_INVALID;
static NameKeyType buttonStatsID = NAMEKEY_INVALID;

// ?WOLBuddyOverlayRCMenuInit@@YAXPAVWindowLayout@@PAX@Z
void WOLBuddyOverlayRCMenuInit( WindowLayout *layout, void *userData )
{
	AsciiString controlName;
	controlName.format("%s:ButtonAdd",layout->getFilename().str()+6);
	buttonAddID =  TheNameKeyGenerator->nameToKey( controlName );
	controlName.format("%s:ButtonDelete",layout->getFilename().str()+6);
	buttonDeleteID =  TheNameKeyGenerator->nameToKey( controlName );
	controlName.format("%s:ButtonPlay",layout->getFilename().str()+6);
	buttonPlayID =  TheNameKeyGenerator->nameToKey( controlName );
	controlName.format("%s:ButtonIgnore",layout->getFilename().str()+6);
	buttonIgnoreID =  TheNameKeyGenerator->nameToKey( controlName );
	controlName.format("%s:ButtonStats",layout->getFilename().str()+6);
	buttonStatsID =  TheNameKeyGenerator->nameToKey( controlName );
}
