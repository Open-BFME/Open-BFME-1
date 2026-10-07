// cl: /Od
// A four-argument hand-off built without optimisation: the caller's three
// values plus the address of a byte the callee fills in. The frame is eight
// bytes with the byte at the top, so a second word sits below it; what that
// word was is not knowable from these bytes.

// Retail calls 0x0082D2D0 directly: the matched bfmeFindChV28 (BfmeConv1468.cpp),
// whose three-argument spelling ignores the fourth slot.
char *bfmeFindChV28(char *first, char *last, char ch);
typedef void (*BfmeDoORFn)(void *one, void *two, unsigned char three, unsigned char *four);

void bfmeGoOR(void *one, void *two, unsigned char three)
{
	int spare;
	unsigned char got;

	((BfmeDoORFn)bfmeFindChV28)(one, two, three, &got);
}
