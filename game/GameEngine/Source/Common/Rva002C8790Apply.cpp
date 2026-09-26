// cl: /O2 /Ob0

class Rva002C8790Audio
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

extern Rva002C8790Audio *g_rva002C8790Audio;

class Rva002C8790
{
	char m_lead[0xF4];
	int m_atF4;

public:
	void apply();
};

void Rva002C8790::apply()
{
	g_rva002C8790Audio->slot4c(m_atF4);
}
