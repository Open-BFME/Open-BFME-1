struct BfmeDeadlineClock
{
	char m_bfmeFields[0x3C];
	int m_bfmeFrame;
};

struct BfmeDeadlineSource
{
	char m_bfmeFields[0x74];
	int m_bfmeValue;
};

extern BfmeDeadlineClock *g_bfmeDeadlineClock;

class Gen_0028EEB0
{
public:
	void bfmeSet(unsigned int index, BfmeDeadlineSource *source, int delay);

private:
	char m_bfmeFields[0x24];
	bool m_bfmeActive[12];
	int m_bfmeDeadlines[10];
	int m_bfmeValues[10];
};

// ?bfmeSet@Gen_0028EEB0@@QAEXIPAUBfmeDeadlineSource@@H@Z
void Gen_0028EEB0::bfmeSet(
	unsigned int index,
	BfmeDeadlineSource *source,
	int delay)
{
	m_bfmeActive[index] = true;
	m_bfmeDeadlines[index] = g_bfmeDeadlineClock->m_bfmeFrame + delay;
	m_bfmeValues[index] = source != 0 ? source->m_bfmeValue : 0;
}
