class BfmeBaseETC
{
public:
	void bfmeAETC(void *a, void *b, void *c);
	void bfmeCETC(void *a, void *b, void *c, void *d);
};

class BfmeHostETC
{
public:
	virtual void bfmeSlot00ETC();
	virtual void bfmeSlot01ETC();
	virtual void bfmeSlot02ETC();
	virtual void bfmeSlot03ETC();
	virtual void bfmeSlot04ETC();
	virtual void bfmeSlot05ETC();
	virtual void bfmeSlot06ETC();
	virtual void *bfmeSlot07ETC(void *a, void *b, void *c, void *d, int zero, void *e);

	void *bfmeRunETC(void *unused, void *a, void *b, void *c, void *d, void *e);
};

void *BfmeHostETC::bfmeRunETC(void *unused, void *a, void *b, void *c, void *d,
	void *e)
{
	if (a == 0 || b == 0 || d == 0)
		return 0;

	BfmeBaseETC *base = (BfmeBaseETC *)((char *)this - 0x20);

	base->bfmeAETC(a, b, c);

	void *result = bfmeSlot07ETC(a, b, c, d, 0, e);

	base->bfmeCETC(a, b, c, d);

	return result;
}
