// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: BfmeThingME::apply, retail 0x0056ABE0, 233 bytes.  Converts
// this, stops the three gadget pointers at +0x264/+0x268/+0x26C, then if
// +0x270 == 2 enables or disables the Load and Delete APT buttons through
// the same GenActionSink used by S3ActionSinkStringForwarders.cpp.

class BfmeX1065;
class BfmeH1065;
class BfmeUnit1013
{
public:
	void bfmeStop1013(int n);
};

class BfmeObjENK;
void bfmeGoENK(BfmeObjENK *o, char v);

class GameWindow;
void Rva004B7A10SetScrollButtonsHidden(GameWindow *window, bool hide);

class GenActionSink
{
public:
	unsigned char *invokeAtLevel(int level, const char *name, int kind, const char *value,
		int a, int b, int c, int d);
};

extern GenActionSink *TheGenActionSink;

int bfmeAptLevel00465CE0(BfmeH1065 *self);

class BfmeThingME
{
public:
	void apply(void);
	int bfmeTestME(void);

	char m_head[0x264];
	BfmeUnit1013 *m_first;
	BfmeUnit1013 *m_second;
	BfmeUnit1013 *m_third;
	int m_state;
};

void BfmeThingME::apply(void)
{
	int level = bfmeAptLevel00465CE0((BfmeH1065 *)this);
	if (m_first)
	{
		m_first->bfmeStop1013(1);
		bfmeGoENK((BfmeObjENK *)m_first, 1);
	}
	if (m_second)
	{
		m_second->bfmeStop1013(1);
		Rva004B7A10SetScrollButtonsHidden((GameWindow *)m_second, true);
	}
	if (m_third)
		m_third->bfmeStop1013(1);

	if (m_state == 2)
	{
		if (!bfmeTestME())
		{
			TheGenActionSink->invokeAtLevel(level, "disableButton", 1, "Load", 0, 0, 0, 0);
			TheGenActionSink->invokeAtLevel(level, "disableButton", 1, "Delete", 0, 0, 0, 0);
			return;
		}
		TheGenActionSink->invokeAtLevel(level, "enableButton", 1, "Load", 0, 0, 0, 0);
		TheGenActionSink->invokeAtLevel(level, "enableButton", 1, "Delete", 0, 0, 0, 0);
	}
}
