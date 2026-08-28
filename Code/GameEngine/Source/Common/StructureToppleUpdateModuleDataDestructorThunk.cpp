// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// StructureToppleUpdateModuleData's destructor, lifted from its MASM dump to C++.
//
// Same ModuleData shape as ActiveBodyModuleData next door: no leading vptr
// store -- which is what the __declspec(novtable) is for -- four members at
// unwind states 3..0, and a single trailing `mov [esi],0x1073744` for the root
// base's vptr restore.
//
//   0x60  AsciiString                       direct 0x00887940
//   0x6C  3 x 12-byte class                 __ehvec_dtor(ptr, 0x0C, 3, dtor)
//   0x9C  _STL::vector<8-byte class>        thunk 0x00046A1A -> 0x0012A770
//   0xA8  _STL::vector<8-byte pod>          inlined (sar 3 / shl 3)
//
// The 0x9C vector holds elements with destructors, so its own destructor is
// out-of-line; its payload is spelled the way Code/gen_small/tgrid_*.cpp spells
// that instantiation, and the emitted destructor mangles to the name the ledger
// already carries at 0x0012A770. The 0xA8 vector's elements are trivially
// destructible, so retail frees it inline and only the 8-byte stride reaches
// the bytes. The array's element destructor is declared and never defined, so
// the address the iterator is handed stays a masked DIR32 -- its identity is
// unknown.

#include <vector>

// payload spelling from Code/gen_small/tgrid_*.cpp
struct Gen_t_0012a770_p8cd { int a[2]; Gen_t_0012a770_p8cd(); Gen_t_0012a770_p8cd(const Gen_t_0012a770_p8cd&); ~Gen_t_0012a770_p8cd(); Gen_t_0012a770_p8cd& operator=(const Gen_t_0012a770_p8cd&); };
bool operator==(const Gen_t_0012a770_p8cd&, const Gen_t_0012a770_p8cd&);
bool operator<(const Gen_t_0012a770_p8cd&, const Gen_t_0012a770_p8cd&);

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

// Array element: non-trivially destructible, identity unknown. Only its size
// and its destructor's address reach the bytes, and the address is masked.
class StructureToppleUpdateModuleDataSlot
{
public:
	~StructureToppleUpdateModuleDataSlot();

private:
	unsigned char m_unreconstructed_00[0x0c];
};

// Root base: vptr plus data out to 0x60, destructor inlined to the vptr restore.
class StructureToppleUpdateModuleDataBase
{
public:
	virtual ~StructureToppleUpdateModuleDataBase() {}

private:
	unsigned char m_unreconstructed_04[0x5c];			///< out to sizeof() == 0x60
};

class __declspec(novtable) StructureToppleUpdateModuleData : public StructureToppleUpdateModuleDataBase
{
public:
	virtual ~StructureToppleUpdateModuleData();

private:
	AsciiString m_unreconstructed_60;					///< retail this+0x60
	unsigned char m_unreconstructed_64[8];
	StructureToppleUpdateModuleDataSlot m_slots[3];		///< retail this+0x6C
	unsigned char m_unreconstructed_90[0x0c];
	_STL::vector<Gen_t_0012a770_p8cd> m_vectorA;		///< retail this+0x9C
	_STL::vector<Gen_p8pod> m_vectorB;					///< retail this+0xA8
};

// ??1StructureToppleUpdateModuleData@@UAE@XZ
StructureToppleUpdateModuleData::~StructureToppleUpdateModuleData()
{
}
