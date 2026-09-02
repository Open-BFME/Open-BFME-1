// ?d_00725620@@YAXXZ
// partial score=0.9 date=2026-09-02
struct BfmeModeAZC
{
	char m_bfmePad[0xc];
	int m_bfmeFrame;
};

extern BfmeModeAZC *g_bfmeModeAZC;

class BfmeChainR725620
{
public:
	void *bfmeGetFinalOverride(void) const;

	void *m_bfmeVtbl;
	BfmeChainR725620 *m_bfmeNext;
	char m_bfmePad[0x58 - 0x08];
	unsigned char m_bfmeFlag58;
	char m_bfmePad2[3];
	int m_bfme5c;
};

extern BfmeChainR725620 *g_bfmeChainR725620;
extern float g_bfmeK725620;

class BfmeThingR725620
{
public:
	void bfmeUpdateR725620(void);

private:
	void bfmeSiblingR725620(void);
	void bfmeTailR725620(void);

	char m_bfmePad[0x4c];
	int m_bfme4c;
	char m_bfmePad2[0x54 - 0x50];
	float m_bfme54;
	char m_bfmePad3[0x94 - 0x58];
	int m_bfme94;
	int m_bfme98;
};

void BfmeThingR725620::bfmeUpdateR725620(void)
{
	BfmeChainR725620 *ov = g_bfmeChainR725620;

	if (ov && ov->m_bfmeNext)
		ov = (BfmeChainR725620 *)ov->m_bfmeNext->bfmeGetFinalOverride();

	if (!ov->m_bfmeFlag58)
		return;

	if (m_bfme98 != 0)
	{
		int state = m_bfme98;

		if (state == 1 || state == 3)
			--m_bfme4c;

		bfmeSiblingR725620();

		int state94 = m_bfme94;

		if (state94 == 2)
		{
			int frame = g_bfmeModeAZC->m_bfmeFrame;

			if (frame != state94)
			{
				m_bfme98 = 3;

				ov = g_bfmeChainR725620;

				if (ov && ov->m_bfmeNext)
					ov = (BfmeChainR725620 *)ov->m_bfmeNext->bfmeGetFinalOverride();

				m_bfme4c = (int)((g_bfmeK725620 - m_bfme54) * ov->m_bfme5c);
				m_bfme94 = frame;
			}
		}
	}
	else
	{
		int frame = g_bfmeModeAZC->m_bfmeFrame;

		if (frame == 2 && m_bfme94 != 2)
		{
			m_bfme94 = 2;
			bfmeTailR725620();
		}
	}
}
