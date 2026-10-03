// cl: /DNDEBUG /MD /EHsc
//
// retail 0x0024E8E0, size 141, dump d_0024e310.asm.
//
// The base-destructor ILT 0x00037A24 routes to the matched GarrisonContain
// destructor at 0x0021D9C0 (GarrisonContainDestructor.cpp). Its nine inherited
// vfptrs occupy 0, 0xc, 0x10, 0x20, 0x24, 0x28, 0x2c, 0x30 and 0x34.
// The narrow string at this+0x9c0 releases through StringBase<char>.
//
// installs vtable(s): 0x010B11C0 (SlaughterHordeContain primary), 0x010B10F8,
// 0x010B10E8, 0x010B0F40, 0x010B0F20, 0x010B0F1C, 0x010B0F0C, 0x010B0ED0,
// 0x010B0EC0 (SlaughterHordeContain interface vtables; see
// targets/game/reverse/symbols.csv _SlaughterHordeContain_vtbl* pins).
// landed neighbours: ??1SlaughterHordeContain@@UAE@XZ 0x0024EB00 (329B,
// SlaughterHordeContainDestructorThunk.cpp, a naked lift of the DERIVED
// class's larger destructor); ?getModuleNameKey@SlaughterHordeContain@@
// 0x0024E850 (ModuleNameKeys_04.cpp) confirms the class name from the
// vtable-carrying-function evidence (tools/vtable_lookup.py).

#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Rva0024E8E0PrimaryBase
{
public:
	virtual ~Rva0024E8E0PrimaryBase() {}

private:
	unsigned char m_pad[8];
};

template <int Number>
class Rva0024E8E0SecondaryBase
{
public:
	virtual ~Rva0024E8E0SecondaryBase() {}
};

class Rva0024E8E0WideSecondaryBase
{
public:
	virtual ~Rva0024E8E0WideSecondaryBase() {}

private:
	unsigned char m_pad[12];
};

// GarrisonContainDestructor.cpp establishes the full 0x99c-byte base extent;
// only its nine vfptrs need explicit layout in this derived destructor.
class __declspec(novtable) GarrisonContain
	: public Rva0024E8E0PrimaryBase,
	  public Rva0024E8E0SecondaryBase<1>,
	  public Rva0024E8E0WideSecondaryBase,
	  public Rva0024E8E0SecondaryBase<2>,
	  public Rva0024E8E0SecondaryBase<3>,
	  public Rva0024E8E0SecondaryBase<4>,
	  public Rva0024E8E0SecondaryBase<5>,
	  public Rva0024E8E0SecondaryBase<6>,
	  public Rva0024E8E0SecondaryBase<7>
{
public:
	virtual ~GarrisonContain();		// ILT 0x00037A24 -> 0x0021D9C0

private:
	unsigned char m_pad[0x99c - 0x38];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlaughterHordeContain.h
class SlaughterHordeContainBase : public GarrisonContain
{
public:
	virtual ~SlaughterHordeContainBase();

private:
	unsigned char m_unreconstructed[0x9c0 - sizeof(GarrisonContain)];
	AsciiString m_name;			// this+0x9c0
};

// ?d_0024e8e0@@YAXXZ -- address-derived; real name/signature not recovered.
SlaughterHordeContainBase::~SlaughterHordeContainBase()
{
}
