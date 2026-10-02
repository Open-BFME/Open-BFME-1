struct BfmeKeyAEA
{
	unsigned char m_bfmeHead[4];
	void *m_bfmeId;
};

class BfmeEntryAEA
{
public:
	unsigned char m_bfmeHead[8];
	void *m_bfmeId;
	unsigned char m_bfmeRest[0x74];
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

class BfmeThingAEA
{
public:
	bool bfmeFindAEA(BfmeKeyAEA *key, void *extra);
	unsigned char m_bfmeHead[0x1c];
	BfmeEntryAEA *m_bfmeBase;
	int m_bfmeCount;
};

bool BfmeThingAEA::bfmeFindAEA(BfmeKeyAEA *key, void *extra)
{
	BfmeEntryAEA *at = m_bfmeBase;
	BfmeEntryAEA *end = at + m_bfmeCount;
	void *want = key->m_bfmeId;
	while (at < end)
	{
		if (at->m_bfmeId == want)
			return reinterpret_cast<BfmeE1173 *>(at)->bfmeHit1173(key, extra);
		++at;
	}
	return false;
}
