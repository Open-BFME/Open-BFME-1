// cl: /O2 /Ob0

struct BfmeElemFC;

// The per-element callee is retail's ILT thunk at 0x0002B355, defined in the
// ledger as ?j_0002b355@@YAXXZ (game/gen_small/thunks_020.cpp).  Reference
// that name through the project-wide thunk convention and apply the callee's
// __thiscall "void copyFrom(BfmeElemFC *)" shape at the call; the layout stays
// private to this TU.
extern void j_0002b355();

typedef void (BfmeElemFC::*BfmeCopyFromFC)(BfmeElemFC *);

struct BfmeElemFC
{
	char m[0x5C];
};

BfmeElemFC *bfmeCopyFC(BfmeElemFC *first, BfmeElemFC *last, BfmeElemFC *dest)
{
	union
	{
		void (*asThunk)(void);
		BfmeCopyFromFC asCopy;
	} callee;

	callee.asThunk = j_0002b355;

	BfmeElemFC *d = dest;
	while (first != last)
	{
		if (d)
			(d->*callee.asCopy)(first);
		first++;
		d++;
	}
	return d;
}