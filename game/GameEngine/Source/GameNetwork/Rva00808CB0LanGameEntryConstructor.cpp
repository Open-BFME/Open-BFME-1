// ??0Rva00808CB0LanGameEntry@@QAE@H@Z
// Retail RVA 0x008087D0. The matched Rva00803620Sink::apply caller constructs
// this entry, and vtable 0x011296B0 identifies its deleting destructor. The
// base call reaches the 0x007E86B0 constructor through its neutral ABI view.
// cl: /O2 /GX- /GS

class Gen007F0130
{
public:
	static void *operator new(unsigned int size);
};

class Rva007E86B0Base : public Gen007F0130
{
public:
	Rva007E86B0Base();
	virtual ~Rva007E86B0Base();

	int m_field04;
};

class Rva00808CB0LanGameEntry : public Rva007E86B0Base
{
public:
	Rva00808CB0LanGameEntry(int sequence);

	int m_field08;
	int m_field0c;
	int m_sequence;
	int m_field14;
	char m_tail18[8];
};

Rva00808CB0LanGameEntry::Rva00808CB0LanGameEntry(int sequence)
{
	m_field08 = 0;
	m_field0c = 0;
	m_field04 = 0;
	m_sequence = sequence;
	m_field14 = 0;
}
