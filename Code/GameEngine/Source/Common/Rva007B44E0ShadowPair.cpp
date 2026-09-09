// cl: /O2 /Ob0
// Retail 0x007B44E0 creates two BfmeB1050 shadow resources and stores them
// at offsets 0x58 and 0x5C. Vtable 0x01128450 and the 0x74 allocation establish
// the child type. BfmeB1159::bfmeGo1159 finishes the owning object.

typedef bool Bool;

extern "C" void *bfmeVft1050B[];

class BfmeB1050
{
public:
	void bfmeBase1050(void);

	void *m_bfmeVfptr;
	char m_bfmePad[0x54];
	int m_bfme58;
	int m_bfme5c;
	float m_bfme60;
	char m_bfme64;
	char m_bfmeTail[0x0C];
};

class BfmeB1050ReleaseInterface
{
public:
	virtual void release(int);
};

class BfmeB1159
{
public:
	Bool initialize(void);
	void bfmeGo1159(void);

private:
	char m_pad[0x58];
	BfmeB1050 *m_first;
	BfmeB1050 *m_second;
};

Bool BfmeB1159::initialize(void)
{
	BfmeB1050 *resource = new BfmeB1050;
	if (resource != 0)
	{
		BfmeB1050 *initialized = resource;
		initialized->bfmeBase1050();
		initialized->m_bfme58 = 0;
		initialized->m_bfme5c = 0;
		initialized->m_bfme60 = 20.0f;
		initialized->m_bfme64 = 0;
		initialized->m_bfmeVfptr = bfmeVft1050B;
	}
	else
	{
		resource = 0;
	}

	m_first = resource;
	if (resource == 0)
	{
		return false;
	}

	resource = new BfmeB1050;
	if (resource != 0)
	{
		BfmeB1050 *initialized = resource;
		initialized->bfmeBase1050();
		initialized->m_bfme58 = 0;
		initialized->m_bfme5c = 0;
		initialized->m_bfme60 = 20.0f;
		initialized->m_bfme64 = 0;
		initialized->m_bfmeVfptr = bfmeVft1050B;
	}
	else
	{
		resource = 0;
	}

	m_second = resource;
	if (resource == 0)
	{
		if (m_first != 0)
		{
			((BfmeB1050ReleaseInterface *)m_first)->release(1);
		}
		m_first = 0;
		return false;
	}

	bfmeGo1159();
	return true;
}
