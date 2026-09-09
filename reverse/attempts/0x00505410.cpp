// ?update@BfmeQuickMatchProgressBody@@QAEXXZ
// partial score=0.98 date=2026-09-09
// ?update@BfmeQuickMatchProgressBody@@QAEXXZ
// partial score=0.93 date=2026-09-02
// cl: /DNDEBUG /MD

// Open-BFME5: retail 0x00505410, 127 bytes. Scales a stored count against a
// global denominator (50 / (n-1), or 25 when n<=1), optionally adds a 12.5
// step, and writes the progress bar at +0x274.

class GameWindow;

void GadgetProgressBarSetProgress(GameWindow *g, int progress);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern int g_bfmeQuickMatchProgressDenom;
extern const double g_bfmeQuickMatchStepScale;

class BfmeQuickMatchProgressBody
{
public:
	void update(void);

	unsigned char _pad21c[0x21C];
	int m_count;
	unsigned char _pad220[4];
	int m_step;
	unsigned char _pad228[0x274 - 0x228];
	GameWindow *volatile m_bar;
};

void BfmeQuickMatchProgressBody::update(void)
{
	int n = g_bfmeQuickMatchProgressDenom;
	register int progress;
	if (n > 1)
		progress = (int)((double)m_count * 50.0 / (double)(n - 1));
	else
		progress = 25;

	if (m_step == 0)
	{
		progress += 50;
		GadgetProgressBarSetProgress(m_bar, progress);
	}
	else
	{
		int shifted = m_step - 1;
		int extra = (int)((double)shifted * g_bfmeQuickMatchStepScale);
		progress += extra;
		_ReadWriteBarrier();
		GadgetProgressBarSetProgress(m_bar, progress);
	}
}
