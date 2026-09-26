// Clean C++ lift of Rva00413F00::set at retail 0x00413F00 (63 bytes).
// The item fields and child slot are recovered from the retail accesses. The
// caller-provided child vtable slot proves the final set dispatch.

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
	if (!item)
		goto set_seven;
	if (!item->first)
		goto set_seven;
	m_a8 = 6;
	goto after_set;

set_seven:
	m_a8 = 7;

after_set:
	Rva00413F00Child **head = m_150;
	if (*head)
		(*head)->set(s);
}
