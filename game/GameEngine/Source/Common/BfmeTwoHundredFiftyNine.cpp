// cl: /Od
// Two values passed on along with what the worker below makes of the first,
// built without optimisation.

int bfmeMakeOX(void *one);

class BfmeThingOX
{
public:
	void bfmeGoOX(void *one, void *two);

	void bfmeDoOX(void *one, void *two, int three);
};

void BfmeThingOX::bfmeGoOX(void *one, void *two)
{
	bfmeDoOX(one, two, bfmeMakeOX(one));
}
