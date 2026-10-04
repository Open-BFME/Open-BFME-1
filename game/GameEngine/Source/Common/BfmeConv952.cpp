// Open-BFME5 conversions.

class BfmeTarget952;

class BfmeHolder952
{
};

class BfmeTarget952
{
public:
	char m_bfmePad[0x38];
	float m_bfmeX;
	float m_bfmeY;
};

class BfmeCheck952
{
public:
	bool bfmeNear952();
	char m_bfmePad[0x1c];
	BfmeHolder952 *m_bfmeHolder;
	char m_bfmePad2[4];
	float m_bfmeX;
	float m_bfmeY;
};

extern void j_0000e570();

typedef BfmeTarget952 *(__fastcall *BfmeGoalThunk952)(BfmeHolder952 *);

bool BfmeCheck952::bfmeNear952()
{
	BfmeTarget952 *t = reinterpret_cast<BfmeGoalThunk952>(
		&j_0000e570)(m_bfmeHolder);
	if (t) {
		float dx = t->m_bfmeX - m_bfmeX;
		float dy = t->m_bfmeY - m_bfmeY;

		if (dx * dx + dy * dy > 2500.0f)
			return true;
	}
	return false;
}
