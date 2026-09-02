// cl: /DNDEBUG /MD /GX- /O2 /Ob2

int GetGameLogicRandomValue(int low, int high, char *file, int line);

struct Gen0060CBB0Pair
{
	Gen0060CBB0Pair(float x, float y) : first(x), second(y) {}
	~Gen0060CBB0Pair() {}

	float first;
	float second;
};

class Gen0060CBB0
{
private:
	Gen0060CBB0Pair *getPair();
	char m_head[0x3C];
	Gen0060CBB0Pair *m_begin;
	Gen0060CBB0Pair *m_end;
	Gen0060CBB0Pair *m_capacity;
};

Gen0060CBB0Pair *Gen0060CBB0::getPair()
{
	static Gen0060CBB0Pair defaultPoint(1930.0f, 210.0f);
	unsigned int count = (unsigned int)(m_end - m_begin);

	if (count == 0)
		return &defaultPoint;

	int index = GetGameLogicRandomValue(0, count - 1,
		"F:\\bfme\\Code\\gameengine\\Source\\GameClient\\LivingWorldEyeTower.cpp", 355);
	return &m_begin[index];
}
