extern "C" void *bfmeWeaponVftIA[];

class BfmeSrcIA
{
public:
	unsigned char m_bfmeHeadIA[0x78];
	float m_bfme78IA;
	float m_bfme7cIA;
	unsigned char m_bfmeGapIA[0x450];
	int m_bfme4d0IA;
};

class BfmeTemplateIA
{
public:
	unsigned char m_bfmeHeadIA[4];
	BfmeSrcIA *m_bfme04IA;
	int m_bfme08IA;
	int m_bfme0cIA;
	unsigned char m_bfmeGapIA[0x20];
	int m_bfme30IA;
};

class Weapon
{
public:
	Weapon(BfmeTemplateIA *t);

	void *volatile m_bfmeVftIA;
	BfmeSrcIA *m_bfme04IA;
	int m_bfme08IA;
	int m_bfme0cIA;
	int m_bfme10IA;
	int m_bfme14IA;
	int m_bfme18IA;
	int m_bfme1cIA;
	int m_bfme20IA;
	int m_bfme24IA;
	int m_bfme28IA;
	int m_bfme2cIA;
	int m_bfme30IA;
	int m_bfme34IA;
	int m_bfme38IA;
	int m_bfme3cIA;
	volatile int m_bfme40IA;
	volatile int m_bfme44IA;
	volatile int m_bfme48IA;
	char m_bfme4cIA;
	unsigned char m_bfmePadIA[3];
	int m_bfme50IA;
	int m_bfme54IA;
	int m_bfme58IA;
};

Weapon::Weapon(BfmeTemplateIA *t)
{
	m_bfmeVftIA = bfmeWeaponVftIA;
	m_bfme40IA = 0;
	m_bfme44IA = 0;
	m_bfme48IA = 0;
	BfmeTemplateIA *tt = *(BfmeTemplateIA *volatile *)&t;

	m_bfme58IA = 0;
	m_bfme04IA = tt->m_bfme04IA;
	m_bfme08IA = tt->m_bfme08IA;
	m_bfme0cIA = tt->m_bfme0cIA;
	m_bfme10IA = 1;
	m_bfme14IA = 0;
	m_bfme1cIA = 0;
	m_bfme20IA = 0;
	m_bfme24IA = 0;
	m_bfme28IA = 0;
	m_bfme18IA = 0;
	m_bfme50IA = 0;
	m_bfme54IA = 0;
	int full;

	if (m_bfme04IA->m_bfme78IA > -3.14159274f || m_bfme04IA->m_bfme7cIA < 3.14159274f)
		full = 1;
	else
		full = 0;

	m_bfme4cIA = (char)full;
	m_bfme34IA = 0x7fffffff;
	m_bfme38IA = 0;
	m_bfme3cIA = m_bfme04IA->m_bfme4d0IA;
	m_bfme2cIA = 0;
	m_bfme30IA = tt->m_bfme30IA;
}
