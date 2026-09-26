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

class Rva008B42F0Root
{
public:
	virtual ~Rva008B42F0Root() {}
};

class Rva008B42F0Item
{
public:
	virtual void invoke();
	virtual void release();
};

class Rva008B42F0Holder
{
public:
	~Rva008B42F0Holder()
	{
		if (m_item)
			m_item->release();
	}

private:
	Rva008B42F0Item *m_item;
};

class Rva008B42F0Middle : public Rva008B42F0Root
{
public:
	__forceinline virtual ~Rva008B42F0Middle()
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

class Rva008B46D0HeaderedDeleting : public Rva008B42F0Middle
{
public:
	virtual ~Rva008B46D0HeaderedDeleting();

private:
	Rva008B42F0Holder m_item;
};

Rva008B46D0HeaderedDeleting::~Rva008B46D0HeaderedDeleting()
{
}
