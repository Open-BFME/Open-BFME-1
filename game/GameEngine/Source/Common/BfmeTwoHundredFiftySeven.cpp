// cl: /Od
// Four values passed straight on together with the address of a byte the callee
// fills in, built without optimisation. The frame holds more than this body
// names; only its size is knowable.

void bfmeDoOV(void *one, void *two, void *three, void *four, unsigned char *five);

void bfmeGoOV(void *one, void *two, void *three, void *four)
{
	int spare[5];

	unsigned char got;

	bfmeDoOV(one, two, three, four, &got);
}
