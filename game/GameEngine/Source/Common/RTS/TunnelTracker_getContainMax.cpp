// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// TunnelTracker::getContainMax, retail 0x000F8520 (12 bytes, ILT 0x000456E2).
//
// Identity: CaveContain::getContainMax (0x002198D0) loads m_caveIndex,
// calls CaveSystem::getTunnelTrackerForCaveIndex on TheCaveSystem and
// tail-jumps here with the tracker in ecx, as Zero Hour's
// `TheCaveSystem->getTunnelTrackerForCaveIndex(m_caveIndex)->getContainMax()`.
// The body is Zero Hour's `return TheGlobalData->m_maxTunnelCapacity;` with
// BFME's GlobalData offset 0xB60 (Zero Hour's is 0x7D4, so
// TunnelTracker.cpp's copy cannot be retail's).

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_bfmePad[0xB60];
	int m_maxTunnelCapacity;	// +0xB60
};

// retail 0x012ED5C8: only Common/GlobalData.cpp defines it.
extern GlobalData *TheWritableGlobalData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/TunnelTracker.h
class TunnelTracker
{
public:
	int getContainMax() const;
};

int TunnelTracker::getContainMax() const
{
	return TheWritableGlobalData->m_maxTunnelCapacity;
}
