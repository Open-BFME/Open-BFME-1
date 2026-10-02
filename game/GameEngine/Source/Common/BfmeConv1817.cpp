// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Iinputs/reference/shims/player /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "Common/Player.h"

struct BfmeTripleZP
{
	void *m_bfmeAZP;
	void *m_bfmeBZP;
	void *m_bfmeCZP;
};

class BfmeLocalZP
{
public:
	void *m_bfmeAZP;
	void *m_bfmeBZP;
	void *m_bfmeCZP;
	void *m_bfmeDZP;
	unsigned char m_bfmeTailZP[4];
};

// Retail calls this five-byte ILT before copying the three source pointers.
// The thunk's ledger owner is address-derived; this typed fastcall pointer
// preserves the constructor's this-in-ECX call sequence.
extern "C" void __cdecl __identifier("?j_0000a628@@YAXXZ")();
typedef void (__fastcall *BfmeLocalZPConstructorThunk)(BfmeLocalZP *self);

int __cdecl rva000cbd40(void *first, void *second);

class BfmeTail926C
{
public:
	void *bfmeMakeZP(BfmeTripleZP *source);
};

void *BfmeTail926C::bfmeMakeZP(BfmeTripleZP *source)
{
	BfmeLocalZP local;
	((BfmeLocalZPConstructorThunk)&__identifier(
		"?j_0000a628@@YAXXZ"))(&local);

	local.m_bfmeAZP = source->m_bfmeAZP;
	local.m_bfmeBZP = source->m_bfmeBZP;
	local.m_bfmeCZP = source->m_bfmeCZP;

	// retail calls 0x0002F1CB, Player::iterateObjects (const, 0x0002F1CB is the
	// five-byte void thunk over the matched int body at 0x000CDCF0).
	((const Player *)this)->iterateObjects((ObjectIterateFunc)rva000cbd40, &local);

	return local.m_bfmeDZP;
}
