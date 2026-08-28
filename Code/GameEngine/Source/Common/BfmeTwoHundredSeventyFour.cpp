// cl: /Od
// A count that starts at nothing handed to the worker below, built without
// optimisation. The frame holds more than this body names; only its size is
// knowable. The callee is pinned by address.

class BfmeThingPO
{
public:
	void bfmeGoPO(void);

	void bfmeDoPO(int *count);
};

void BfmeThingPO::bfmeGoPO(void)
{
	unsigned char spare[0x40];

	int got = 0;

	bfmeDoPO(&got);
}
