// ?d_0015a280@@YAXXZ
// partial score=0.99 date=2026-09-10
// ?bfmeAddMA@BfmeThingMA@@QAEXPAVBfmeItemMA@@@Z
// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class BfmeThingMA;

class BfmeItemMA
{
public:
	unsigned char m_pad000[0x31C];
	BfmeThingMA *m_owner;
};

class BfmeThingMA
{
public:
	void bfmeAddMA(BfmeItemMA *item);

private:
	unsigned char m_pad000[0x120];
	int m_itemCount;
	BfmeItemMA *m_items[36];
	unsigned char m_pad1B4[4];
	bool m_itemsCurrent;
};

void BfmeThingMA::bfmeAddMA(BfmeItemMA *item)
{
	item->m_owner = 0;
	if (m_itemCount < 36)
	{
		m_items[m_itemCount] = item;
		++m_itemCount;
	}
	m_itemsCurrent = false;
}
