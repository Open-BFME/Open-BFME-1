struct Rva0088A1F0Iface
{
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void call3(void *a1, void *a2, void *a3);
	virtual void call4();
};

struct Rva0088A1F0Node
{
	Rva0088A1F0Node *m_next;
	unsigned char m_pad4[0x10 - 4];
	Rva0088A1F0Iface *m_10;
};

struct Rva0088A1F0Owner
{
	unsigned char m_pad0[0xc];
	Rva0088A1F0Node *m_c;
	unsigned char m_pad10[0x9cf4 - 0x10];
	void *m_9cf4;
	unsigned char m_9cf8[4];

	void broadcast();
};

void Rva0088A1F0Owner::broadcast()
{
	for (Rva0088A1F0Node *n = m_c; n; n = n->m_next)
	{
		Rva0088A1F0Iface *iface = n->m_10;
		if (iface)
		{
			n->m_10->call3(m_9cf4, m_9cf8, 0);
			n->m_10->call4();
		}
	}
}
