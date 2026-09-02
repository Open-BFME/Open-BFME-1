// cl: /O2
// 0x007EA320 / 0x007EA380: if the second arg is live, store both args and
// tail-call vslot 4 on the object at +0x268/+0x284; otherwise report -203
// through the nested +0x6A8 interface.

class Rva007EA320Inner
{
public:
	virtual void v0();
	virtual void v1();
	virtual void slot2(int a, int *err);
};

class Rva007EA320Nested
{
public:
	char m_pad[0x6A8];
	Rva007EA320Inner *m_inner;
};

class Rva007EA320Slot4
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void slot4(void *buf, int z);
};

class Rva007EA320Owner
{
public:
	void bind(void *a, void *b);

private:
	char m_pad[0x268];
	Rva007EA320Slot4 *m_slot4;
	Rva007EA320Nested *m_nested;
	char m_buf[8];
	void *m_278;
	void *m_27C;
};

class Rva007EA380Owner
{
public:
	void bind(void *a, void *b);

private:
	char m_pad[0x284];
	Rva007EA320Slot4 *m_slot4;
	Rva007EA320Nested *m_nested;
	char m_buf[8];
	void *m_294;
	void *m_298;
};

void Rva007EA320Owner::bind(void *a, void *b)
{
	if (b)
	{
		m_278 = b;
		m_27C = a;
		m_slot4->slot4(m_buf, 0);
	}
	else
	{
		int err = -203;
		m_nested->m_inner->slot2(0, &err);
	}
}

void Rva007EA380Owner::bind(void *a, void *b)
{
	if (b)
	{
		m_294 = b;
		m_298 = a;
		m_slot4->slot4(m_buf, 0);
	}
	else
	{
		int err = -203;
		m_nested->m_inner->slot2(0, &err);
	}
}
