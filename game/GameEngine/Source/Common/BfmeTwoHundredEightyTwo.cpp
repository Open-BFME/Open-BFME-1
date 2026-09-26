// cl: /Od
// A block asked for and, when one comes back, emptied to a bare text. What was
// kept of it is never read again. Built without optimisation; the callee is
// pinned by address.

void *bfmeAllocPV(int kind, unsigned int bytes);

void bfmeMakePV(unsigned int bytes)
{
	void *out;

	char *got = (char *)bfmeAllocPV(1, bytes);

	if (got != 0)
	{
		*got = 0;

		out = got;
	}
	else
	{
		out = 0;
	}
}
