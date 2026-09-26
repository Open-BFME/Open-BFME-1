// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Sibling of BfmeTimerGF::bfmeTickGF at 0x006E1620. Same global g_bfmeModeGF
// (VA 0x012F0FE0) and same stop callee. Address-derived method on a same-layout
// ticker: if the global kind is 4 and this copy is not, arm a 0xFF countdown
// that calls the stop helper and clears the copy.

class BfmeModeGF
{
public:
	void bfmeStopGF(int flag);

	unsigned char m_bfmeHeadGF[0xc];
	int m_bfmeKindGF;
};

extern BfmeModeGF *g_bfmeModeGF;

class BfmeTimerAZ
{
public:
	void bfmeTickAZ(void);

	unsigned char m_bfmeHeadAZ[0xc];
	int m_bfmeOtherAZ;
	int m_bfmeStateAZ;
	int m_bfmeCountAZ;
};

// ?bfmeTickAZ@BfmeTimerAZ@@QAEXXZ
void BfmeTimerAZ::bfmeTickAZ(void)
{
	int mode = (*(BfmeModeGF *volatile *)&g_bfmeModeGF)->m_bfmeKindGF;
	int four = 4;
	BfmeTimerAZ *self = this;
	if (mode == four && self->m_bfmeOtherAZ != four)
	{
		self->m_bfmeStateAZ = 1;
		self->m_bfmeOtherAZ = four;
		self->m_bfmeCountAZ = 0xff;
	}

	if (self->m_bfmeStateAZ != 0)
	{
		if (self->m_bfmeStateAZ == 1)
		{
			int remaining = --self->m_bfmeCountAZ;
			if (remaining <= 0)
			{
				self->m_bfmeCountAZ = 0;
				self->m_bfmeStateAZ = 0;

				if (g_bfmeModeGF->m_bfmeKindGF == four)
					g_bfmeModeGF->bfmeStopGF(0);

				self->m_bfmeOtherAZ = 0;
			}
		}
	}
}
