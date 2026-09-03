// ?d_007e3770@@YAXXZ
// partial score=0.7 date=2026-09-03
// ?scan@BfmeB996@@QAEHHPAH@Z [retail body 0x007E3770]
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

class BfmeDev996
{
public:
	virtual void v0(void);
	virtual void v1(void);
	virtual void v2(void);
	virtual void v3(void);
	virtual void v4(void);
	virtual void set996(int value, int enabled);
	virtual void v6(void);
	virtual void v7(void);
	virtual void v8(void);
	virtual void v9(void);
	virtual void v10(void);
	virtual void v11(void);
	virtual int available(void);
};

class BfmeB996
{
public:
	int scan(int target, int *maximum);
	char bfmeTry996(int first, int second, char *stop);

private:
	char m_pad[4];
	BfmeDev996 *m_dev;
	int m_kind;
};

int BfmeB996::scan(int target, int *maximum)
{
	int count = 0;
	if (m_kind != 6)
		return 0;

	int initial = m_dev->available();
	if (m_kind == 6)
		m_dev->set996(0, 0);

	int second = 0;
	int first = 0;
	char stop = 0;

	for (;;) {
		if (m_kind != 6)
			goto finish;
		if (!bfmeTry996((int)&first, (int)&second, &stop)) {
			if (stop)
				return 0;
			goto finish;
		}
		if (stop)
			return 0;

		if (target != 0 && first == target && *maximum < second)
			*maximum = second;
		if (*maximum < second)
			*maximum = second;
		++count;

		if (m_kind != 6)
			goto finish;
		if (!bfmeTry996((int)&first, (int)&second, &stop))
			continue;
		if (stop)
			continue;

		m_dev->set996(-8, 1);
		m_dev->set996(second, 1);
	}

finish:
	m_dev->set996(initial, 1);
	return count;
}
