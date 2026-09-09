class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *s) throw();
	__forceinline ~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();

	char *m_bfmeDataCA;
};

class BfmeThingCA
{
public:
	virtual void bfmeDropCA(int flag);

	void bfmeStopCA(int a) throw();
};

class BfmeNodeCA
{
public:
	unsigned char m_bfmeHeadCA[8];
	BfmeThingCA *m_bfme08CA;
};

struct BfmeIterCA
{
	BfmeNodeCA *m_bfmeNodeCA;
	void *m_bfmeMapCA;
};

class BfmeMapCA
{
public:
	BfmeNodeCA *bfmeFindCA(const BFMERetailAsciiString *k) throw();
	void bfmeEraseCA(BfmeIterCA *it) throw();
};

class BfmeHostCA
{
public:
	void bfmeRemoveCA(const char *name);

	unsigned char m_bfmeHeadCA[0x1a8];
	BfmeThingCA *m_bfme1A8CA;
	unsigned char m_bfmeMidCA[0x224 - 0x1ac];
	BfmeMapCA m_bfme224CA;
};

void BfmeHostCA::bfmeRemoveCA(const char *name)
{
	if (name == 0)
		return;

	BFMERetailAsciiString key(name);

	BfmeMapCA *m = &m_bfme224CA;

	BfmeNodeCA *n = m->bfmeFindCA(&key);

	if (n != 0)
	{
		BfmeThingCA *t = n->m_bfme08CA;

		if (t != 0)
		{
			if (m_bfme1A8CA == t)
			{
				m_bfme1A8CA->bfmeStopCA(0);

				m_bfme1A8CA = 0;
			}

			t->bfmeDropCA(1);
		}

		BfmeIterCA it;

		it.m_bfmeNodeCA = n;
		it.m_bfmeMapCA = m;

		m->bfmeEraseCA(&it);
	}
}
