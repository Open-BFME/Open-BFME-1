// cl: /O2 /Ob0

struct Rva00918CA0Word
{
	unsigned value;
};

class Rva00918CA0DwordGetter
{
	unsigned char m_prefix[0x108];
	unsigned m_value;
public:
	Rva00918CA0Word get() const;
};
Rva00918CA0Word Rva00918CA0DwordGetter::get() const
{
	Rva00918CA0Word result = { m_value };
	return result;
}
