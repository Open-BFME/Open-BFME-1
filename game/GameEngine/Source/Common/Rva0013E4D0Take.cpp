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

class Rva0013E4D0
{
	char m_pad[0x1C];
	Rva0036CA00Str m_1C;

public:
	bool take(Rva0036CA00Str &dest);
};

bool Rva0013E4D0::take(Rva0036CA00Str &dest)
{
	if (m_1C.m_item && m_1C.m_item->first)
	{
		dest = m_1C;
		return true;
	}
	return false;
}
