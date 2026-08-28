// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?canSwitchIndexToIndex@CaveSystem@@QAE_NHH@Z: Code/GameEngine/Source/GameLogic/System/CaveSystem.cpp
// Open-BFME: CaveSystem::canSwitchIndexToIndex, retail 0x003782D0, 89 bytes.
//
// The reference's body unchanged but for one BFME difference: getContainCount
// takes an argument here, and both calls pass zero.
//
// The tracker vector is at this+0x0C, and both bounds checks recompute its
// size from _M_start and _M_finish rather than caching it -- the call in
// between is enough. The comparison is unsigned, which is what the reference's
// size() against a signed index comes to, and the count is unsigned too.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/TunnelTracker.h
class TunnelTracker
{
public:
	UnsignedInt getContainCount(Int bfmeArg);		// ILT 0x00036165
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/CaveSystem.h
class CaveSystem
{
public:
	Bool canSwitchIndexToIndex(Int oldIndex, Int newIndex);

private:
	char m_slice_pad[0x0C];					// retail this+0x00 .. +0x0B, untouched
	_STL::vector<TunnelTracker *> m_tunnelTrackerVector;	// this+0x0C
};

Bool CaveSystem::canSwitchIndexToIndex( Int oldIndex, Int newIndex )
{
	TunnelTracker *oldTracker = 0;
	TunnelTracker *newTracker = 0;
	if( m_tunnelTrackerVector.size() > oldIndex )
	{
		oldTracker = m_tunnelTrackerVector[oldIndex];
		if( oldTracker && oldTracker->getContainCount(0) > 0 )
			return false;// You can't switch a connection if one of the two is non empty
	}
	if( m_tunnelTrackerVector.size() > newIndex )
	{
		newTracker = m_tunnelTrackerVector[newIndex];
		if( newTracker && newTracker->getContainCount(0) > 0 )
			return false;// You can't switch a connection if one of the two is non empty
	}

	return true;
}
