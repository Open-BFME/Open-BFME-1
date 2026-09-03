// cl: /DNDEBUG /MD /EHs-c-

class BfmeSub939G
{
public:
	void bfmeCall939G();
	void *m_bfmeP;
};

class Rva004C5EF0
{
public:
	void handle(int msg);

	BfmeSub939G m_first;
	BfmeSub939G m_second;
};

void Rva004C5EF0::handle(int msg)
{
	if (msg == 2)
	{
		if (m_first.m_bfmeP)
			m_first.bfmeCall939G();
	}
	else if (msg == 3)
	{
		if (m_second.m_bfmeP)
			m_second.bfmeCall939G();
	}
}
