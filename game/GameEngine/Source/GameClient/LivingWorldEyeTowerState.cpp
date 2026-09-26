// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// LivingWorldEyeTower state methods share the observed 0x74-byte object layout.
// The two rate/progress pairs have distinct offsets and retain offset names;
// no additional original member spelling is inferred from their arithmetic.

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
int GetGameLogicRandomValue(int low, int high, char *file, int line);
extern float g_bfmeDefaultBU;

class LivingWorldEyeTower
{
public:
	void updateState();

private:
	void beginState();
	void processItems();
	void processFrame();
	Gen0060CBB0Pair *getPair();

	char m_unmodelled00[0x48];
	unsigned int m_state;
	Gen0060CBB0Pair m_to;
	Gen0060CBB0Pair m_from;
	Gen0060CBB0Pair m_current;
	float m_rate64;
	float m_progress68;
	float m_rate6C;
	float m_progress70;
};

void LivingWorldEyeTower::beginState()
{
	m_progress68 += m_rate64;
	if (m_progress68 >= 1.0f)
		m_progress68 = 1.0f;

	g_bfmeStateDF->interpolate(&m_from, &m_to, &m_current, m_progress68);

	if (m_progress68 >= 1.0f)
		processItems();
}

void LivingWorldEyeTower::processItems()
{
	m_from = m_current;

	int frames = (GetGameLogicRandomValue(0, 2,
		"F:\\bfme\\Code\\gameengine\\Source\\GameClient\\LivingWorldEyeTower.cpp",
		366) + 4) * 30;
	m_progress68 = 0.0f;
	m_rate64 = g_bfmeDefaultBU / (float)frames;

	do
	{
		Gen0060CBB0Pair *pair = getPair();
		m_to = *pair;
	} while (m_to.first == m_current.first && m_to.second == m_current.second);

	frames = (GetGameLogicRandomValue(0, 8,
		"F:\\bfme\\Code\\gameengine\\Source\\GameClient\\LivingWorldEyeTower.cpp",
		374) + 4) * 30;
	m_progress70 = 0.0f;
	m_state = 1;
	m_rate6C = g_bfmeDefaultBU / (float)frames;
}

void LivingWorldEyeTower::updateState()
{
	switch (m_state) {
		case 0:
			beginState();
			break;

		case 1:
			m_progress70 += m_rate6C;
			if (m_progress70 >= 1.0f)
				m_state = 0;
			break;
	}

	processFrame();
}
