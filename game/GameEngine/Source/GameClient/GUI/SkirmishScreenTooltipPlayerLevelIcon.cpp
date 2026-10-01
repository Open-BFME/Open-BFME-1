// ?tooltipPlayerLevelIcon@BfmeAptScreenSkirmish@@QAEXVAsciiString@@PAX@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline /Igame/Libraries/Source/WWVegas/WWLib

#include "StringInline.h"

class SkirmishBattleHonors
{
public:
	int getRankDisplay( AsciiString name ) const;
};

// Local view of the one method this body reaches on retail's 0x012F19E8
// global, which is a WindowManager*.
class BfmeThingBIF
{
public:
	void bfmeGoBIF( void *what, void *out );
};

class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;

class BfmeAptScreenSkirmish
{
public:
	void tooltipPlayerLevelIcon( AsciiString name, void *argument );

private:
	char m_unmodelled[ 0x3c4 ];
	SkirmishBattleHonors m_honors;
};

void BfmeAptScreenSkirmish::tooltipPlayerLevelIcon(
	AsciiString name, void *argument )
{
	int rank = m_honors.getRankDisplay( name );
	((BfmeThingBIF *)g_rva012F19E8WindowManager)->bfmeGoBIF(
		&AsciiString( (const char *)argument ), (void *)rank );
}
