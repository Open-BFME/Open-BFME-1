// Open-BFME5: clean reconstruction of the cached two-axis scale update at
// retail RVA 0x00784480.  The owning type's original identity is not recovered;
// the address-derived wrapper records the observed layout without inventing it.

extern float g_bfmeDefaultBU; // retail 0x01075334
extern float g_bfmeUint32Scale; // retail 0x01075358 (2^32 conversion fixup)

class BfmeThingIH
{
public:
	int bfmeGetIH(void);
	void *m_bfmeItem;
};

class BfmeThingIJ
{
public:
	int bfmeGetIJ(void);
};

class Gen_00784480
{
public:
	void update(BfmeThingIH &thing);

private:
	unsigned char m_pad[0x15];
	unsigned char m_initialized;
	unsigned char m_gap[2];
	void *m_sub;
	float m_first0;
	float m_second0;
	float m_first1;
	float m_second1;
	float m_first2;
	float m_second2;
};

void Gen_00784480::update(BfmeThingIH &thing)
{
	if (m_initialized)
		return;
	if (thing.m_bfmeItem == 0)
		return;

	unsigned int first = (unsigned int)thing.bfmeGetIH();
	float first_scale = g_bfmeDefaultBU / (float)first;
	unsigned int second = (unsigned int)((BfmeThingIJ *)&thing)->bfmeGetIJ();
	float second_scale = g_bfmeDefaultBU / (float)second;

	m_initialized = 1;
	m_first0 *= first_scale;
	m_first1 *= first_scale;
	m_first2 *= first_scale;
	m_second0 *= second_scale;
	m_second1 *= second_scale;
	m_second2 *= second_scale;
}
