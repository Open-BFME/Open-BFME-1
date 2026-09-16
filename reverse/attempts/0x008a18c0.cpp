// ?rva008A18C0@Rva008A18C0Holder@@QAEXXZ
// partial score=0.48 date=2026-09-16
// Address-derived Apt node-holder cleanup at retail RVA 0x008A18C0.

class BfmeNode1285
{
public:
	virtual void attach();
	virtual void release();

	unsigned int m_flags04;
	char m_padding08[0x48];
	struct Info
	{
		char m_padding00[0x18];
		int m_field18;
		int m_field1c;
	};
	Info *m_info50;

	void bfmeSetState1285(int state);
};

class BfmeNode1236
{
public:
	virtual void attach();
	virtual void release();

	unsigned int m_flags04;
	char m_padding08[0x48];
	BfmeNode1285::Info *m_info50;

	void bfmeActivate1236();
};

class Rva008A18C0Holder
{
public:
	void rva008A18C0();

private:
	char m_padding00[0x0c];
	BfmeNode1285 **m_nodes0c;
	int m_count10;
};

void Rva008A18C0Holder::rva008A18C0()
{
	int index = 0;
	if (m_count10 > 0)
	{
     do
     {
       if ((m_nodes0c[index]->m_flags04 & 0x3f) == 0x0e &&
           !((unsigned char)(~(m_nodes0c[index]->m_flags04 >> 15)) & 1))
       {
         if (m_nodes0c[index]->m_info50->m_field1c == 0)
           m_nodes0c[index]->bfmeSetState1285(1);
       }
       if ((m_nodes0c[index]->m_flags04 & 0x3f) == 0x0d &&
           !((unsigned char)(~(m_nodes0c[index]->m_flags04 >> 15)) & 1))
       {
         if (m_nodes0c[index]->m_info50->m_field18 == -1)
           reinterpret_cast<BfmeNode1236 *>(m_nodes0c[index])->bfmeActivate1236();
       }

       m_nodes0c[index]->release();
			++index;
		}
		while (index < m_count10);
	}
	m_count10 = 0;
}
