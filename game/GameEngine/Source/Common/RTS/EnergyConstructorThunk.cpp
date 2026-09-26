// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: Energy's default constructor, retail 0x00808880.
//
// Shape: call the SnapshotDupReplica constructor at 0x007E86B0, zero four dwords at +4,
// +8, +0xc and +0x10, then store the vtable at +0. Zero Hour's Energy::Energy
// assigns exactly four members -- m_energyProduction, m_energyConsumption,
// m_owner, m_powerSabotagedTillFrame -- and with the SnapshotDupReplica vptr at +0 those
// four offsets are exactly what gets written.
//
// Retail writes them in the order 8, 0xc, 4, 0x10. A constructor body emits its
// assignments in source order, so that ordering is the DECLARATION order
// talking: m_owner sits at +0x04, ahead of the two counters, where ZH declares
// it third. Keeping ZH's assignment order and moving the declaration reproduces
// the sequence exactly; reordering the body instead would not, since the fourth
// write would still trail.
//
// The identification rests on that member count and the packet's alignment,
// NOT on the vtable: the address stored there, 0x011296B0, is also what
// ??0GhostObjectManager@@QAE@XZ at 0x007E87F0 stores, so the two vtables are
// COMDAT-folded and the operand distinguishes nothing. It is a relocation and
// masked from the comparison anyway. A "SnapshotDupReplica constructor, zero N dwords,
// set vtable" body is boilerplate shared by every SnapshotDupReplica subclass with N
// scalar members; N is the only discriminator these bytes carry.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
// Retail runs the 16-byte base constructor at 0x007E86B0 here (vftable
// 0x01129358 plus a zeroed word at +4), not the 9-byte vptr-only body the
// ledger carries as ??0Snapshot@@QAE@XZ. SnapshotDupReplica is the
// TU-local spelling functions.csv already records as that body's object
// symbol.
class SnapshotDupReplica
{
public:
	SnapshotDupReplica();										///< 0x007E86B0
	virtual void crc() {}
	virtual void xfer() {}
	virtual void loadPostProcess() {}
};

class Player;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Energy.h
class Energy : public SnapshotDupReplica
{
public:
	Energy();

private:
	Player *m_owner;								///< retail this+0x04
	int m_energyProduction;							///< retail this+0x08
	int m_energyConsumption;						///< retail this+0x0c
	int m_powerSabotagedTillFrame;					///< retail this+0x10
};

// ??0Energy@@QAE@XZ
Energy::Energy()
{
	m_energyProduction = 0;
	m_energyConsumption = 0;
	m_owner = 0;
	m_powerSabotagedTillFrame = 0;
}
