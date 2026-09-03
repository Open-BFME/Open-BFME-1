// cl: /EHsc

class Q4Sub00C9CC70
{
public:
	~Q4Sub00C9CC70();
};

class Q4Base00D35D68
{
public:
	void notify(int a, int b);
};

class Rva008B93A0Root
{
public:
	virtual ~Rva008B93A0Root() {}
};

class Rva008B93A0Item
{
public:
	virtual void invoke();
	virtual void release();
};

extern void (*WideFreePtr)(void *block);

class Rva008B93A0Middle : public Rva008B93A0Root
{
public:
	__forceinline virtual ~Rva008B93A0Middle()
	{
		((Q4Base00D35D68 *)this)->notify(0, 0);
		m_flag = 0;
	}

private:
	char m_gap0[8 - 4];
	Q4Sub00C9CC70 m_sub;
	char m_gap1[0x18 - 9];
	int m_flag;
	char m_gap2[0x20 - 0x1C];
};

class Rva008B9C90HeaderedDeleting : public Rva008B93A0Middle
{
public:
	virtual ~Rva008B9C90HeaderedDeleting();

	Rva008B93A0Item **m_block;
	int m_capacity;
	int m_count;
};

Rva008B9C90HeaderedDeleting::~Rva008B9C90HeaderedDeleting()
{
	Rva008B93A0Item **block = m_block;
	int z = 0;
	int i;
	int tagged;
	m_capacity = z;
	if (block != (Rva008B93A0Item **)z)
	{
		for (i = z; i < m_count; ++i)
		{
			Rva008B93A0Item *item = m_block[i];
			Rva008B93A0Item *ptr = (Rva008B93A0Item *)((unsigned)item & ~1u);
			if (ptr)
			{
				tagged = (unsigned)item & 1u;
				if (!tagged)
					ptr->release();
			}
		}
		WideFreePtr(m_block);
		m_block = (Rva008B93A0Item **)z;
	}
}
