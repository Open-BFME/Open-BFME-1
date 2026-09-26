// cl: /Od
// Two values passed on along with what the worker below makes of the first,
// built without optimisation. Both callees are pinned by address; nothing here
// names them.

int bfmeMakeOX(void *one);

class BfmeThingPB
{
public:
	void bfmeGoPB(void *one, void *two);

	void bfmeDoPB(void *one, void *two, int three);
};

void BfmeThingPB::bfmeGoPB(void *one, void *two)
{
	bfmeDoPB(one, two, bfmeMakeOX(one));
}
