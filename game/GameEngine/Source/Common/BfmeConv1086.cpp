// Open-BFME5 conversions.

class BfmeD1086
{
public:
	void bfmeClose1086(void);
};

class BfmeQ1086;

class BfmeA1086
{
public:
	void bfmeDrop1086A(int *a);
};

class BfmeB1086
{
public:
	void bfmeDrop1086B(int *a);
};

class BfmeC1086
{
public:
	void bfmeDel1086(BfmeQ1086 *a);
};

// Retail's global at 0x012ED5B8 is `PartitionManager *ThePartitionManager`
// (game/GameEngine/Source/GameLogic/Object/PartitionManager.cpp defines it).
// Declare it under that exact spelling; the narrow call view is cast in.
class PartitionManager;
extern PartitionManager *ThePartitionManager;
class CollisionManager;
extern CollisionManager *TheCollisionManager;

extern BfmeC1086 *g_bfmeC1086;

class BfmeQ1086
{
public:
	void bfmeGo1086A(void);
	char m_bfmePad[0x6c];
	int m_bfme6c;
	int m_bfme70;
	char m_bfmePad1[0x2f4];
	char m_bfme368;
	char m_bfmePad2[0x47];
	BfmeD1086 *m_bfme3b0;
	int m_bfme3b4;
	int m_bfme3b8;
};

void BfmeQ1086::bfmeGo1086A(void)
{
	if (m_bfme3b0)
		m_bfme3b0->bfmeClose1086();
	if (m_bfme3b4)
		((BfmeA1086 *)ThePartitionManager)->bfmeDrop1086A(&m_bfme6c);
	if (m_bfme3b8)
		(*reinterpret_cast<BfmeB1086 **>(&TheCollisionManager))->bfmeDrop1086B(&m_bfme70);
	if (g_bfmeC1086)
		g_bfmeC1086->bfmeDel1086(this);
	m_bfme368 = 0;
}
