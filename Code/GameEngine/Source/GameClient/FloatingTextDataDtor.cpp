// cl: /DNDEBUG /DWIN32 /MD /EHsc
// BFME FloatingTextData destructor from the InGameUI floating-text path.

class UnicodeString
{
public:
	~UnicodeString();

private:
	void *m_data;
};

class DisplayString;

class DisplayStringManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual DisplayString *newDisplayString();
	virtual void freeDisplayString(DisplayString *string);
};

extern DisplayStringManager *TheDisplayStringManager;

class FloatingTextData
{
public:
	virtual ~FloatingTextData();

private:
	unsigned int m_color;
	UnicodeString m_text;
	DisplayString *m_dString;
	char m_tail[0x14];
};

FloatingTextData::~FloatingTextData()
{
	if (m_dString)
	{
		TheDisplayStringManager->freeDisplayString(m_dString);
	}
	m_dString = 0;
}
