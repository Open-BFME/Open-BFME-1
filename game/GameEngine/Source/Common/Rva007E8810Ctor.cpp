// cl: /O2 /Ob0

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
// Retail runs the 16-byte base constructor at 0x007E86B0 here (vftable
// 0x01129358 plus a zeroed word at +4), not the 9-byte vptr-only body the
// ledger carries as ??0Snapshot@@QAE@XZ. SnapshotDupReplica is the
// TU-local spelling functions.csv already records as that body's object
// symbol.
// Retail stores vftable 0x011296B0, the table Rva007F6D60ChildConstructor.cpp
// emits (dir32 row ??_7Rva007F6D60Member2C@@6B@). A virtual handle() here would emit a
// non-retail vftable that leaves ?handle@SnapshotDupReplica unresolved, so the
// vptr is a plain word stored by name.
extern "C" void *__identifier("??_7Rva007F6D60Member2C@@6B@")[];

class SnapshotDupReplica
{
public:
	SnapshotDupReplica();
	void *m_vptr;
};

class Rva007E8810 : public SnapshotDupReplica
{
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	char m_30;

public:
	Rva007E8810();
};

Rva007E8810::Rva007E8810()
{
	m_vptr = (void *)__identifier("??_7Rva007F6D60Member2C@@6B@");
	m_08 = 0;
	m_0C = 0;
	m_04 = 0;
	m_10 = 0;
	m_18 = 0;
	m_14 = 0;
	m_28 = 0;
	m_24 = 0;
	m_20 = 0;
	m_1C = 0;
	m_30 = 0;
	m_2C = 4;
}
