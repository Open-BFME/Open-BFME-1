// cl: /O2 /Ob0

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
// Retail runs the 16-byte base constructor at 0x007E86B0 here (vftable
// 0x01129358 plus a zeroed word at +4), not the 9-byte vptr-only body the
// ledger carries as ??0Snapshot@@QAE@XZ. SnapshotDupReplica is the
// TU-local spelling functions.csv already records as that body's object
// symbol.
class SnapshotDupReplica
{
public:
	SnapshotDupReplica();
	virtual void handle();
};

class Rva007F4DA0 : public SnapshotDupReplica
{
	int m_04;
	char m_08;
	char m_gap[0x1B];
	int m_24;

public:
	Rva007F4DA0();
};

Rva007F4DA0::Rva007F4DA0()
{
	m_08 = 0;
	m_24 = 0;
	m_04 = 1;
}
