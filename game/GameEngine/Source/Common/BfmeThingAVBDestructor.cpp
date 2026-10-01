// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME5: BfmeThingAVB destructor at retail 0x003B5170 (111B).
// Sibling of blocked ctor 0x003B5100. Dual inheritance: SubsystemInterface-sized
// primary base (dtor 0x009A1A40) plus Snapshot-like secondary at +0x08 (inline
// empty dtor restoring 0x01073744), then vector members at +0x10 (0x003B47F0 via
// ILT 0x00046939) and +0x20 (0x00363750 via ILT 0x00035D8C).

struct Gen_uwm_00046939
{
	~Gen_uwm_00046939();

private:
	char m_bytes[12];
};

struct Gen_uwm_00035d8c
{
	~Gen_uwm_00035d8c();

private:
	char m_bytes[12];
};

// The primary base is the real SubsystemInterface, not a TU-local stand-in:
// retail's 0x009A1A40 body is its destructor, and the header's `AsciiString
// m_name` at +0x04 is the same four bytes the old `int m_name04` stood for.
typedef bool Bool;
#include "System/subsystem_interface.h"

struct BfmeThingAVBSecondary
{
	virtual ~BfmeThingAVBSecondary() {}

private:
	int m_field04;
};

class BfmeThingAVB : public SubsystemInterface, public BfmeThingAVBSecondary
{
public:
	virtual ~BfmeThingAVB();

private:
	Gen_uwm_00046939 m_vec10;
	char m_flag1C;
	char m_flag1D;
	char m_pad1E;
	char m_pad1F;
	Gen_uwm_00035d8c m_vec20;
};

// ??1BfmeThingAVB@@UAE@XZ
BfmeThingAVB::~BfmeThingAVB()
{
}
