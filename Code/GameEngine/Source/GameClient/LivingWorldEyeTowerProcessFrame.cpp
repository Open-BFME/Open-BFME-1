// cl: /DNDEBUG /MD /GX- /O2 /Ob2

struct Gen0060CBB0Pair
{
	unsigned int first;
	volatile unsigned int second;
};

struct Gen0060CBB0Scratch
{
	unsigned int first;
	unsigned int second;
	unsigned int third;
};

class BfmeStateDF
{
public:
	virtual ~BfmeStateDF();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void buildFramePoint(void *source, Gen0060CBB0Scratch *point);
};

extern "C" BfmeStateDF *g_bfmeStateDF;
extern "C" char *g_bfmeStateDO;

class Gen0060CBB0
{
private:
	void processFrame();
	void updatePosition();
	void applyTo(unsigned int target, Gen0060CBB0Pair *point);

	char m_head[0x1C];
	unsigned int m_firstTarget;
	unsigned int m_secondTarget;
	Gen0060CBB0Pair m_framePoint;
	char m_gap[0x30];
	Gen0060CBB0Pair m_targetPoint;
};

void Gen0060CBB0::processFrame()
{
	Gen0060CBB0Scratch scratch;
	g_bfmeStateDF->buildFramePoint(g_bfmeStateDO + 0x20, &scratch);

	m_framePoint.first = m_targetPoint.first;
	m_framePoint.second = m_targetPoint.second;
	updatePosition();
	applyTo(m_firstTarget, &m_framePoint);
	applyTo(m_secondTarget, &m_framePoint);
}
