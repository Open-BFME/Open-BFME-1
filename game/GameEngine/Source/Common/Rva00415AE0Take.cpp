// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

	struct Data
	{
		short a;
		short b;
		unsigned short first;
	};

	Data *m_item;
};

class Rva00415AE0
{
	char m_pad[0x2D8];
	Rva0036CA00Str m_2D8;

public:
	bool take(Rva0036CA00Str &dest);
};

bool Rva00415AE0::take(Rva0036CA00Str &dest)
{
	if (m_2D8.m_item && m_2D8.m_item->first)
	{
		dest = m_2D8;
		return true;
	}
	return false;
}
