// ?set@Rva00413F00@@QAEXABVRva00413F00Str@@@Z
// partial score=0.94 date=2026-09-02
// cl: /O2 /Ob0

class Rva00413F00Str
{
public:
	struct Data
	{
		short a;
		short b;
		unsigned short first;
	};

	Data *m_item;
};

class Rva00413F00Child
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void set(const Rva00413F00Str &s);
};

class Rva00413F00
{
	char m_pad[0xA8];
	int m_a8;
	char m_pad2[0xA4];
	Rva00413F00Child **m_150;

public:
	void set(const Rva00413F00Str &s);
};

void Rva00413F00::set(const Rva00413F00Str &s)
{
	Rva00413F00Str::Data *item = s.m_item;
	if (!item || !item->first)
		m_a8 = 7;
	else
		m_a8 = 6;
	Rva00413F00Child **head = m_150;
	if (*head)
		(*head)->set(s);
}
