// cl: /Od
// A block asked for and, when one comes back, given the caller's byte as its
// only content. What was kept of it is never read again. Built without
// optimisation; the callee is pinned by address.

void *bfmeAllocQA(int kind, unsigned int bytes);

void bfmeMakeQA(unsigned int bytes, const char *from)
{
	void *out;

	char *got = (char *)bfmeAllocQA(1, bytes);

	if (got != 0)
	{
		*got = *from;

		out = got;
	}
	else
	{
		out = 0;
	}
}
