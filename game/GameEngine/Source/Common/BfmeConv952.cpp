// Open-BFME5 conversions.

class BfmeTarget952;

class BfmeHolder952
{
public:
	BfmeTarget952 *bfmeGoal952();
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

extern float g_bfmeLimit952;

bool BfmeCheck952::bfmeNear952()
{
	BfmeTarget952 *t = m_bfmeHolder->bfmeGoal952();
	if (t) {
		float dx = t->m_bfmeX - m_bfmeX;
		float dy = t->m_bfmeY - m_bfmeY;

		if (dx * dx + dy * dy > g_bfmeLimit952)
			return true;
	}
	return false;
}
