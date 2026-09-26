// Open-BFME5 conversions.

class BfmeSubTEB
{
public:
	void bfmeSetTEB(int a);
};

class BfmeBaseTEB
{
public:
	void bfmeInitTEB();
};

class BfmeThingTEB
{
public:
	virtual void bfmeV0TEB() = 0;
	virtual void bfmeV1TEB() = 0;
	virtual void bfmeV2TEB() = 0;
	virtual void bfmeV3TEB() = 0;
	virtual void bfmeV4TEB() = 0;
	virtual void bfmeV5TEB() = 0;
	virtual void bfmeV6TEB() = 0;
	virtual void bfmeV7TEB() = 0;
	virtual void bfmeDoTEB(int a) = 0;
	void bfmeGoTEB();
};

void BfmeThingTEB::bfmeGoTEB()
{
	(*(BfmeSubTEB **)((char *)this - 8))->bfmeSetTEB(3);
	((BfmeBaseTEB *)((char *)this - 0x10))->bfmeInitTEB();
	bfmeDoTEB(0);
}

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
