// cl: /O2 /MD
class BfmeThingCX
{
public:
	int m_bfmeHead;
	unsigned short m_bfmeRefs;
};

class BfmeHandleCX
{
public:
	BfmeHandleCX(void)
	{
		m_bfmeThing = 0;
	}

	~BfmeHandleCX(void);

	BfmeThingCX *m_bfmeThing;
};

BfmeHandleCX g_bfmeTableDU[8];
