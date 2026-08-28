// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// CritterEmitterUpdateModuleData's destructor, lifted from its MASM dump to C++.
//
// Five things are destroyed and the unwind states say how they are related:
// four run at 3, 2, 1, 0 and the subobject at 0x08 runs last, at state 4.
// That ordering is the whole puzzle. A base class cannot produce it -- MSVC
// numbers bases before members, so making 0x08 a direct base numbers it 0 and
// pushes the members to 1..4. What does produce it is an intermediate class
// with an inline destructor: its member is destroyed after the derived class's
// own members and gets a state numbered after them.
//
//   0x08  member of the intermediate base   thunk 0x0001B97D -> 0x00129C80
//   0xA4  AsciiString                       direct 0x00887940
//   0xA8  _STL::vector<8-byte pod>          inlined (sar 3 / shl 3)
//   0xB4  12-byte member with a destructor  thunk 0x00038055 -> 0x001FA220
//   0xC0  AsciiString                       direct 0x00887940
//
// The trailing `mov [esi],0x1073744` is the root base's vptr restore with its
// destructor inlined away, so that base is a vptr plus one word. It is also the
// ONLY vptr store retail emits, which is what the two __declspec(novtable)s are
// for: without them MSVC opens the destructor by storing this class's vptr and
// stores the intermediate base's again before its member, and retail does
// neither.
//
// 0x00887940 is the AsciiString destructor body the ledger already pins under
// that name. The destructors at 0x00129C80 and 0x001FA220 are unclaimed and
// unidentified; they are named for their offsets here and pinned at the thunk
// addresses their call sites encode, which is all the bytes say about them.

#include <vector>

// vector elements: trivially destructible, so only their size reaches the bytes
struct Gen_p8pod { int a[2]; };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

// Member at 0x08 of the intermediate base, destroyed out-of-line at 0x00129C80.
// Identity unknown.
class CritterEmitterUpdateModuleDataInner
{
public:
	~CritterEmitterUpdateModuleDataInner();

private:
	unsigned char m_unreconstructed_00[0x9c];			///< 0x08 out to 0xA4
};

// Member at 0xB4, destroyed out-of-line at 0x001FA220. Identity unknown.
class CritterEmitterUpdateModuleDataUnknownB4
{
public:
	~CritterEmitterUpdateModuleDataUnknownB4();

private:
	unsigned char m_unreconstructed_00[12];
};

// Root base: vptr plus one word, destructor inlined to the vptr restore.
class CritterEmitterUpdateModuleDataRootBase
{
public:
	virtual ~CritterEmitterUpdateModuleDataRootBase() {}

private:
	void *m_unreconstructed_04;
};

// Intermediate base: destructor inline, so its member's cleanup is emitted here
// and numbered after the derived class's members.
class __declspec(novtable) CritterEmitterUpdateModuleDataBase : public CritterEmitterUpdateModuleDataRootBase
{
public:
	virtual ~CritterEmitterUpdateModuleDataBase() {}

private:
	CritterEmitterUpdateModuleDataInner m_unreconstructed_08;	///< retail this+0x008
};

class __declspec(novtable) CritterEmitterUpdateModuleData : public CritterEmitterUpdateModuleDataBase
{
public:
	virtual ~CritterEmitterUpdateModuleData();

private:
	AsciiString m_unreconstructed_a4;					///< retail this+0x0A4
	_STL::vector<Gen_p8pod> m_vector;					///< retail this+0x0A8
	CritterEmitterUpdateModuleDataUnknownB4 m_unreconstructed_b4;	///< retail this+0x0B4
	AsciiString m_unreconstructed_c0;					///< retail this+0x0C0
};

// ??1CritterEmitterUpdateModuleData@@UAE@XZ
CritterEmitterUpdateModuleData::~CritterEmitterUpdateModuleData()
{
}
