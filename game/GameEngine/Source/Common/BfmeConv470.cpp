class BfmeSubBIC
{
public:
	int bfmeAskBIC();
};

// The value query reaches the ILT thunk at 0x0002CA61
// (`?j_0002ca61@@YAXXZ`, game/gen_small/thunks_021.cpp) with the sub-object
// as this, so the callee is named by the thunk holding that address.

extern void j_0002ca61();

int __stdcall bfmeGoBIC(BfmeSubBIC *sub)
{
	typedef int (BfmeSubBIC::*Query)();
	union { void (*raw)(); Query query; } call;

	if (sub == 0)
		return -1;
	call.raw = j_0002ca61;
	return (sub->*call.query)();
}
