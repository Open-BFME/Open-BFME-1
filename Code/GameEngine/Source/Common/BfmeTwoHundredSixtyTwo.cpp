// cl: /Od
// Two values passed on along with what the worker below makes of the first,
// built without optimisation. Both callees are pinned by address; nothing here
// names them.

int bfmeMakeOX(void *one);

class BfmeThingPC
{
public:
	void bfmeGoPC(void *one, void *two);

	void bfmeDoPC(void *one, void *two, int three);
};

void BfmeThingPC::bfmeGoPC(void *one, void *two)
{
	bfmeDoPC(one, two, bfmeMakeOX(one));
}
