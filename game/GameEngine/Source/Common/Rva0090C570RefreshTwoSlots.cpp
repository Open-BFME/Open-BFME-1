// ?rva0090c570@Rva0090C570Outer@@QAEXXZ

class Rva0090C570Iface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28();
	virtual void *slot2c();
	virtual void slot30();
	virtual void *slot34();
};

struct Rva0090C570Sub
{
	char m_pad0[0xc];
	Rva0090C570Iface *m_0c;
	void *m_10;
	void *m_14;
	Rva0090C570Iface *m_18;
	void *m_1c;
	void *m_20;
};

class Rva0090C570Outer
{
public:
	char m_pad0[0x14];
	Rva0090C570Sub *m_14;

	void rva0090c570(void);
};

void Rva0090C570Outer::rva0090c570(void)
{
	Rva0090C570Sub *sub = m_14;
	Rva0090C570Iface *a = sub->m_0c;

	if (!a)
		return;

	void *r1 = a->slot2c();
	sub->m_14 = r1;
	a = sub->m_0c;
	void *r2 = a->slot34();
	sub->m_10 = r2;
	sub->m_0c = 0;

	Rva0090C570Iface *b = sub->m_18;
	if (b)
	{
		void *r3 = b->slot2c();
		sub->m_20 = r3;
		b = sub->m_18;
		void *r4 = b->slot34();
		sub->m_18 = 0;
		sub->m_1c = r4;
	}
	else
	{
		sub->m_20 = 0;
		sub->m_1c = 0;
	}
}
