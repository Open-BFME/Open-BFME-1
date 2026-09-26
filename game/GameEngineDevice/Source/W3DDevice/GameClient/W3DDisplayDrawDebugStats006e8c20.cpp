// cl: /DNDEBUG /MD /EHsc

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BfmeDrawString006e8c20
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
	void drawDebugStats(void);

private:
	unsigned char m_unmodelled[0x1C8];
	BfmeDrawString006e8c20 *m_strings[25];
};

void W3DDisplay::drawDebugStats(void)
{
	int y = 3;
	unsigned int textColor = 0xFFFFFFFFu;
	int slot = -4;
	BfmeDrawString006e8c20 **p = m_strings;
	int n = 25;
	do
	{
		if (*p == 0)
			goto skip;
		switch (slot)
		{
		case 0:
			textColor = 0xFFFF9696u;
			break;
		case 2:
			textColor = 0xFFA0A0FFu;
			break;
		case 1:
			textColor = 0xFF64FF64u;
			break;
		case 4:
			textColor = 0xFFFFFF00u;
			break;
		case 6:
			textColor = 0xE164FF64u;
			break;
		case 7:
			textColor = 0xE1FFFF00u;
			break;
		case 9:
			textColor = 0xE164FF64u;
			break;
		case 10:
			textColor = 0xD7FFFF00u;
			break;
		case 12:
			textColor = 0xE164FF64u;
			break;
		case 13:
			textColor = 0xCDFFFF00u;
			break;
		case 15:
			textColor = 0xE164FF64u;
			break;
		case 16:
			textColor = 0xC3FFFF00u;
			break;
		case 18:
			textColor = 0xE164FF64u;
			break;
		case 19:
			textColor = 0xB9FFFF00u;
			break;
		}
		{
			int height;
			int width;
			_ReadWriteBarrier();
			(*p)->color006e((int)textColor, 0xff000000u);
			(*p)->place006e(3, y, 1, 1);
			(*p)->size006e(&width, &height);
			y += height;
		}
	skip:
		++p;
		++slot;
		--n;
	} while (n);
}
