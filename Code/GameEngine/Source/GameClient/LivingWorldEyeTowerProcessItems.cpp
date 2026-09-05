// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// Open-BFME: ?processItems@Gen0060CBB0@@AAEXXZ, retail 0x0060CAD0, 178B.
// LivingWorldEyeTower.cpp lines 366 and 374.
// g_bfmeDefaultBU at 0x01075334 is the 1.0f used by fdivr (bytes 00 00 80 3F).

int GetGameLogicRandomValue(int low, int high, char *file, int line);

extern float g_bfmeDefaultBU;

struct Gen0060CBB0Pair
{
	float first;
	float second;
};

class Gen0060CBB0
{
private:
	void processItems();
	Gen0060CBB0Pair *getPair();

	char m_head[0x48];
	unsigned int m_state;
	Gen0060CBB0Pair m_to;
	Gen0060CBB0Pair m_from;
	Gen0060CBB0Pair m_current;
	float m_rate;
	float m_progress;
	float m_rate2;
	float m_progress2;
};

void Gen0060CBB0::processItems()
{
	m_from = m_current;

	int frames = (GetGameLogicRandomValue(0, 2,
		"F:\\bfme\\Code\\gameengine\\Source\\GameClient\\LivingWorldEyeTower.cpp",
		366) + 4) * 30;
	m_progress = 0.0f;
	m_rate = g_bfmeDefaultBU / (float)frames;

	do
	{
		Gen0060CBB0Pair *pair = getPair();
		m_to = *pair;
	} while (m_to.first == m_current.first && m_to.second == m_current.second);

	frames = (GetGameLogicRandomValue(0, 8,
		"F:\\bfme\\Code\\gameengine\\Source\\GameClient\\LivingWorldEyeTower.cpp",
		374) + 4) * 30;
	m_progress2 = 0.0f;
	m_state = 1;
	m_rate2 = g_bfmeDefaultBU / (float)frames;
}
