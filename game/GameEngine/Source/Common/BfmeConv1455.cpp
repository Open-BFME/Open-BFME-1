// Open-BFME5 conversions.

class BfmePoolVMP
{
public:
	virtual void bfmeSlot0VMP();
	virtual void bfmeSlot1VMP();
	virtual void bfmeSlot2VMP();
	virtual void bfmeFreeVMP(void *p, int f);
};

void *bfmeGo929C(void);
// 0x007F0170 is ledgered as the static ??3Gen007F0170@@SAXPAX@Z operator delete.
extern "C" void __cdecl __identifier("??3Gen007F0170@@SAXPAX@Z")(void *p, unsigned n);
#define bfmeDeleteVMP __identifier("??3Gen007F0170@@SAXPAX@Z")

struct BfmeBufVMP
{
	int m_bfme00;
	int m_bfme04;
	void *m_bfme08;
};

class BfmeCtxVMP
{
public:
	void bfmeResetVMP();
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	BfmeBufVMP *m_bfme18;
};

void BfmeCtxVMP::bfmeResetVMP()
{
	BfmeBufVMP *b = m_bfme18;

	if (b != 0)
	{
		((BfmePoolVMP *)bfmeGo929C())->bfmeFreeVMP(b->m_bfme08, 1);
		b->m_bfme04 = 0;
		b->m_bfme00 = 0;
		b->m_bfme08 = 0;
		bfmeDeleteVMP(b, 0xc);
	}
	m_bfme04 = 0;
	m_bfme00 = 0;
	m_bfme08 = 0;
	m_bfme0c = 0;
	m_bfme10 = 0;
	m_bfme14 = 0;
	m_bfme18 = 0;
}
