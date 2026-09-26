// cl: /O2 /DNDEBUG /MD

class Rva008A0FF0Value
{
public:
	virtual void slot00();
	virtual void release();
};

class Rva008A0FF0ValueStack
{
public:
	void releaseAll();

private:
	int m_value00;
	int m_value04;
	int m_value08;
	int m_value0C;
	int m_value10;
	int m_count;
	int m_capacity;
	Rva008A0FF0Value **m_values;
};

void Rva008A0FF0ValueStack::releaseAll()
{
	for (int n = m_count; n > 0; --n)
	{
		m_values[m_count - 1]->release();
		--m_count;
	}
}
