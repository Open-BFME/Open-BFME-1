// Open-BFME5 conversions.

// Retail 0x007EB810 is defined once by
// game/GameEngine/Source/Common/GlobalDwordGetters.cpp as
// ?Rva007EB810Get@@YAPAURva007EB810Diag@@XZ, so the call below spells that
// name; the local view of the returned object keeps this TU's own spelling.
struct Rva007EB810Diag
{
public:
	virtual void bfmeSlot0VNC();
	virtual void bfmeSlot1VNC();
	virtual void bfmeSlot2VNC();
	virtual void bfmeAssertVNC(const char *cond, const char *file, int line);
};

Rva007EB810Diag *Rva007EB810Get();

// Retail 0x007E8900 is defined once by game/GameEngine/Source/Common/BfmeConv908.cpp
// as ?bfmeGoRF@BfmeThingRF@@QAEPAXPAX0@Z. BfmeKeyVNC's own spelling belongs to
// the matched row for bfmeFreeVNC, so the callee is reached through the real
// declaring class and the object is cast at the use.
class BfmeThingRF
{
public:
	void *bfmeGoRF(void *a, void *b);
};

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
	void *h = ((BfmeThingRF *)key)->bfmeGoRF("TID", 0);
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
					Rva007EB810Get()->bfmeAssertVNC("mNumProbes >= 0", "\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserdemangler.cpp", 0x147);
			}
			break;
		}
	}
}
