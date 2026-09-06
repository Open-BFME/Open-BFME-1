// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/weapon /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Open-BFME7: retail 0x001E8670 (138 bytes) is Weapon::rebuildScatterTargets with BFME's
// layouts: the template pointer at +4, the unused-target index vector at +0x40 and the
// template's 8-byte scatter records at +0x34.  Address-tagged classes carry only those fields.
#include "PreRTS.h"

struct Rva001E8670Scatter { int m_a; int m_b; };

class Rva001E8670Template
{
public:
	const std::vector<Rva001E8670Scatter> &getScatterTargetsVector() const { return m_scatterTargets; }
private:
	unsigned char m_pad00[0x34];
	std::vector<Rva001E8670Scatter> m_scatterTargets;	// +0x34
};

class Rva001E8670Weapon
{
public:
	void rebuildScatterTargets();
private:
	unsigned char m_pad00[4];
	const Rva001E8670Template *m_template;		// +0x04
	unsigned char m_pad08[0x40 - 8];
	std::vector<Int> m_scatterTargetsUnused;		// +0x40
};

void Rva001E8670Weapon::rebuildScatterTargets()
{
	m_scatterTargetsUnused.clear();
	Int scatterTargetsCount = m_template->getScatterTargetsVector().size();
	if (scatterTargetsCount)
	{
		for (Int targetIndex = 0; targetIndex < scatterTargetsCount; targetIndex++)
			m_scatterTargetsUnused.push_back( targetIndex );
	}
}
