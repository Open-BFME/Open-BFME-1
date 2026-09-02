// cl: /DNDEBUG /MD /GX- /O2 /Ob2

struct Gen0060CBB0Pair
{
	float first;
	float second;
};

class BfmeStateDF
{
public:
	void interpolate(Gen0060CBB0Pair *first, Gen0060CBB0Pair *second,
		Gen0060CBB0Pair *third, float progress);
};

extern "C" BfmeStateDF *g_bfmeStateDF;

class Gen0060CBB0
{
private:
	void beginState();
	void processItems();

	char m_head[0x4C];
	Gen0060CBB0Pair m_first;
	Gen0060CBB0Pair m_second;
	Gen0060CBB0Pair m_third;
	float m_rate;
	float m_progress;
};

void Gen0060CBB0::beginState()
{
	m_progress += m_rate;
	if (m_progress >= 1.0f)
		m_progress = 1.0f;

	g_bfmeStateDF->interpolate(&m_second, &m_first, &m_third, m_progress);

	if (m_progress >= 1.0f)
		processItems();
}
