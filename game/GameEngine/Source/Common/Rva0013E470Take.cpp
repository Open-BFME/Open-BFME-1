// cl: /O2 /Ob0

class Rva00630D00UStr
{
public:
	Rva00630D00UStr &operator=(const Rva00630D00UStr &other);

	struct Data
	{
		short a;
		short b;
		unsigned short first;
	};

	Data *m_item;
};

class Rva0013E470
{
	char m_pad[0x14];
	Rva00630D00UStr m_14;

public:
	bool take(Rva00630D00UStr &dest);
};

bool Rva0013E470::take(Rva00630D00UStr &dest)
{
	if (m_14.m_item && m_14.m_item->first)
	{
		dest = m_14;
		return true;
	}
	return false;
}
