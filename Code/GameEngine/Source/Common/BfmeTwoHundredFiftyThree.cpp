// cl: /Od
// A four-argument hand-off built without optimisation: the caller's three
// values plus the address of a byte the callee fills in. The frame is eight
// bytes with the byte at the top, so a second word sits below it; what that
// word was is not knowable from these bytes.

void bfmeDoOR(void *one, void *two, unsigned char three, unsigned char *four);

void bfmeGoOR(void *one, void *two, unsigned char three)
{
	int spare;
	unsigned char got;

	bfmeDoOR(one, two, three, &got);
}
