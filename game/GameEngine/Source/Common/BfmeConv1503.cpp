// Open-BFME5 conversions.

class BfmeLogVNC
{
public:
	virtual void bfmeSlot0VNC();
	virtual void bfmeSlot1VNC();
	virtual void bfmeSlot2VNC();
	virtual void bfmeAssertVNC(const char *cond, const char *file, int line);
};

BfmeLogVNC *bfmeGetLogVNC();

class BfmeKeyVNC
{
public:
	void *bfmeFindVNC(const char *name, int flag);
};

class BfmeSinkVNC
{
public:
	virtual void bfmeDropVNC(int a, void *p);
};

struct BfmeSlotVNC
{
	void *m_bfme00;
	int m_bfme04;
	char m_bfme08;
	char m_bfmePad09[3];
	void *m_bfme0c;
	char m_bfmePad10[0x10];
	int m_bfme20;
};

class BfmeMgrVNC
{
public:
	void bfmeFreeVNC(BfmeKeyVNC *key);
	char m_bfmePad000[0xc];
	BfmeSinkVNC *m_bfme0c;
	char m_bfmePad010[0xc4];
	BfmeSlotVNC m_bfme0d4[8];
	int m_bfme1f4;
};

void BfmeMgrVNC::bfmeFreeVNC(BfmeKeyVNC *key)
{
	void *h = key->bfmeFindVNC("TID", 0);
	int n1;

	for (n1 = 0; n1 < 8; ++n1)
	{
		if (m_bfme0d4[n1].m_bfme00 == h)
		{
			BfmeSlotVNC *s = &m_bfme0d4[n1];

			if (s != 0)
			{
				m_bfme0c->bfmeDropVNC(0, s->m_bfme0c);
				s->m_bfme00 = 0;
				s->m_bfme04 = 0;
				s->m_bfme0c = 0;
				s->m_bfme20 = 0;
				s->m_bfme08 = 0;
				if (--m_bfme1f4 < 0)
					bfmeGetLogVNC()->bfmeAssertVNC("mNumProbes >= 0", "\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserdemangler.cpp", 0x147);
			}
			break;
		}
	}
}
