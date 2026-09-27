// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// RVA 005668C0, 300 bytes: native virtual destructor for the separate
// 28-byte object constructed at 00566EC0 and embedded at screen+390.
// This definition also naturally emits its 30-byte deleting destructor at
// 00566AE0. See identity_evidence/00566ec0-profile-family.md.

#include "ascii_string.h"

class SkirmishPreferences
{
public:
	virtual ~SkirmishPreferences();
	char field04[0x14];
};

class WindowManager
{
public:
	void removeAptObject( const AsciiString &name );
};

extern WindowManager *g_theWindowManager;

class Rva00566EC0Profile;
extern Rva00566EC0Profile *Rva012F4B3CProfile;

class Rva00566EC0Profile
{
public:
	virtual ~Rva00566EC0Profile();

private:
	SkirmishPreferences m_prefs;
};

Rva00566EC0Profile::~Rva00566EC0Profile()
{
	if( Rva012F4B3CProfile == this )
	{
		if( g_theWindowManager )
		{
			{
				AsciiString name( "Skirmish/tooltipPlayerLevelIconGondor" );
				g_theWindowManager->removeAptObject( name );
			}
			{
				AsciiString name( "Skirmish/tooltipPlayerLevelIconRohan" );
				g_theWindowManager->removeAptObject( name );
			}
			{
				AsciiString name( "Skirmish/tooltipPlayerLevelIconIsengard" );
				g_theWindowManager->removeAptObject( name );
			}
			{
				AsciiString name( "Skirmish/tooltipPlayerLevelIconMordor" );
				g_theWindowManager->removeAptObject( name );
			}
		}
		Rva012F4B3CProfile = 0;
	}
}
