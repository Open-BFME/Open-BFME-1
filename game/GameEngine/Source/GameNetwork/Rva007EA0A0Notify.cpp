// cl: /O2
// 0x007EA0A0: for each of three service pairs, if the nested object at
// +0x254/+0x288/+0x26C is live, slot2(0, arg) through +0x6A8 then slot5
// on the sibling at +0x250/+0x284/+0x268.

class Rva007EA0A0Inner
{
public:
	virtual void v0();
	virtual void v1();
	virtual void slot2(int a, void *arg);
};

class Rva007EA0A0Nested
{
public:
	char m_pad[0x6A8];
	Rva007EA0A0Inner *m_inner;
};

class Rva007EA0A0Slot
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void slot5();
};

class Rva007EA0A0Owner
{
public:
	void notify(void *arg);

private:
	char m_pad[0x250];
	Rva007EA0A0Slot *m_250;
	Rva007EA0A0Nested *m_254;
	char m_pad258[0x10];
	Rva007EA0A0Slot *m_268;
	Rva007EA0A0Nested *m_26C;
	char m_pad270[0x14];
	Rva007EA0A0Slot *m_284;
	Rva007EA0A0Nested *m_288;
};

void Rva007EA0A0Owner::notify(void *arg)
{
	Rva007EA0A0Nested *n = m_254;
	if (n)
	{
		n->m_inner->slot2(0, arg);
		m_250->slot5();
	}
	n = m_288;
	if (n)
	{
		n->m_inner->slot2(0, arg);
		m_284->slot5();
	}
	n = m_26C;
	if (n)
	{
		n->m_inner->slot2(0, arg);
		m_268->slot5();
	}
}
