struct Gen009F5040Node;

class BfmeThingZU;

struct BfmeReachZU
{
	BfmeThingZU *m_bfmeBack;
};

class BfmeThingZU
{
public:
	void bfmeUnhookZU(void);

	unsigned char m_bfmeHead[8];
	BfmeReachZU *m_bfmeFirstOn;
	BfmeThingZU *m_bfmeFirstBack;
	unsigned char m_bfmeGap[8];
	BfmeReachZU *m_bfmeSecondOn;
	BfmeThingZU *m_bfmeSecondBack;
};

class BfmeThingYQ
{
public:
	virtual void bfmeV0YQ() = 0;
	virtual void bfmeV1YQ() = 0;
	virtual void bfmeV2YQ() = 0;
	virtual void bfmeV3YQ() = 0;
	virtual void bfmeV4YQ() = 0;
	virtual void bfmeClearYQ(int flag) = 0;
	virtual Gen009F5040Node *bfmeTakeYQ() = 0;
};

class Gen009F5040
{
public:
	void remove(Gen009F5040Node *n);
	void bfmeDropYQ(BfmeThingYQ *t);
};

void Gen009F5040::bfmeDropYQ(BfmeThingYQ *t)
{
	if (t == 0)
		return;

	Gen009F5040Node *n = t->bfmeTakeYQ();

	if (n == 0)
		return;

	remove(n);
	t->bfmeClearYQ(0);
	reinterpret_cast<BfmeThingZU *>(n)->bfmeUnhookZU();

	::operator delete(n);
}
