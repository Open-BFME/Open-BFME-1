class BfmeThingCBB
{
public:
	void bfmeOneCBB(void *what);
	void bfmeTwoCBB(void *what, int value);
	void bfmeThreeCBB(void *what);
	void bfmeGoCBB(void *what);
};

void BfmeThingCBB::bfmeGoCBB(void *what)
{
	bfmeOneCBB(what);
	bfmeTwoCBB(what, 0);
	bfmeThreeCBB(what);
}
