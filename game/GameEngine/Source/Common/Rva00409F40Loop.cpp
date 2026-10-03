// cl: /O2 /Ob0

struct Coord3D;

class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
};

class BfmeHold9F
{
public:
	virtual void go(int);
	int m_04;
	int m_08;
};

class BfmeObj9F
{
public:
	void bfmeGo9F(unsigned a0, unsigned char on);
	char m_00[4];
	BFMERopeDrawable *m_04;
};

// Retail 0x00409F40 reaches the two out-of-line bodies through the five-byte
// ILT thunks at 0x0004B12D and 0x00046AFB; both tail-jump, so they keep the
// this-call register and the pushed argument of the bodies they stand for.
// 0x0004B12D is the recorded thunk body of
// ?getPosition@BFMERopeDrawable@@QBEPBUCoord3D@@XZ; 0x00046AFB's only definition
// is the void thunk ?j_00046afb@@YAXXZ, which drops the return value, so keep
// the target's call shape while naming the recorded thunk.
void j_00046afb();

union BfmeObj9FUse
{
	void (*function)(void);
	void (BfmeObj9F::*member)(const Coord3D *);
};

void BfmeObj9F::bfmeGo9F(unsigned a0, unsigned char on)
{
	int z = 0;
	BFMERopeDrawable *p = m_04;
	if (p != (BFMERopeDrawable *)z)
	{
		BfmeObj9FUse use;
		use.function = &j_00046afb;
		(this->*use.member)(p->getPosition());
	}
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