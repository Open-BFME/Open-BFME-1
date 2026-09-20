// ?rva007e34c0@BfmeB996Range@@QAEDXZ
// partial score=0.24 date=2026-09-20
// Address-derived reconstruction of retail 0x007E34C0 (carved, 221 B).
// The receiver reuses the exact BfmeB996Range layout and checkRange callee
// proven at 0x007E2EB0 (BfmeConv996RangeCheck.cpp): +4 device, +8 kind.
// The device's slot-0x14 virtual (unnamed by any landed body; declared
// here as v5, following that file's v0..v4/cursor placeholder scheme) is
// called with (0,0), (-8,1) and (1,value) argument pairs while m_kind==6.
// No caller resolves a semantic name for this method; the caller is
// still an .asm dump (d_007df1f0.asm).

class BfmeDev996Range
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual int classify(int value, int width);
	virtual void v4();
	virtual void v5(int a, int b);
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual int cursor();
};

class BfmeB996Range
{
public:
	char checkRange(int first, unsigned int *second, char *stop);
	char rva007e34c0();

private:
	char m_pad[4];
	BfmeDev996Range *m_dev;
	int m_kind;
	int m_limit;
};

char BfmeB996Range::rva007e34c0()
{
	char flag1 = 0;
	char success = 0;

	if (m_kind == 6)
	{
		m_dev->v5(0, 0);
		goto loopCheck;
	}
	goto done;

loopBody:
	{
		int probe1;
		unsigned int arg1;
		if (!checkRange((int)&probe1, &arg1, &flag1) || flag1)
			goto done;

		m_dev->v5(-8, 1);
		if (m_kind != 6)
		{
			success = 1;
			goto loopCheck;
		}

		char flag2 = 0;
		int probe2;
		unsigned int arg2;
		if (!checkRange((int)&probe2, &arg2, &flag2) || flag2)
		{
			success = 1;
			goto loopCheck;
		}

		m_dev->v5(-8, 1);
		m_dev->v5(1, arg2);
		success = 1;
	}

loopCheck:
	if (m_kind == 6)
		goto loopBody;

done:
	if (!success)
		return 0;
	if (flag1)
		return 0;
	if (m_kind == 6)
		m_dev->v5(0, 0);
	return 1;
}
