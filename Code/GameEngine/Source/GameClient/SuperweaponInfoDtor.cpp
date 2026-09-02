// cl: /DNDEBUG /DWIN32 /MD /EHsc
// BFME SuperweaponInfo destructor from the canonical InGameUI source.

class AsciiString
{
public:
	~AsciiString();

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
	virtual void slot24();
	virtual void freeDisplayString(DisplayString *string);
};

extern DisplayStringManager *TheDisplayStringManager;

class SuperweaponInfo
{
protected:
	virtual ~SuperweaponInfo();

private:
	DisplayString *m_nameDisplayString;
	DisplayString *m_timeDisplayString;
	unsigned int m_color;
	const void *m_powerTemplate;
	AsciiString m_powerName;
	unsigned int m_tail[4];
};

SuperweaponInfo::~SuperweaponInfo()
{
	if (m_nameDisplayString)
		TheDisplayStringManager->freeDisplayString(m_nameDisplayString);
	m_nameDisplayString = 0;

	if (m_timeDisplayString)
		TheDisplayStringManager->freeDisplayString(m_timeDisplayString);
	m_timeDisplayString = 0;
}
