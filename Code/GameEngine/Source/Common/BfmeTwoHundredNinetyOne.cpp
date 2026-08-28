// cl: /Od
// A block asked for and, when one comes back, given the caller's word as its
// only content. What the choice yields is never read. Built without
// optimisation; the callee is pinned by address.

void *bfmeAllocQG(int kind, unsigned int bytes);

class BfmeThingQG
{
public:
	void bfmeMakeQG(unsigned int bytes, const int *from);
};

void BfmeThingQG::bfmeMakeQG(unsigned int bytes, const int *from)
{
	int *got = (int *)bfmeAllocQG(4, bytes);

	(got != 0) ? (*got = *from, (void *)got) : (void *)0;
}
