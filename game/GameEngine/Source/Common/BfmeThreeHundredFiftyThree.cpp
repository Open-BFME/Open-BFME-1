extern "C" unsigned char bfmeVftUB[];

void bfmeFreeUB(void *what);

class BfmeThingUB
{
public:
	void bfmeResetUB();
	void *m_bfmeVft;
	unsigned char m_bfmeGap[8];
	void *m_bfmeWhat;
};

void BfmeThingUB::bfmeResetUB()
{
	m_bfmeVft = bfmeVftUB;
	bfmeFreeUB(m_bfmeWhat);
}
