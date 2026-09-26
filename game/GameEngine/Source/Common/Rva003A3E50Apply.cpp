// cl: /O2 /Ob0

class Rva003A3E50Audio
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
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c(int value);
};

extern Rva003A3E50Audio *g_rva003A3E50Audio;

class Rva003A3E50
{
	char m_lead[0x24];
	int m_at24;

public:
	void apply();
};

void Rva003A3E50::apply()
{
	if (g_rva003A3E50Audio)
	{
		int value = m_at24;
		if (value != 1)
			g_rva003A3E50Audio->slot4c(value);
	}
}
