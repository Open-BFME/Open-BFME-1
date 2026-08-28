// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: per-TU GhostObjectManager constructor at retail 0x007E87F0.
// Model the duplicate with a unique C++ type because its separately emitted
// vtable is not the canonical GhostObjectManager vtable in this executable.
//
// The sibling Energy constructor analysis identifies this body's folded
// vtable and the Snapshot copy at 0x007E86B0.  The reference member order
// places m_localPlayer at +4 and the two lock values at +8/+0C; the reference
// constructor's assignment order produces retail's +8, +0C, +4 stores.

typedef int Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot();
	virtual void crc() {}
	virtual void xfer() {}
	virtual void loadPostProcess() {}
};

class GhostObjectManagerEnergyDup : public Snapshot
{
public:
	GhostObjectManagerEnergyDup();

private:
	int m_localPlayer;
	Bool m_lockGhostObjects;
	Bool m_saveLockGhostObjects;
};

// ??0GhostObjectManagerEnergyDup@@QAE@XZ present-unmatched
GhostObjectManagerEnergyDup::GhostObjectManagerEnergyDup()
{
	m_lockGhostObjects = 0;
	m_saveLockGhostObjects = 0;
	m_localPlayer = 0;
}
