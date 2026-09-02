// cl: /DNDEBUG /MD /EHsc

class Gen0035F050
{
public:
	bool poll(int a, int limit, int c, int d, int e);
	int step(void);

private:
	void *m_unused0;
	int m_value;
};

bool Gen0035F050::poll(int, int limit, int, int, int)
{
	if (m_value > limit)
	{
		do
		{
			if (!step())
				return false;
		} while (m_value > limit);
	}
	return true;
}
