// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Include /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Retail RVA 003DE6E0, 446 bytes: Pathfinder constructor. The matched
// complete destructor at 003DC040 proves the multiple-inheritance layout,
// sixteen 0x44-byte layers, zone manager, 64 strings, tree and vector.
// Native containers and typed zeroing loops reproduce construction and unwind.
// Unknown member names retain offsets; registration callback retains its ILT.

#include "ascii_string.h"

#include "Common/INI/INI.h"
#include <set>
#include <vector>
typedef unsigned int Rva003DE6E0UInt;

// Layout-only virtual bases. The retail Snapshot order is destructor,
// 003DC160 no-op, 003DC170 name getter, 003E38F0 xfer. Neither existing
// Snapshot header has that order, so this constructor uses an address view.
class Rva00CEE5C8PathServices
{
public:
 virtual void slot00(); virtual void slot01(); virtual void slot02();
 virtual void slot03(); virtual void slot04();
};
class Rva00C73744SnapshotBase
{
public:
 virtual ~Rva00C73744SnapshotBase() {}
 virtual void rva003DC160() = 0;
 virtual const char *rva003DC170() = 0;
 virtual void rva003E38F0(Xfer *) = 0;
};

class PathfindLayer
{
public:
	PathfindLayer();
	~PathfindLayer();
	char m_unknown[0x44];
};

class PathfindZoneManager
{
public:
	PathfindZoneManager();
	~PathfindZoneManager();
	char m_unknown[0x23860];
};

// The INI registry's canonical row is a 12-byte singly-linked registration
// record (Common/INI/ini.cpp). This constructor stores the callback but
// never invokes it; preserve ILT 000352AB without asserting its identity.
extern void j_000352ab();

struct BlockParse
{
	BlockParse *next;
	const char *token;
	void *callback;
	BlockParse(const char *name, void *function);
};
extern BlockParse *theBlockParseList;

BlockParse::BlockParse(const char *name, void *function)
	: next(theBlockParseList), token(name), callback(function)
{
	theBlockParseList = this;
}

struct Rva003DE6E0VectorEntry { unsigned int words[3]; };

class Pathfinder : private Rva00CEE5C8PathServices, public Rva00C73744SnapshotBase
{
public:
	Pathfinder();
	virtual ~Pathfinder();
	virtual void rva003DC160();
	virtual const char *rva003DC170();
	virtual void rva003E38F0(Xfer *);
	void reset();

	char m_prefix[4];                         // +0x08..+0x0b
	Rva003DE6E0UInt m_field0C;                // +0x0c
	Rva003DE6E0UInt m_field10;                // +0x10
	char m_unknown14[0x20];
	Rva003DE6E0UInt m_at034[512];                  // +0x34..+0x833
	Rva003DE6E0UInt m_field834;              // +0x834
	Rva003DE6E0UInt m_field838;              // +0x838
	char m_unknown83C[0x18];                  // +0x83c..+0x853
	Rva003DE6E0UInt m_field854;              // +0x854
	Rva003DE6E0UInt m_field858;              // +0x858
	PathfindLayer m_layers[16];               // +0x85c
	PathfindZoneManager m_zoneManager;        // +0xc9c
	AsciiString m_strings[64];                // +0x244fc
	Rva003DE6E0UInt m_at245FC[64];           // +0x245fc
	char m_gap246FC[4];
	std::set<unsigned int> m_set;
	std::vector<Rva003DE6E0VectorEntry> m_vector;
};

Pathfinder::Pathfinder()
	: m_field0C(0), m_field10(0), m_field834(0x200), m_field838(0),
	  m_field854(0), m_field858(0)
{
	for (int i=0;i<64;++i) m_at245FC[i]=0;
	for (int j=0;j<512;++j) m_at034[j]=0;
	reset();

	static BlockParse pathfinderRegistration(
		"Pathfinder", (void *)j_000352ab);

	INI ini;
	ini.loadFile(AsciiString("Data\\INI\\Pathfinder.ini"), INI_LOAD_OVERWRITE, (Xfer *)0);
}
