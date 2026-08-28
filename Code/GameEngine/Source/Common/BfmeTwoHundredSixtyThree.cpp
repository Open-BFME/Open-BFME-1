// cl: /Od
// Two values passed on along with what the worker below makes of the first,
// built without optimisation. Both callees are pinned by address; nothing here
// names them.

int bfmeMakeOX(void *one);

class BfmeThingPD
{
public:
	void bfmeGoPD(void *one, void *two);

	void bfmeDoPD(void *one, void *two, int three);
};

void BfmeThingPD::bfmeGoPD(void *one, void *two)
{
	bfmeDoPD(one, two, bfmeMakeOX(one));
}
