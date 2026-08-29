// Open-BFME5 conversions.

extern void *g_bfme914A;
extern void *g_bfme914B;
extern int g_bfme914Count;
extern void *g_bfme914Ptr;
extern char g_bfme914Obj[];
int bfmeTest914A(void);

int bfmeGo914A(void)
{
	g_bfme914Count = 0;
	if (g_bfme914A && g_bfme914B && bfmeTest914A()) {
		g_bfme914Ptr = g_bfme914Obj;
		return 1;
	}
	return 0;
}

class BfmeSrc914C
{
public:
	int bfmeFind914C(void *k);
};

class BfmeThing914C
{
public:
	BfmeThing914C *bfmeGo914C(void *k);
	BfmeSrc914C *m_bfmeSrc;
	char m_bfmeFlag;
};

BfmeThing914C *BfmeThing914C::bfmeGo914C(void *k)
{
	int ok;
	if (m_bfmeFlag && m_bfmeSrc->bfmeFind914C(k) != -1)
		ok = 1;
	else
		ok = 0;
	m_bfmeFlag = (char)ok;
	return this;
}
