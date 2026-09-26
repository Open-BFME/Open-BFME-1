// ??1Rva008A6410HeaderedDeleting@@UAE@XZ
// cl: /DNDEBUG /MD /EHsc
// Retail 0x008A61F0 is the complete destructor paired with the existing
// scalar deleting destructor at 0x008A6410. The class owns two ref-counted
// strings before the common Q4 teardown.

class Q4Sub00C9CC70
{
public:
	~Q4Sub00C9CC70();
};

class Q4Base00D35D68
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	void notify(int a, int b);
	~Q4Base00D35D68() { }
};

extern void (__cdecl **Rva01337A30ReleaseTable)(void *);

struct Rva008A6410RefCount
{
	unsigned short m_count;
};

class Rva008A6410Ref
{
	public:
	~Rva008A6410Ref()
	{
		Rva008A6410RefCount *ref = m_reference;
		--ref->m_count;
		if (ref->m_count == 0)
			Rva01337A30ReleaseTable[1](ref);
	}

	private:
	Rva008A6410RefCount *m_reference;
};

class Rva008A6410Middle : public Q4Base00D35D68
{
public:
	virtual void v3();
	virtual void v4();
	virtual void v5();
	__forceinline virtual ~Rva008A6410Middle()
	{
		notify(0, 0);
		m_flag = 0;
	}

	char m_gap0[8 - 4];
	Q4Sub00C9CC70 m_sub;
	char m_gap1[0x18 - 9];
	int m_flag;
};

class Rva008A6410HeaderedDeleting : public Rva008A6410Middle
{
public:
	virtual ~Rva008A6410HeaderedDeleting();

private:
	char m_gap2[0x20 - 0x1C];
	Rva008A6410Ref m_ref20;
	Rva008A6410Ref m_ref24;
};

Rva008A6410HeaderedDeleting::~Rva008A6410HeaderedDeleting()
{
}
