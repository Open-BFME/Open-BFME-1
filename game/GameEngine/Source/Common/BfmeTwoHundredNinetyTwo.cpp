// cl: /Od
// A word moved from one place to another through a third the finder names,
// leaving the source empty. Nothing happens when the finder points back at the
// source. Built without optimisation; the callee is pinned by address.

// The finder retail calls is the chain-walk at 0x0082BBC0, owned by
// Rva0082BC30Empty.cpp as ?rva0082BBC0Find@@YAPAHPAHH@Z; the placeholder
// bfmeFindQH was defined by nothing, so the call had no target at link time.
int *rva0082BBC0Find(int *at, int how);

void bfmeSwapQH(int *at, int *other)
{
	int *found = rva0082BBC0Find(other, 0);

	if (found != other)
	{
		int keep = *at;

		*at = *other;

		*other = 0;

		*found = keep;
	}
}
