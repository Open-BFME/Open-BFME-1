// Open-BFME5: convert the retail batch update at 0x0048E5C0.

struct Rva0048E5C0Clock
{
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual unsigned int getCount() = 0;
};

struct Rva0048E5C0Sink
{
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void apply(void *storage, void *tail, unsigned int count) = 0;
};

extern Rva0048E5C0Clock *g_rva0048E5C0Clock;

class Rva0048E5C0Batch
{
public:
	void update();

	Rva0048E5C0Sink *m_sink;
	void *m_storage;
	unsigned int m_used;
	unsigned char m_gap[4];
	unsigned char m_tail[4];
};

void Rva0048E5C0Batch::update()
{
	unsigned int available = g_rva0048E5C0Clock->getCount();
	if (available < m_used)
		return;

	m_sink->apply(m_storage, m_tail, available - m_used);
}
