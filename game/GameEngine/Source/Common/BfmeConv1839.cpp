void __cdecl bfmeReleaseXC(void *item);

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase(const StringBase &other);
	~StringBase();

	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	static UnicodeString TheEmptyString;

	__forceinline UnicodeString(const UnicodeString &other)
		: StringBase<unsigned short>(other) {}
	__forceinline ~UnicodeString() {}
};

class GameWindow;

void GadgetTextEntrySetText(GameWindow *window, UnicodeString text);

class BfmeWindowField
{
public:
	__forceinline operator GameWindow *() const
	{
		return m_window;
	}

	GameWindow *m_window;
};

class BfmeMgr19E
{
public:
	void bfmeAddAI(void *owner, char *fmt, int argc, char *first, char *second,
		char *third, char *fourth, char *fifth);
};

extern BfmeMgr19E *g_mgr12F19E8;
extern char g_bfmeFmt1057[];

class BfmeNotifyOwnerXC
{
public:
	unsigned char m_bfmeHeadXC[0x250];
	void *m_bfmeSinkXC;
};

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43();
	virtual int winSetFocus(GameWindow *window);
};

extern GameWindowManager *TheWindowManager;

class BfmeStateXC
{
public:
	void bfmeStopXC(void *unused);

	void bfmeNotifyXC(int kind);
	void bfmeApplyXC(void *item, int kind);
	void bfmeFlushXC();
	void bfmeDoneXC();

	unsigned char m_bfmeHeadXC[0x34];
	BfmeNotifyOwnerXC *m_bfmeOwnerXC;
	unsigned char m_bfmePad38XC[8];
	void *m_bfmeFirstXC;
	void *m_bfmeSecondXC;
	unsigned char m_bfmePad48XC[0x18];
	BfmeWindowField m_bfmeWindow60XC;
	unsigned char m_bfmePad64XC[0xc];
	BfmeWindowField m_bfmeWindow70XC;
	unsigned char m_bfmePad74XC[0xc];
	BfmeWindowField m_bfmeWindow80XC;
	unsigned char m_bfmePad84XC[0xc];
	BfmeWindowField m_bfmeWindow90XC;
	unsigned char m_bfmePad94XC[0x10];
	int m_bfmeModeXC;
	int m_bfmeNotifyKindXC;
};

void BfmeStateXC::bfmeNotifyXC(int kind)
{
	m_bfmeNotifyKindXC = kind;
	switch (kind)
	{
	case 0:
	{
		g_mgr12F19E8->bfmeAddAI(m_bfmeOwnerXC->m_bfmeSinkXC, g_bfmeFmt1057, 1,
			(char *)0x011053C8, 0, 0, 0, 0);
		GadgetTextEntrySetText(m_bfmeWindow70XC, UnicodeString::TheEmptyString);
		TheWindowManager->winSetFocus(m_bfmeWindow70XC);
		break;
	}
	case 1:
	{
		g_mgr12F19E8->bfmeAddAI(m_bfmeOwnerXC->m_bfmeSinkXC, g_bfmeFmt1057, 1,
			(char *)0x01106F84, 0, 0, 0, 0);
		GadgetTextEntrySetText(m_bfmeWindow60XC, UnicodeString::TheEmptyString);
		TheWindowManager->winSetFocus(m_bfmeWindow60XC);
		break;
	}
	case 2:
	{
		g_mgr12F19E8->bfmeAddAI(m_bfmeOwnerXC->m_bfmeSinkXC, g_bfmeFmt1057, 1,
			(char *)0x011053E0, 0, 0, 0, 0);
		GadgetTextEntrySetText(m_bfmeWindow90XC, UnicodeString::TheEmptyString);
		TheWindowManager->winSetFocus(m_bfmeWindow90XC);
		break;
	}
	case 3:
	{
		g_mgr12F19E8->bfmeAddAI(m_bfmeOwnerXC->m_bfmeSinkXC, g_bfmeFmt1057, 1,
			(char *)0x01106F74, 0, 0, 0, 0);
		GadgetTextEntrySetText(m_bfmeWindow80XC, UnicodeString::TheEmptyString);
		TheWindowManager->winSetFocus(m_bfmeWindow80XC);
		break;
	}
	}
}

void BfmeStateXC::bfmeStopXC(void *unused)
{
	switch (m_bfmeModeXC)
	{
	case 1:
		bfmeApplyXC(m_bfmeFirstXC, 0);
		break;
	case 2:
		bfmeNotifyXC(0);
		break;
	case 3:
		bfmeNotifyXC(1);
		break;
	}

	bfmeFlushXC();
	bfmeReleaseXC(m_bfmeSecondXC);
	bfmeDoneXC();
}
