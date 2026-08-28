// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: PathfindZoneManager::markZonesDirty, retail 0x004030D0, 6 bytes.
// The body carried only a machine byte-dump row; reverse/reloc_names.csv holds
// the name with identity=real.
//
// Both arguments are ignored: whatever they once selected, this build just sets
// the flag at +0 and returns.

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindZoneManager
{
public:
	void markZonesDirty(Bool a, Bool b);

private:
	Bool m_bfmeDirty;					// +0x00
};

// ?markZonesDirty@PathfindZoneManager@@QAEX_N0@Z
void PathfindZoneManager::markZonesDirty(Bool a, Bool b)
{
	m_bfmeDirty = true;
}
