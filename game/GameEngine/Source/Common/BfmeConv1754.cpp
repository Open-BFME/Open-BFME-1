// Retail reaches this through the five-byte thunk at ILT 0x0002126F, which the
// ledger defines as ?j_0002126f@@YAXXZ in game/gen_small/thunks_015.cpp and
// nothing else defines, so that thunk name is what the call spells. The thunk
// declares no parameters, so the argument-passing shape is restored through a
// function pointer cast.
void j_0002126f();

typedef void (__cdecl *RunBL_t)(void *, int, void *);

void __cdecl bfmeSendBL(void *first, char second, char third, void *last)
{
	int flags = (second == 0) + 1;

	if (third)
		flags |= 8;
	else
		flags |= 4;

	((RunBL_t)j_0002126f)(first, flags | 0x40, last);
}
