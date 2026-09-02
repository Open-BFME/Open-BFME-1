// cl: /O2 /Ob0

struct BfmeC39F
{
	int x, y, z;
};

class BfmeHold9F
{
public:
	virtual void go(int);
	int m_04;
	int m_08;
};

class BfmePos9F
{
public:
	const BfmeC39F *bfmePos9F();
};

class BfmeObj9F
{
public:
	void bfmeGo9F(unsigned a0, unsigned char on);
	void bfmeUse9F(const BfmeC39F *);
	char m_00[4];
	BfmePos9F *m_04;
};

void BfmeObj9F::bfmeGo9F(unsigned a0, unsigned char on)
{
	int z = 0;
	BfmePos9F *p = m_04;
	if (p != (BfmePos9F *)z)
		bfmeUse9F(p->bfmePos9F());
	if (on == (unsigned char)z)
		return;
	unsigned k = a0;
	char *s = (char *)this + 0x3C;
	int n = 6;
	do
	{
		if (s[-0x30] != (char)z)
		{
			if (*(int *)(s + 4) == z || *(int *)s == z)
			{
				if (k > *(unsigned *)(s - 0x20))
				{
					switch (*(int *)(s - 0x28))
					{
					case 1:
						{
							BfmeHold9F *h = *(BfmeHold9F **)(s - 0x1C);
							if (h != (BfmeHold9F *)z)
								h->m_08 = 2;
							s[-0x30] = (char)z;
						}
						break;
					}
				}
			}
		}
		{
			BfmeHold9F *h = *(BfmeHold9F **)(s - 0x1C);
			if (h != (BfmeHold9F *)z && h->m_08 == 3)
			{
				h->go(1);
				*(int *)(s - 0x1C) = z;
			}
		}
		s += 0x44;
	} while (--n);
}
