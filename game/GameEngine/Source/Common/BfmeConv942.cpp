// Open-BFME5 conversions.

struct BfmeObj926C;

class BfmeKey926C
{
public:
	BfmeObj926C *bfmeFind926C();
};

class BfmeSub942D
{
public:
	void *bfmeCall942D(void *a);
};

class BfmeThing942D
{
public:
	virtual void bfmeSlot942D00();
	virtual void bfmeSlot942D01();
	virtual void bfmeSlot942D02();
	virtual void bfmeSlot942D03();
	virtual void bfmeSlot942D04();
	virtual void bfmeSlot942D05();
	virtual void bfmeSlot942D06();
	virtual void bfmeSlot942D07();
	virtual void bfmeSlot942D08();
	virtual void bfmeVirt942D(void *r);
	void bfmeGo942D(void *a);
};

void BfmeThing942D::bfmeGo942D(void *a)
{
	BfmeKey926C *k = *(BfmeKey926C **)((char *)this - 0x18);
	if (!k->bfmeFind926C())
		return;
	BfmeObj926C *o = (*(BfmeKey926C **)((char *)this - 0x18))->bfmeFind926C();
	bfmeVirt942D(((BfmeSub942D *)((char *)o + 0x684))->bfmeCall942D(a));
}
