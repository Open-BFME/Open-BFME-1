// Address-derived guarded release at 0x006ECF10.  The held object's destructor
// is the existing 0x0000D33C thunk; its eight-byte vector element type is the
// stride proved by the retail pointer-difference division.

struct Gen006ECF10Item
{
	int first;
	int second;
};

class Gen0000D33C
{
public:
	~Gen0000D33C();
	unsigned int size() const
	{
		return (unsigned int)(m_finish - m_start);
	}

	char m_head[8];
	Gen006ECF10Item *m_start;
	Gen006ECF10Item *m_finish;
	Gen006ECF10Item *m_end;
	int m_state;
};

class Gen006ECF10
{
public:
	void releaseEmpty();

private:
	char m_head[0x184];
	int m_active;
	Gen0000D33C *m_held;
};

void Gen006ECF10::releaseEmpty()
{
	if (m_active)
	{
		Gen0000D33C *held = m_held;
		if (held && held->m_state == 1 && held->size() <= 0)
		{
			delete held;
			m_held = 0;
			m_active = 0;
		}
	}
}
