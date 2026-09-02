// ?d_006f2890@@YAXXZ
// partial score=0.92 date=2026-09-02
// Address-derived reconstruction of the four-byte vector append at 0x006F2890.
// The owner is otherwise unidentified; its vector storage begins at +0x29C.

struct Gen006F2890False
{
};

class Gen006F2890Vector
{
public:
	void insertOverflow(int *position, const int &value,
		const Gen006F2890False &, unsigned int count, bool atEnd);

	void append(const int &value)
	{
		if (m_finish != m_end)
		{
			if (m_finish)
				*m_finish = value;

			++m_finish;
		}
		else
		{
			insertOverflow(m_finish, value,
				reinterpret_cast<const Gen006F2890False &>(value), 1, true);
		}
	}

	int *m_start;
	int *m_finish;
	int *m_end;
};

class Gen006F2890
{
public:
	void append(int value);

private:
	char m_head[0x29C];
	Gen006F2890Vector m_values;
};

void Gen006F2890::append(int value)
{
	m_values.append(value);
}
