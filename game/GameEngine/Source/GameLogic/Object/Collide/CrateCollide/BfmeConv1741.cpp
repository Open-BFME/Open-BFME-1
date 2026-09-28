float __cdecl GetGameLogicRandomValueReal(float low, float high, char *file, int line);

extern char g_bfmeFileAO[];

class BfmeDataAO
{
public:
	unsigned char m_bfmeHeadAO[0x5c];
	float m_bfmeChanceAO;
};

class BfmeOwnAO
{
public:
	int bfmeRollAO(void);

	unsigned char m_bfmeHeadAO[4];
	BfmeDataAO *m_bfmeDataAO;
};

int BfmeOwnAO::bfmeRollAO(void)
{
	BfmeDataAO *data = m_bfmeDataAO;

	if (GetGameLogicRandomValueReal(0.0f, 1.0f, g_bfmeFileAO, 0x44) < data->m_bfmeChanceAO)
		return 2;

	return 3;
}
