// cl: /DNDEBUG /MD /EHsc

// Retail 0x006F6220. If m_4, tail-call virtual slot 0x2C; else return -1.

class Gen_006f6220_Iface
{
public:
	virtual int v0(void);
	virtual int v1(void);
	virtual int v2(void);
	virtual int v3(void);
	virtual int v4(void);
	virtual int v5(void);
	virtual int v6(void);
	virtual int v7(void);
	virtual int v8(void);
	virtual int v9(void);
	virtual int v10(void);
	virtual int v11(void);
};

class Gen_006f6220
{
public:
	int call(void);

private:
	unsigned char m_pad[4];
	Gen_006f6220_Iface *m_4;
};

// ?call@Gen_006f6220@@QAEHXZ
int Gen_006f6220::call(void)
{
	if (m_4)
		return m_4->v11();
	return -1;
}
