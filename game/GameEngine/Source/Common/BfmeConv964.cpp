// Open-BFME5 conversions.

// ILT 0x000024A5 -> matched 0x0048A200 TransitionGroup::reset.
class TransitionGroup
{
public:
	void reset();
};

class BfmeItem964
{
};

class BfmeClear964
{
public:
	void bfmeClear964();

	char m_bfmePad[0x20];
	BfmeItem964 *m_bfmeA;
	BfmeItem964 *m_bfmeB;
	BfmeItem964 *m_bfmeD;
	BfmeItem964 *m_bfmeC;
	char m_bfmePad2[0x25];
	char m_bfmeDone;
};

void BfmeClear964::bfmeClear964()
{
	if (m_bfmeA) {
		((TransitionGroup *)m_bfmeA)->reset();
		m_bfmeA = 0;
	}
	if (m_bfmeB) {
		((TransitionGroup *)m_bfmeB)->reset();
		m_bfmeB = 0;
	}
	if (m_bfmeC) {
		((TransitionGroup *)m_bfmeC)->reset();
		m_bfmeC = 0;
	}
	if (m_bfmeD) {
		((TransitionGroup *)m_bfmeD)->reset();
		m_bfmeD = 0;
	}
	m_bfmeDone = 0;
}
