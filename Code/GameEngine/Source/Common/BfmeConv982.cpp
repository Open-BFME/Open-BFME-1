// Open-BFME5 conversions.

class BfmeZ982;

class BfmeY982
{
public:
	virtual void bfmeVY0982();
	virtual void bfmeVY1982();
	virtual void bfmeVY2982();
	virtual void bfmeVY3982();
	virtual void bfmeVY4982();
	virtual void bfmeVY5982();
	virtual BfmeZ982 *bfmeNext982B();

	BfmeY982 *bfmeConv982B();
};

class BfmeSrc982
{
public:
	virtual void bfmeVS0982();
	virtual void bfmeVS1982();
	virtual void bfmeVS2982();
	virtual void bfmeVS3982();
	virtual void bfmeVS4982();
	virtual void bfmeVS5982();
	virtual void bfmeVS6982();
	virtual void bfmeVS7982();
	virtual void bfmeVS8982();
	virtual void bfmeVS9982();
	virtual void bfmeVS10982();
	virtual void bfmeVS11982();
	virtual void bfmeVS12982();
	virtual void bfmeVS13982();
	virtual void bfmeVS14982();
	virtual void bfmeVS15982();
	virtual void bfmeVS16982();
	virtual void bfmeVS17982();
	virtual void bfmeVS18982();
	virtual void bfmeVS19982();
	virtual void bfmeVS20982();
	virtual void bfmeVS21982();
	virtual void bfmeVS22982();
	virtual void bfmeVS23982();
	virtual void bfmeVS24982();
	virtual void bfmeVS25982();
	virtual BfmeY982 *bfmeGet982B(int a);
};

class BfmeOut982
{
public:
	virtual void bfmeVO0982();
	virtual void bfmeVO1982();
	virtual void bfmeVO2982();
	virtual void bfmeVO3982();
	virtual void bfmeVO4982();
	virtual void bfmeVO5982();
	virtual void bfmeVO6982();
	virtual void bfmeVO7982();
	virtual void bfmeVO8982();
	virtual void bfmeVO9982();
	virtual void bfmeVO10982();
	virtual void bfmeVO11982();
	virtual void bfmeVO12982();
	virtual void bfmeVO13982();
	virtual void bfmeVO14982();
	virtual void bfmeVO15982();
	virtual void bfmeVO16982();
	virtual void bfmeVO17982();
	virtual void bfmeSend982B(BfmeZ982 *z);
};

extern BfmeSrc982 *g_bfmeSrc982;
extern BfmeOut982 *g_bfmeOut982;

void __stdcall bfmeGo982B(int a)
{
	BfmeY982 *y = g_bfmeSrc982->bfmeGet982B(a);

	if (!y)
		return;

	BfmeZ982 *z = y->bfmeConv982B()->bfmeNext982B();

	if (!z)
		return;

	g_bfmeOut982->bfmeSend982B(z);
}

class BfmeT982
{
public:
	void bfmeTouch982C();
};

class BfmeHub982
{
public:
	void bfmeBegin982C();
	void bfmeEnd982C();
};

extern BfmeHub982 *g_bfmeHub982;

void bfmeStep982C(void);

void bfmeGo982C(BfmeT982 *t)
{
	if (!t)
		return;

	bfmeStep982C();

	if (!g_bfmeHub982)
		return;

	g_bfmeHub982->bfmeBegin982C();
	t->bfmeTouch982C();
	g_bfmeHub982->bfmeEnd982C();
}
