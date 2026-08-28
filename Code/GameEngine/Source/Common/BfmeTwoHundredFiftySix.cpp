// cl: /Od
// A byte handed to the worker below and the record handed back, built without
// optimisation. The frame holds something this body never names.

class BfmeThingOU
{
public:
	BfmeThingOU *bfmeSetOU(unsigned char one);

	void bfmeDoOU(unsigned char one);
};

BfmeThingOU *BfmeThingOU::bfmeSetOU(unsigned char one)
{
	unsigned char spare[0x14];

	bfmeDoOU(one);

	return this;
}
