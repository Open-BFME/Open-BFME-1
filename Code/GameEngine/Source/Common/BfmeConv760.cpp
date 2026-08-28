class BfmeOtherDQE
{
public:
	void bfmeCallDQE(void *what);
};

class BfmeThingDQE
{
public:
	BfmeOtherDQE *bfmeGoDQE(BfmeOtherDQE *other, void *a, void *b, void *c, void *what);
};

BfmeOtherDQE *BfmeThingDQE::bfmeGoDQE(BfmeOtherDQE *other, void *a, void *b, void *c, void *what)
{
	volatile int tmp = 0;
	other->bfmeCallDQE(what);
	return other;
}
