// cl: /Od
// A record emptied and then, if the caller asks for it, let go of as well, with
// the record handed back either way. Built without optimisation; both callees
// are pinned by address.

void bfmeFreePP(void *at);

class BfmeThingPP
{
public:
	BfmeThingPP *bfmeDropPP(int how);

	void bfmeClearPP(void);
};

BfmeThingPP *BfmeThingPP::bfmeDropPP(int how)
{
	bfmeClearPP();

	if ((how & 1) != 0)
		bfmeFreePP(this);

	return this;
}
