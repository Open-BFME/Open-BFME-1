// cl: /Od
// A block asked for and, when one comes back, emptied to a bare text. What the
// choice yields is never read; it lives in a temporary below the record, which
// is what puts this in the middle slot. Built without optimisation; the callee is
// pinned by address.

void *bfmeAllocQB(int kind, unsigned int bytes);

class BfmeThingQB
{
public:
	void bfmeMakeQB(unsigned int bytes, void *spare);
};

void BfmeThingQB::bfmeMakeQB(unsigned int bytes, void *spare)
{
	char *got = (char *)bfmeAllocQB(1, bytes);

	(got != 0) ? (*got = 0, (void *)got) : (void *)0;
}
