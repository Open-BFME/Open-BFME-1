// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// TransitionDamageFXModuleData's destructor, lifted from its MASM dump to C++.
//
// The ModuleData shape: no leading vptr store -- which is what the
// __declspec(novtable) is for -- members at unwind states 5..0, and a single
// trailing `mov [esi],0x1073744` for the root base's vptr restore with its
// destructor inlined away.
//
// Five of the six members are arrays run through the eh vector destructor
// iterator, and its argument list is the whole specification the bytes give:
//
//   0x000C  0x30 x 0x1C   element destructor 0x0041074E
//   0x0550  0x30 x 0x1C   element destructor 0x00415703
//   0x0A94  0x30 x 0x1C   element destructor 0x0042E451
//   0x0FD4  4 x 0x0C      element destructor 0x00426AB2
//   0x1004  4 x 0x0C      element destructor 0x00426AB2
//   0x1034  out-of-line destructor, thunk 0x0003D2C1 -> 0x00252DA0
//
// The three 0x1C-byte arrays have three different element destructors, so they
// are three different types despite the shared stride; the two 0x0C-byte arrays
// share one, so they are the same type. SlotA now uses independently proved
// native AsciiString destruction at element+8. The other array callbacks
// retain their previous declarations pending separate ownership repairs.
// The 0x1034 member's destructor is called
// rather than pushed, and its body is already named in the ledger, so it is
// spelled under that name below.

// C0E9A8 owns the48-element array at0C. Its callback ILT1074E ->252370
// releases the canonical AsciiString at element+8. Other callback owners
// remain distinct (252390 and2523B0); no identical-body identity merging.
#include "ascii_string.h"
class FXDamageFXListInfo
{
public:
    ~FXDamageFXListInfo() {}
private:
    unsigned char m_unreconstructed_00[8];
    AsciiString m_unreconstructed_08;
    unsigned char m_unreconstructed_0c[0x10];
};
class FXDamageOCLInfo { public: ~FXDamageOCLInfo(); private: unsigned char m_unreconstructed_00[0x1c]; };
class FXDamageParticleSystemInfo { public: ~FXDamageParticleSystemInfo(); private: unsigned char m_unreconstructed_00[0x1c]; };
class TransitionDamageFXSlotD { public: ~TransitionDamageFXSlotD(); private: unsigned char m_unreconstructed_00[0x0c]; };

// The 0x1034 member's destructor body at 0x00252DA0 is already in the ledger as
// TensileFormationUpdateMember::~TensileFormationUpdateMember, so it is spelled
// with that name and layout here rather than claimed again under a new one.
class TensileFormationUpdateMember
{
public:
	~TensileFormationUpdateMember();

private:
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

// Root base: vptr plus two words, destructor inlined to the vptr restore.
class TransitionDamageFXModuleDataBase
{
public:
	virtual ~TransitionDamageFXModuleDataBase() {}

private:
	unsigned char m_unreconstructed_04[8];				///< out to sizeof() == 0x0C
};

class __declspec(novtable) TransitionDamageFXModuleData : public TransitionDamageFXModuleDataBase
{
public:
	virtual ~TransitionDamageFXModuleData();

private:
	FXDamageFXListInfo m_slotsA[0x30];				///< retail this+0x000C
	unsigned char m_unreconstructed_54c[4];
	FXDamageOCLInfo m_slotsB[0x30];				///< retail this+0x0550
	unsigned char m_unreconstructed_a90[4];
	FXDamageParticleSystemInfo m_slotsC[0x30];				///< retail this+0x0A94
	TransitionDamageFXSlotD m_slotsD[4];				///< retail this+0x0FD4
	TransitionDamageFXSlotD m_slotsE[4];				///< retail this+0x1004
	TensileFormationUpdateMember m_tail;				///< retail this+0x1034
};

// ??1TransitionDamageFXModuleData@@UAE@XZ
TransitionDamageFXModuleData::~TransitionDamageFXModuleData()
{
}
