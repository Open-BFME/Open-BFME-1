// cl: /O2 /Ob0

class Rva00652950
{
	char *cur;
	char *base;
	char *end;
	char **block;

public:
	Rva00652950 &next();
};

Rva00652950 &Rva00652950::next()
{
	cur += 0x210;
	if (cur == end)
	{
		++block;
		base = *block;
		end = base + 0x210;
		cur = base;
	}
	return *this;
}
