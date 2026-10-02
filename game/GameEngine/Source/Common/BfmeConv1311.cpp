// Open-BFME5 conversions.

class BfmeBaseTEC
{
public:
	void bfmeTwoTEC();
	void bfmeThreeTEC();
};

class BfmeThingTEC
{
public:
	int bfmeGoTEC();
	void bfmeOneTEC();
};

int BfmeThingTEC::bfmeGoTEC()
{
	bfmeOneTEC();
	BfmeBaseTEC *b = (BfmeBaseTEC *)((char *)this - 0x10);
	b->bfmeTwoTEC();
	b->bfmeThreeTEC();
	return 1;
}
