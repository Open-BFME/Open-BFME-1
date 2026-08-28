class BfmeThingBPC
{
public:
	void bfmeSetBPC(int what);
};

void __stdcall bfmeDoBPC(BfmeThingBPC *one, void *two);

void __stdcall bfmeGoBPC(BfmeThingBPC *one, void *two)
{
	bfmeDoBPC(one, two);
	one->bfmeSetBPC(3);
}
