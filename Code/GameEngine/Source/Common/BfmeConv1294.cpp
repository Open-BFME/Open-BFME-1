// Open-BFME5 conversions.

class BfmeSetterSLA
{
public:
	void bfmeSetSLA(void *p, int v);
};

class BfmeThingSLA
{
public:
	void bfmeOneSLA();
	void bfmeTwoSLA();
};

void BfmeThingSLA::bfmeOneSLA()
{
	BfmeSetterSLA *s = *(BfmeSetterSLA **)((char *)this - 8);
	s->bfmeSetSLA(*(char **)((char *)this - 0xc) + 0x70, 1);
	s->bfmeSetSLA(*(char **)((char *)this - 0xc) + 0x7c, 0);
}

void BfmeThingSLA::bfmeTwoSLA()
{
	BfmeSetterSLA *s = *(BfmeSetterSLA **)((char *)this - 8);
	s->bfmeSetSLA(*(char **)((char *)this - 0xc) + 0x70, 0);
	s->bfmeSetSLA(*(char **)((char *)this - 0xc) + 0x7c, 1);
}
