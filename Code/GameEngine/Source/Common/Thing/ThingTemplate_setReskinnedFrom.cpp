// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// ThingTemplate::setReskinnedFrom, retail 0x00146840 (72 bytes), reached through
// ILT 0x00047799 from its sole caller at 0x00139EA8 in
// ThingFactory::parseObjectDefinition, at Zero Hour's setReskinnedFrom point
// (after copyFrom and setCopiedFromDefault, before initFromINI). Zero Hour
// stores the pointer in m_reskinnedFrom; BFME appends the reskin source's name
// (+0x20) to the vector of names at +0x2DC, which isEquivalentTo (0x0013FE10)
// compares where Zero Hour compares m_reskinnedFrom.
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
#include "PreRTS.h"

class ThingTemplate : public Overridable
{
public:
	void setReskinnedFrom( const ThingTemplate *tt );

private:
	char m_unmodelled0C[0x20 - 0x0C];
	AsciiString m_nameString;							// +0x020
	char m_unmodelled24[0x2DC - 0x24];
	std::vector<AsciiString> m_field2DC;				// +0x2DC, BFME-only
};

void ThingTemplate::setReskinnedFrom( const ThingTemplate *tt )
{
	m_field2DC.push_back( tt->m_nameString );
}
