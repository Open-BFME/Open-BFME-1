// cl: /DNDEBUG /MD
// ?update@BfmeQuickMatchProgressBody@@QAEXXZ  retail 0x00505410, 127 bytes
//
// Scales a stored count against a global denominator (count * 50 / (n - 1),
// or 25 when n <= 1), adds 50 when the step at +0x224 is zero and otherwise
// (step - 1) times the step scale, then writes the progress bar at +0x274.
// The setters at 0x00505530 and 0x00505550 (S3ValueSetters.cpp) store +0x224
// on the same object.
//
// Retail duplicates the single GadgetProgressBarSetProgress call into both
// arms of the step test; writing it once reproduces that tail. Earlier banks
// wrote two calls with a volatile bar and a barrier, which left the bar in
// ECX instead of retail's EAX.

class GameWindow;

void GadgetProgressBarSetProgress(GameWindow *g, int progress);

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
	GameWindow *m_bar;
};

void BfmeQuickMatchProgressBody::update(void)
{
	int n = g_bfmeQuickMatchProgressDenom;
	int progress;
	if (n > 1)
		progress = (int)((double)m_count * 50.0 / (double)(n - 1));
	else
		progress = 25;

	if (m_step == 0)
		progress += 50;
	else
		progress += (int)((double)(m_step - 1) * g_bfmeQuickMatchStepScale);

	GadgetProgressBarSetProgress(m_bar, progress);
}
