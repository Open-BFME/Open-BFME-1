// cl: /Od
// Four values passed straight on together with the address of a byte the callee
// fills in, built without optimisation. The frame holds more than this body
// names; only its size is knowable.

// Retail 0x0082F1A0 calls 0x0082E680 directly: the matched bfmeFindIfV30
// (BfmeConv1470.cpp), whose four-argument spelling ignores the fifth slot.
char *bfmeFindIfV30(char *first, char *last, int a, int b);
typedef void (*BfmeDoOVFn)(void *one, void *two, void *three, void *four, unsigned char *five);

void bfmeGoOV(void *one, void *two, void *three, void *four)
{
	int spare[5];

	unsigned char got;

	((BfmeDoOVFn)bfmeFindIfV30)(one, two, three, four, &got);
}
