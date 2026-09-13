// cl: /DNDEBUG /MD /GX- /O2 /Ob2

struct Gen0060CBB0Pair
{
	unsigned int first;
	volatile unsigned int second;
};

class Gen0060CBB0
{
public:
	void handle();

private:
	Gen0060CBB0Pair *getPair();
	void processItems();

	char m_head[0x3C];
	Gen0060CBB0Pair *m_begin;
	Gen0060CBB0Pair *volatile m_end;
	Gen0060CBB0Pair *m_capacity;
	unsigned int m_empty;
	char m_gap[0x10];
	Gen0060CBB0Pair m_pair;
	char m_gap2[0x08];
	unsigned int m_state;
};

void Gen0060CBB0::handle()
{
	Gen0060CBB0Pair *pair = getPair();
	m_pair.first = pair->first;
	m_pair.second = pair->second;

	if ((m_end - m_begin) == 0) {
		m_empty = 1;
		m_state = 0;
		return;
	}

	processItems();
}
