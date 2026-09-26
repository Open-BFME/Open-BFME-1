// Open-BFME5 conversions.

class BfmeStrVGB
{
public:
	void bfmeCopyVGB(const BfmeStrVGB *s);
	char m_bfmePad[4];
	int m_bfme04;
	int m_bfme08;
};

class BfmeThingVGB
{
public:
	BfmeStrVGB *bfmeGetVGB(BfmeStrVGB *out);
	char m_bfmePad[0x2e8];
	BfmeStrVGB m_bfmeStr;
};

BfmeStrVGB *BfmeThingVGB::bfmeGetVGB(BfmeStrVGB *out)
{
	volatile int m_bfmeDead = 0;
	BfmeStrVGB *s = &m_bfmeStr;
	out->bfmeCopyVGB(s);
	out->m_bfme04 = s->m_bfme04;
	out->m_bfme08 = s->m_bfme08;
	return out;
}
