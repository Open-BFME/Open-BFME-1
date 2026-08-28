// Retail 0x00658340, 131 bytes: the target of the
// BFMENetworkQueueItem1::copyFromQueueNode incremental-link thunk.
//
// The body is not a void method. It ends mov eax,esi / ret 4, so it hands
// back this and takes one argument by reference -- a copy-assignment
// operator, which is why the pinned shim spelling (void return, void*
// argument) cannot be the definition's own name.
//
// The layout falls out of how the members are copied. +0x00 is a plain dword
// moved before the first call. +0x04 is handed to PSPlayerStats::operator=,
// and the next thing touched is +0x1C8, so that object is 0x1C4 bytes. The
// five dwords from +0x1C8 are copied through a pair of lea'd base registers
// rather than direct displacements, which is MSVC copying one POD struct
// member as a unit; the four dwords from +0x1DC use full displacements off
// esi and edi, so those are separate scalar members. The tail at +0x1EC is
// moved a byte at a time, so it is a bool.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PersistentStorageThread.h
class PSPlayerStats
{
public:
	PSPlayerStats &operator=(const PSPlayerStats &other);	// retail 0x000A5950

private:
	char m_bfmeStats[0x1C4];
};

struct BfmeQueueNodeRecord
{
	int m_bfmeWord0;
	int m_bfmeWord1;
	int m_bfmeWord2;
	int m_bfmeWord3;
	int m_bfmeWord4;
};

class BFMENetworkQueueItem1
{
public:
	BFMENetworkQueueItem1 &operator=(const BFMENetworkQueueItem1 &other);

	int m_bfmeKind;					// +0x000
	PSPlayerStats m_bfmeStats;			// +0x004
	BfmeQueueNodeRecord m_bfmeRecord;		// +0x1C8
	int m_bfmeExtra0;				// +0x1DC
	int m_bfmeExtra1;				// +0x1E0
	int m_bfmeExtra2;				// +0x1E4
	int m_bfmeExtra3;				// +0x1E8
	bool m_bfmeFlag;				// +0x1EC
};

// ??4BFMENetworkQueueItem1@@QAEAAV0@ABV0@@Z
BFMENetworkQueueItem1 &BFMENetworkQueueItem1::operator=(const BFMENetworkQueueItem1 &other)
{
	m_bfmeKind = other.m_bfmeKind;
	m_bfmeStats = other.m_bfmeStats;
	m_bfmeRecord = other.m_bfmeRecord;
	m_bfmeExtra0 = other.m_bfmeExtra0;
	m_bfmeExtra1 = other.m_bfmeExtra1;
	m_bfmeExtra2 = other.m_bfmeExtra2;
	m_bfmeExtra3 = other.m_bfmeExtra3;
	m_bfmeFlag = other.m_bfmeFlag;

	return *this;
}
