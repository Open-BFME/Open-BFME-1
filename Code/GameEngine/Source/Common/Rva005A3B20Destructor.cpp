// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: near-twin of ??1CashHackSpecialPowerModuleData (0x00258E20,
// CashHackSpecialPowerModuleDataDestructorThunk.cpp); same std::vector<8-byte
// element> teardown (implicit dtor emits the sar 3 / shl 3 rounding and the
// operator-delete-vs-node_alloc split automatically), but our vector sits at
// +0xc behind a SubsystemInterface base (vtable + one int) instead of a large
// novtable head, and our class re-stores its own vtable then chains to the
// base destructor explicitly instead of leaving it out-of-line.

#include <vector>

struct Rva005A3B20Entry
{
	int m_a;
	int m_b;
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	int m_bfmeSubsystem04;
};

class Rva005A3B20 : public SubsystemInterface
{
public:
	virtual ~Rva005A3B20();

private:
	unsigned char m_pad[0xc - 8];
	std::vector<Rva005A3B20Entry> m_entries;
};

// ?d_005a3b20@@YAXXZ
Rva005A3B20::~Rva005A3B20()
{
}
