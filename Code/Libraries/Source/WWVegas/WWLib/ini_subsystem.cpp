// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Oy- /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// The subsystem loader: look a subsystem up in the legend by name and load every
// INI file its "LoadSubsystem" block lists. This is the function that makes
// SubsystemLegend mean something — the legend is a manifest, and this is what
// reads it.
//
// Retail's home for it is ini.cpp: 0x000BB310 sits in that TU's arena, directly
// after INI::parseThingTemplate / parseParticleSystemTemplate / parseUpgradeTemplate
// (0x000BAD6A..0x000BB040), and shares their EH funcinfo run. It lives here
// instead because ini.cpp is still a ZH-tree port, and ZH's AsciiString inlines
// its release path while this function needs the out-of-line StringBase<char>
// calls retail makes. Fold it into ini.cpp when that file goes native.
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
#include "subsystem_legend.h"
#include "Common/INI/INI.h"

// The try sits inside the loop, not around it. That is not a style choice: with
// the try outside, MSVC hoists both EH-state stores above the loop test, while
// retail re-executes them every iteration — mov [ebp-4],0 between the cmp and
// the je, mov [ebp-4],1 in the body. Per-iteration scope is what reproduces
// that, and it says the loader abandons the whole subsystem at the first bad
// file rather than skipping it.
bool INI::loadSubsystemFiles(const char *subsystem, void *xfer)
{
	SubsystemLegendEntry *entry = TheSubsystemLegend->findEntry(AsciiString(subsystem));
	if (entry)
	{
		INI ini;
		for (std::vector<AsciiString>::iterator f = entry->m_initFile.begin();
			 f != entry->m_initFile.end(); ++f)
		{
			try
			{
				ini.load(*f, 1, 0, xfer);
			}
			catch (...)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}
