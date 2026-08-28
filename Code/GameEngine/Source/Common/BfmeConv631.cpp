class BfmeThingCOF
{
public:
	bool bfmeAskCOF();
	void bfmeRunCOF(void *a, void *b, void *c, void *d);
};

void bfmeGoCOF(BfmeThingCOF *thing, void *a, void *b, void *c, void *d)
{
	if (thing == 0)
		return;
	if (thing->bfmeAskCOF())
		return;
	thing->bfmeRunCOF(a, b, c, d);
}
