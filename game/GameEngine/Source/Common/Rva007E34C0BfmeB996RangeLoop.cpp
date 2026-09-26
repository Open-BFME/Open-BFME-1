// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Address-derived reconstruction of retail 0x007E34C0 (carved, 221 B).
// The receiver reuses the BfmeB996Range layout and checkRange callee
// proven at 0x007E2EB0 (BfmeConv996RangeCheck.cpp): +4 device, +8 kind.
// Retail inlines three landed bodies of the same receiver: the kind-6
// slot-0x14 (0,0) call at 0x007E3410, the checked -8 step at 0x007E31D0
// and the checked -8 then +value step at 0x007E3230. The inlined loop
// condition is why MSVC keeps the loop top-tested here. No caller names
// the method; its one caller is still an .asm dump (d_007df1f0.asm).

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

	// Inline copies of the out-of-line bodies landed at 0x007E3410
	// (invokeForMode), 0x007E31D0 (bfmeGo996B) and 0x007E3230
	// (bfmeAdvance996); retail expands all three in place here.
	void invokeForMode()
	{
		if (m_kind == 6)
			m_dev->v5(0, 0);
	}

	char bfmeGo996B(int first, unsigned int *second, char *stop)
	{
		if (m_kind == 6 && checkRange(first, second, stop) && !*stop)
		{
			m_dev->v5(-8, 1);
			return 1;
		}
		return 0;
	}

	void bfmeAdvance996()
	{
		if (m_kind == 6)
		{
			int probe2;
			unsigned int arg2;
			char flag2 = 0;
			if (checkRange((int)&probe2, &arg2, &flag2) && !flag2)
			{
				m_dev->v5(-8, 1);
				m_dev->v5(arg2, 1);
			}
		}
	}

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
	invokeForMode();
	int probe1;
	unsigned int arg1;
	while (bfmeGo996B((int)&probe1, &arg1, &flag1))
	{
		bfmeAdvance996();
		success = 1;
	}
	if (!success || flag1)
		return 0;
	invokeForMode();
	return 1;
}
