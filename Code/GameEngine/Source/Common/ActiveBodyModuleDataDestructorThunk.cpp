// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// ActiveBodyModuleData's destructor, lifted from its MASM dump to C++.
//
// The ModuleData shape: no leading vptr store at all, four members at unwind
// states 3..0, and a single trailing `mov [esi],0x1073744` -- the root base's
// vptr restore with its destructor inlined away. The __declspec(novtable) is
// what suppresses the leading store; without it MSVC opens the destructor by
// writing this class's own vptr and retail does not.
//
//   0x2C  AsciiString                  direct 0x00887940
//   0x30  AsciiString                  direct 0x00887940
//   0x34  AsciiString                  direct 0x00887940
//   0x50  _STL::vector<12-byte pod>    inlined (imul 0x2AAAAAAB then *12)
//
// 0x00887940 is the AsciiString destructor body the ledger already pins under
// that name. The vector's elements are trivially destructible, so retail frees
// it inline and the 12-byte stride is all the bytes pin.

#include <vector>

// vector elements: trivially destructible, so only their size reaches the bytes
struct Gen_p12pod { int a[3]; };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

// Root base: vptr plus data out to 0x2C, destructor inlined to the vptr restore.
class ActiveBodyModuleDataBase
{
public:
	virtual ~ActiveBodyModuleDataBase() {}

private:
	unsigned char m_unreconstructed_04[0x28];			///< out to sizeof() == 0x2C
};

class __declspec(novtable) ActiveBodyModuleData : public ActiveBodyModuleDataBase
{
public:
	virtual ~ActiveBodyModuleData();

private:
	AsciiString m_unreconstructed_2c;					///< retail this+0x2C
	AsciiString m_unreconstructed_30;					///< retail this+0x30
	AsciiString m_unreconstructed_34;					///< retail this+0x34
	unsigned char m_unreconstructed_38[0x18];
	_STL::vector<Gen_p12pod> m_vector;					///< retail this+0x50
};

// ??1ActiveBodyModuleData@@UAE@XZ
ActiveBodyModuleData::~ActiveBodyModuleData()
{
}
