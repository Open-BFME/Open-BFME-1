// cl: /Od
// A place handed on together with a count that starts at nothing, built without
// optimisation. The frame is far larger than the one word this body names, so
// something else stood there in the original; only its size is knowable.

class BfmeThingOS
{
public:
	void bfmeGoOS(void *what);

	void bfmeDoOS(void *what, int *count);
};

void BfmeThingOS::bfmeGoOS(void *what)
{
	unsigned char spare[0x64];

	int got = 0;

	bfmeDoOS(what, &got);
}
