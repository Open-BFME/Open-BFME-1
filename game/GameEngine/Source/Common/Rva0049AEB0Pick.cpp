// cl: /O2 /Ob0

class Rva0049AEB0
{
	char pad[0x70];
	int m_70;
	int m_74;
	int m_78;

public:
	int pick(int v);
};

int Rva0049AEB0::pick(int v)
{
	if (v == m_70)
	{
		if (m_74 == 3)
			return m_70;
		return m_74;
	}
	if (v == m_74)
	{
		if (m_78 == 3)
			return m_70;
		return m_78;
	}
	if (v == m_78)
		return m_70;
	return v;
}
