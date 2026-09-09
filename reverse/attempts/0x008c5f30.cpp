// ?bfmePushDB@BfmeStackDB@@QAEXPAVAptValue@@@Z
// partial score=0.85 date=2026-09-09
class AptValue
{
public:
	virtual void bfmeReleaseDB();

	unsigned int m_bfme04DB;
	int m_bfme08DB;
};

extern AptValue *g_bfmeFallbackDB;

class BfmeStackDB
{
public:
	void bfmePushDB(AptValue *value);

	int m_bfme00DB;
	unsigned char m_bfmeHeadDB[4];
	AptValue **m_bfme08DB;
	unsigned char m_bfmeMidDB[0x58 - 0xc];
	AptValue **m_bfme58DB;
	unsigned char m_bfmeMid2DB[4];
	AptValue **m_bfme60DB;
};

void BfmeStackDB::bfmePushDB(AptValue *value)
{
	AptValue *v = value;
	unsigned int flags = value->m_bfme04DB;
	unsigned int tag = flags & 0x3f;

	if (tag == 8 && ((unsigned char)~(unsigned char)(flags >> 15) & 1) == 0)
	{
		v = m_bfme60DB[value->m_bfme08DB];
	}
	else if (tag == 4 && ((unsigned char)~(unsigned char)(flags >> 15) & 1) == 0)
	{
		v = m_bfme58DB[value->m_bfme08DB];

		if (v == 0)
			v = g_bfmeFallbackDB;
	}

	m_bfme08DB[m_bfme00DB] = v;
	m_bfme00DB++;

	if (((unsigned char)(v->m_bfme04DB >> 30) & 1) == 0)
		v->bfmeReleaseDB();
}
