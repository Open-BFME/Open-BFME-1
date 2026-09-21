// ?method@Rva0076EB50@@QAE?AVBFMERetailAsciiString@@H@Z
// partial score=0.9 date=2026-09-08
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() { m_data = 0; }
	BFMERetailAsciiString(const char *s);
	~BFMERetailAsciiString();

private:
	void *m_data;
};

class Rva0076EB50Item
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual const char *slot2();
};

class Rva0076EB50Entry
{
public:
	Rva0076EB50Item *m_item;
	unsigned char m_padding[0x18];
};

class Rva0076CAF0ConditionalDispatch
{
public:
	void target();
};

extern int g_Va012F8064;

class Rva0076EB50
{
public:
	BFMERetailAsciiString method(int i);

	unsigned char m_padding00[0x90];
	int m_stamp90;
	unsigned char m_padding94[0x3c];
	Rva0076EB50Entry m_entriesD0[3];
};

BFMERetailAsciiString Rva0076EB50::method(int i)
{
	Rva0076CAF0ConditionalDispatch *owner =
		(Rva0076CAF0ConditionalDispatch *)((char *)this - 0xc);

	if (g_Va012F8064 != m_stamp90)
		owner->target();

	if (i < 0)
		return BFMERetailAsciiString();
	if ((unsigned int)i >= 3)
		return BFMERetailAsciiString();
	if (m_entriesD0[i].m_item != 0)
		return BFMERetailAsciiString(m_entriesD0[i].m_item->slot2());

	return BFMERetailAsciiString();
}
