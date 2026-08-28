// cl: /Od
// A word moved from one place to another through a third the finder names,
// leaving the source empty. Nothing happens when the finder points back at the
// source. Built without optimisation; the callee is pinned by address.

int *bfmeFindQH(int *at, int how);

void bfmeSwapQH(int *at, int *other)
{
	int *found = bfmeFindQH(other, 0);

	if (found != other)
	{
		int keep = *at;

		*at = *other;

		*other = 0;

		*found = keep;
	}
}
