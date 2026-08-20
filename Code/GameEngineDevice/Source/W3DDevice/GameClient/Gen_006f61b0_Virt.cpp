// cl: /DNDEBUG /MD /EHsc

// Retail 0x006F61B0. If m_4, tail-call virtual slot 0x0C with two args; else return 0.

class Gen_006f61b0_Iface
{
public:
	virtual int v0(int, int);
	virtual int v1(int, int);
	virtual int v2(int, int);
	virtual int v3(int, int);
};

class Gen_006f61b0
{
public:
	int call(int a, int b);

private:
	unsigned char m_pad[4];
	Gen_006f61b0_Iface *m_4;
};

// ?call@Gen_006f61b0@@QAEHHH@Z
int Gen_006f61b0::call(int a, int b)
{
	if (m_4)
		return m_4->v3(a, b);
	return 0;
}
