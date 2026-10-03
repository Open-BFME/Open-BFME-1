// Retail reaches this comparison through the five-byte thunk at ILT 0x00014196,
// which the ledger defines as ?j_00014196@@YAXXZ in game/gen_small/gthunks_021.cpp
// and nothing else defines, so that thunk name is what the call spells. The
// thunk declares no parameters (that is its real signature), so the
// argument-passing shape is restored through a function pointer cast.
void j_00014196();

typedef char (__cdecl *TestQP_t)(void *, void *);

int bfmeEitherQP(void *a, void *b)
{
	if (((TestQP_t)j_00014196)(a, b) || ((TestQP_t)j_00014196)(b, a))
		return 1;

	return 0;
}
