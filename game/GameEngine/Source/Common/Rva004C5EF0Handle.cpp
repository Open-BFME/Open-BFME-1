// cl: /DNDEBUG /MD /EHs-c-

class BfmeA1042N
{
public:
	void bfmeGo1042D();
	void *m_bfmeP;
};

class Rva004C5EF0
{
public:
	void handle(int msg);

	BfmeA1042N m_first;
	BfmeA1042N m_second;
};

void Rva004C5EF0::handle(int msg)
{
	if (msg == 2)
	{
		if (m_first.m_bfmeP)
			m_first.bfmeGo1042D();
	}
	else if (msg == 3)
	{
		if (m_second.m_bfmeP)
			m_second.bfmeGo1042D();
	}
}
