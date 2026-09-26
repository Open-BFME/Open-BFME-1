// Open-BFME5: clean reconstruction of the 0x30-byte allocation and initializer
// at retail RVA 0x0078A430.  The original owning type is not recovered, so the
// address-derived view records only the observed fields and table pointer.

struct Gen_0078A430
{
	unsigned int m_vptr;
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	unsigned char m_flag;
	int m_e;
	int m_f;
	int m_g;
	int m_h;
	int m_i;
	int m_j;

	Gen_0078A430(unsigned char flag)
	{
		m_a = -1;
		m_b = 0;
		m_vptr = 0x01126ccc;
		m_c = 0;
		m_d = 0;
		m_flag = flag;
		m_e = 0;
		m_f = 0;
		m_g = 0;
		m_h = 0;
		m_i = 0;
		m_j = 0;
	}
};

Gen_0078A430 *createGen_0078A430(unsigned char flag)
{
	return new Gen_0078A430(flag);
}
