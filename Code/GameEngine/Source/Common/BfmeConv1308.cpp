// Open-BFME5 conversions.

class BfmeGetterTCA
{
public:
	void *bfmeGetTCA(void *a, void *b);
};

class BfmeSinkTCA
{
public:
	void bfmeUseTCA(void *v);
};

class BfmeHostTCA
{
public:
	void bfmeGoTCA(BfmeGetterTCA *r);
	char m_bfmePad[0x18];
	BfmeSinkTCA *m_bfmeSink;
};

void BfmeHostTCA::bfmeGoTCA(BfmeGetterTCA *r)
{
	m_bfmeSink->bfmeUseTCA(r->bfmeGetTCA((void *)"TID", 0));
}

class BfmeBaseTCB
{
public:
	void bfmeInitTCB();
};

class BfmeSetterTCB
{
public:
	void bfmeSetTCB(void *p, int v);
};

class BfmeThingTCB
{
public:
	void bfmeGoTCB();
};

void BfmeThingTCB::bfmeGoTCB()
{
	((BfmeBaseTCB *)((char *)this - 0x10))->bfmeInitTCB();
	BfmeSetterTCB *s = *(BfmeSetterTCB **)((char *)this - 8);
	s->bfmeSetTCB(*(char **)((char *)this - 0xc) + 0x70, -1);
}
