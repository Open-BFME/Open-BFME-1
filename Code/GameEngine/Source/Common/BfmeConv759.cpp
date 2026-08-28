class BfmeOtherDQD
{
public:
	void bfmeCallDQD(void *what);
};

class BfmeThingDQD
{
public:
	BfmeOtherDQD *bfmeGoDQD(BfmeOtherDQD *other, void *a, void *b, void *c, void *what);
};

BfmeOtherDQD *BfmeThingDQD::bfmeGoDQD(BfmeOtherDQD *other, void *a, void *b, void *c, void *what)
{
	volatile int tmp = 0;
	other->bfmeCallDQD(what);
	return other;
}
