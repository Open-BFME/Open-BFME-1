// Open-BFME5 conversions.

void bfmeSetTextureVDA(unsigned n, void *tex);
void bfmeDrawTrianglesVDA(unsigned short a, unsigned short b, unsigned short c, unsigned short d);

class BfmeThingVDA
{
public:
	void bfmeDrawVDA(char skip);
	char m_bfmePad[0x34];
	void *m_bfmeTex;
	char m_bfmePad2[0xbc];
	unsigned short m_bfmef4;
	char m_bfmePad3[2];
	unsigned short m_bfmef8;
	char m_bfmePad4[2];
	unsigned short m_bfmefc;
	char m_bfmePad5[2];
	unsigned short m_bfme100;
	char m_bfmePad6[2];
	char m_bfmeEnabled;
};

void BfmeThingVDA::bfmeDrawVDA(char skip)
{
	if (!m_bfmeEnabled)
		return;
	if (!skip)
		bfmeSetTextureVDA(0, &m_bfmeTex);
	bfmeDrawTrianglesVDA(m_bfmef4, m_bfme100, m_bfmefc, m_bfmef8);
}

void bfmeFreeVDB(void *p);

struct BfmeNodeVDB
{
	char m_bfmePad[0x30];
	BfmeNodeVDB *m_bfmeNext;
};

class BfmeThingVDB
{
public:
	void bfmeClearVDB();
	BfmeNodeVDB *m_bfmeTable[0x493];
	BfmeNodeVDB *m_bfmeExtra;
};

void BfmeThingVDB::bfmeClearVDB()
{
	for (unsigned i = 0; i < 0x493; ++i) {
		BfmeNodeVDB *p = m_bfmeTable[i];
		while (p) {
			BfmeNodeVDB *next = p->m_bfmeNext;
			bfmeFreeVDB(p);
			p = next;
		}
	}
	BfmeNodeVDB *p = m_bfmeExtra;
	while (p) {
		BfmeNodeVDB *next = p->m_bfmeNext;
		bfmeFreeVDB(p);
		p = next;
	}
}
