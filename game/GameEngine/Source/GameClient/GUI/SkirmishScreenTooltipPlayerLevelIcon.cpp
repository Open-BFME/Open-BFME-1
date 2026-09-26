// ?tooltipPlayerLevelIcon@BfmeAptScreenSkirmish@@QAEXVAsciiString@@PAX@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline /Igame/Libraries/Source/WWVegas/WWLib

#include "StringInline.h"

class SkirmishBattleHonors
{
public:
	int getRankDisplay( AsciiString name ) const;
};

class BfmeThingBIF
{
public:
	void bfmeGoBIF( void *what, void *out );
};

extern BfmeThingBIF *Rva00579160TheManager;

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
	Rva00579160TheManager->bfmeGoBIF(
		&AsciiString( (const char *)argument ), (void *)rank );
}
