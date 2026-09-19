// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Three vectors and a string, destroyed in reverse declaration order with the
// unwind state counting down from 3: vectors at +0x70, +0x44 and +0x18, then the
// string at +0x08.
//
// Each vector teardown is inlined rather than called, so the element has no
// destructor, and the sar 4 / shl 4 pair puts its size at sixteen bytes. No vptr
// store appears at entry, so the class is novtable; the store of 0x01073744 at
// the end is Snapshot's, from the base destructor inlined last.
#include <vector>

struct HeavensEntry
{
	int m_a;
	int m_b;
	int m_c;
	int m_d;
};

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();

	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot() {}
};

class __declspec(novtable) PartTheHeavensUpdateModuleData : public Snapshot
{
public:
	virtual ~PartTheHeavensUpdateModuleData();

private:
	unsigned char m_gap0[0x04];
	BFMERetailAsciiString m_name;
	unsigned char m_gap1[0x0C];
	std::vector<HeavensEntry> m_vec0;
	unsigned char m_gap2[0x20];
	std::vector<HeavensEntry> m_vec1;
	unsigned char m_gap3[0x20];
	std::vector<HeavensEntry> m_vec2;
};

// ??1PartTheHeavensUpdateModuleData@@UAE@XZ
PartTheHeavensUpdateModuleData::~PartTheHeavensUpdateModuleData()
{
}
