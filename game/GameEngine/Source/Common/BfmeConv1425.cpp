// cl: /Od

struct BfmeFlagVMC
{
	char m_bfme00;
};

// Retail reaches the conversion through the five-byte thunk at ILT 0x00018179,
// which the ledger defines as ?j_00018179@@YAXXZ in game/gen_small/thunks_011.cpp
// and nothing else defines, so that thunk name is what the call spells. The
// thunk declares no parameters, so the argument-passing shape is restored
// through a function pointer cast.
void j_00018179();

typedef void (__cdecl *CallVMC_t)(int, int, int);

void bfmeFwdVMC(int a, int b, int c)
{
	BfmeFlagVMC n1 = BfmeFlagVMC();
	BfmeFlagVMC n2 = BfmeFlagVMC();

	((CallVMC_t)j_00018179)(a, b, c);
}
