// Open-BFME5 conversions.

class BfmeThingVIM
{
public:
	void *bfmeSetVIM(void *p);
	void bfmeNotifyVIM();
	char m_bfmePad[8];
	int m_bfme08;
	char m_bfmePad0c[8];
	int m_bfme14;
	char m_bfmePad18[0x40];
	void *m_bfme58;
};

void *BfmeThingVIM::bfmeSetVIM(void *p)
{
	void *old = m_bfme58;
	m_bfme58 = p;
	int flag = (p == 0);
	m_bfme08 = flag;
	if (m_bfme14 & flag)
		bfmeNotifyVIM();
	return old;
}
