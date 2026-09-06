// cl: /DNDEBUG /MD /EHsc
//
// retail 0x0024E8E0, size 141, dump d_0024e310.asm.
//
// Fuzzy twin: GarrisonContain::~GarrisonContain (0x0021D9C0, r0.925,
// GarrisonContainDestructor.cpp) -- SAME nine-polymorphic-subobject vtable
// install shape (offsets 0, 0xc, 0x10, 0x20, 0x24, 0x28, 0x2c, 0x30, 0x34,
// matching the twin's OpenContain layout exactly), but the callee set
// differs: this destructor releases a BFMERetailAsciiString at this+0x9c0
// and then calls a base destructor still pinned only as a placeholder
// (??1Gen_dtor_0021e310@@UAE@XZ, 0x00037A24) whose REAL address does not
// match the already-landed ??1OpenContain@@UAE@XZ (0x002262E0). So the
// nine-vtable base hierarchy here is shape-identical to but NOT the same
// class as the twin's OpenContain -- copied under fresh names and pinned to
// the address this body's callee list actually proves (0x00037A24), leaving
// the real OpenContain pin untouched.
//
// installs vtable(s): 0x010B11C0 (SlaughterHordeContain primary), 0x010B10F8,
// 0x010B10E8, 0x010B0F40, 0x010B0F20, 0x010B0F1C, 0x010B0F0C, 0x010B0ED0,
// 0x010B0EC0 (SlaughterHordeContain interface vtables; see
// reverse/symbols.csv _SlaughterHordeContain_vtbl* pins).
// landed neighbours: ??1SlaughterHordeContain@@UAE@XZ 0x0024EB00 (329B,
// SlaughterHordeContainDestructorThunk.cpp, a naked lift of the DERIVED
// class's larger destructor); ?getModuleNameKey@SlaughterHordeContain@@
// 0x0024E850 (ModuleNameKeys_04.cpp) confirms the class name from the
// vtable-carrying-function evidence (tools/vtable_lookup.py).

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

// Shape-identical to GarrisonContainDestructor.cpp's OpenContain, but a
// DIFFERENT compiled instance (see header comment) -- fresh names, own pin.
class __declspec(novtable) Rva0024E8E0OpenContainLike
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
	virtual ~Rva0024E8E0OpenContainLike();		// ??1Rva0024E8E0OpenContainLike@@UAE@XZ, pinned 0x00037A24

private:
	unsigned char m_pad[0x3c4];
};

template <typename T>
class StringBase
{
public:
	~StringBase()
	{
		releaseBuffer();
	}

	void *m_data;

private:
	void releaseBuffer();
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	~BFMERetailAsciiString() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlaughterHordeContain.h
class SlaughterHordeContainBase : public Rva0024E8E0OpenContainLike
{
public:
	virtual ~SlaughterHordeContainBase();

private:
	unsigned char m_unreconstructed[0x9c0 - sizeof(Rva0024E8E0OpenContainLike)];
	BFMERetailAsciiString m_name;			// this+0x9c0
};

// ?d_0024e8e0@@YAXXZ -- address-derived; real name/signature not recovered.
SlaughterHordeContainBase::~SlaughterHordeContainBase()
{
}
