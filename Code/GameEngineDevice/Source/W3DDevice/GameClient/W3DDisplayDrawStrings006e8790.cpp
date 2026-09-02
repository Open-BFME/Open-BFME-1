// cl: /DNDEBUG /MD /EHsc

class BfmeDrawString006e
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void color006e(int a, unsigned int b);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void place006e(int a, int b, int c, int d);
	virtual void size006e(int *w, int *h);
};

class W3DDisplay
{
public:
	void drawDisplayStrings(void);

private:
	unsigned char m_unmodelled[0x18c];
	BfmeDrawString006e *m_strings[15];
};

// ?drawDisplayStrings@W3DDisplay@@QAEXXZ
void W3DDisplay::drawDisplayStrings(void)
{
	int x = 3;
	BfmeDrawString006e **p = m_strings;
	int n = 15;
	do
	{
		int height;
		int width;
		(*p)->color006e(-1, 0xff000000);
		(*p)->place006e(3, x, 1, 1);
		(*p)->size006e(&width, &height);
		x += height;
		++p;
		--n;
	} while (n);
}
