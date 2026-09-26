// Open-BFME5 conversions.

class BfmeSlot1173
{
public:
	void bfmeStore1173(void *k, int v);
};

class BfmeE1173
{
public:
	bool bfmeHit1173(void *a1, void *a2);
	char m_bfmePad0[4];
	int m_bfme04;
	char m_bfmePad1[0x34];
	char *m_bfme3c;
	int m_bfme40;
	int m_bfme44;
	void *m_bfme48;
};

bool BfmeE1173::bfmeHit1173(void *a1, void *a2)
{
	BfmeSlot1173 *e;
	int i;

	if (a2 != m_bfme48)
		return false;

	i = m_bfme44;

	if (i >= m_bfme40)
		e = 0;
	else
		e = (BfmeSlot1173 *)(m_bfme3c + i * 48);

	m_bfme44 = i + 1;
	e->bfmeStore1173(a1, m_bfme04);

	int c = m_bfme44;
	int d = m_bfme40;

	return c >= d;
}
