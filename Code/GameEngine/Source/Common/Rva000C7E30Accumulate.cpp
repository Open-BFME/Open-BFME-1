// Address-derived name: real identity not recovered.
class Rva000C7E30Sink
{
public:
	void notify(bool flag);
};

class Rva000C7E30Owner
{
public:
	void accumulate(int amount);

	int m_head;
	int m_total;
	int m_limit;
	Rva000C7E30Sink *m_sink;
};

void Rva000C7E30Owner::accumulate(int amount)
{
	m_total = m_total + amount;

	if (m_sink != 0)
		m_sink->notify(m_total < m_limit);
}
