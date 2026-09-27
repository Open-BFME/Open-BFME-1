// ??0PartTheHeavensUpdateModuleData@@QAE@XZ
// partial score=0.9567567568 date=2026-09-27
// cl: /DNDEBUG /MD /O2 /EHsc
//
// ??0PartTheHeavensUpdateModuleData@@QAE@XZ -- retail 0x00299E10, 217 bytes.
//
// Identity: module_registry.tsv row PartTheHeavensUpdate (0x002999D0) and
// phantom_modules.tsv both name this address as the module-data ctor; the only
// caller is ?friend_newModuleData@PartTheHeavensUpdate@@SAPAVModuleData@ (the
// landed body in PartTheHeavensUpdateFriendNewModuleDataThunk.cpp, which news
// this class and hands it to INI::initFromINIMultiProc), and the adjacent
// matched destructor 0x00299F50 plus the scalar-deleting destructor 0x00299F20
// close the class.  The ctor installs vftable 0x010C08A8, the vtable this class
// owns per tools/vtable_lookup.py.
//
// Layout proven by the body itself and by the EH funclets of the scope table at
// 0x00C12144 (a dtor on the +0x00 subobject, BFMERetailAsciiString's dtor on
// +0x08, and the record dtor on +0x10 and +0x3C):
//
//   +0x00  base with the vptr store
//   +0x04  a dword no body in retail ever touches
//   +0x08  BFMERetailAsciiString (its destructor is the funclet at table+0x24)
//   +0x0C  a second dword the ctor zeroes and nothing else touches
//   +0x10  record 0, +0x3C record 1, +0x68 record 2, 0x2C bytes each
//
// Each record is 0x2C bytes: two dwords, a 0x10-byte three-pointer vector of
// 16-byte elements (the matched destructor 0x00299F50 tears down exactly
// [this+0x18], [this+0x44] and [this+0x70] = record+0x08 with the sar 4 / shl 4
// pair that gives 16), a dword the ctor never writes, a pointer reloaded from
// the vector's finish pointer, then four zeroed dwords nothing else ever
// touches.  The ctor body then calls ?set@Rva0006AB10Curve@@QAEXMMHH@Z on
// each record: (0,0,0,0), (0,1.0f,0,0), (0,0,0,0) -- the middle record is
// seeded with a unit value, the only difference between the three calls.
//
// The state byte the ctor stores to its EH frame before the first call counts
// the subobjects whose destructor runs on unwind, so every member above is a
// class with a real destructor.

struct Rva0006AA90Element;

// Layout as landed in game/GameEngine/Source/Common/Rva0006AB10CurveSet.cpp.
// Only the shape matters here; set() itself is the matched body in that TU.
class Rva0006AA90Vector
{
public:
	Rva0006AA90Vector()
	{
		m_start = 0;
		m_finish = 0;
		m_end = 0;
	}

	Rva0006AA90Element *m_start;
	// Retail reloads the finish pointer into the record's own pointer instead
	// of folding the zero it just stored, so the read is volatile.
	Rva0006AA90Element *volatile m_finish;
	Rva0006AA90Element *m_end;
	unsigned char m_padding;
	unsigned char m_flag;
	unsigned char m_reserved[2];
};
class Rva0006AB10Curve
{
public:
	Rva0006AB10Curve()
		: m_field0( 0 )
		, m_field4( 0 )
		, m_points()
		, m_current( m_points.m_finish )
	{
	}

	void set(float time, float value, int inTangent, int outTangent);

	int m_field0;
	int m_field4;
	Rva0006AA90Vector m_points;
	Rva0006AA90Element *m_current;
};
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString();

	char *m_data;
};

class Rva000299E10String
{
public:
	Rva000299E10String()
	{
		m_name.m_data = 0;
		m_unnamed = 0;
	}

	~Rva000299E10String() {}

	BFMERetailAsciiString m_name;
	int m_unnamed;
};

// One 0x2C record.  The four trailing dwords are zeroed by the ctor and are
// never read, freed or touched again anywhere in retail, so they carry no
// name beyond their position.
class Rva000299E10Record
{
public:
	Rva000299E10Record()
	{
		m_tail3 = 0;
		m_tail2 = 0;
		m_tail1 = 0;
		m_tail0 = 0;
	}

	~Rva000299E10Record();

	Rva0006AB10Curve m_curve;
	int m_tail0;
	int m_tail1;
	int m_tail2;
	int m_tail3;
};

// upstream layout:
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}
};

class PartTheHeavensUpdateModuleData : public Snapshot
{
public:
	PartTheHeavensUpdateModuleData();
	virtual ~PartTheHeavensUpdateModuleData();

private:
	int m_unnamed0;
	Rva000299E10String m_name;
	Rva000299E10Record m_record0;
	Rva000299E10Record m_record1;
	Rva000299E10Record m_record2;
};

PartTheHeavensUpdateModuleData::PartTheHeavensUpdateModuleData()
{
	m_record0.m_curve.set(0.0f, 0.0f, 0, 0);
	m_record1.m_curve.set(0.0f, 1.0f, 0, 0);
	m_record2.m_curve.set(0.0f, 0.0f, 0, 0);
}
