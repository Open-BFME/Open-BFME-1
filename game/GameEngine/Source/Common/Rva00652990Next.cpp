// cl: /O2 /Ob0

class Rva00652990
{
	char *cur;
	char *base;
	char *end;
	char **block;

public:
	Rva00652990 &next();
};

Rva00652990 &Rva00652990::next()
{
	cur += 0x1F0;
	if (cur == end)
	{
		++block;
		base = *block;
		end = base + 0x1F0;
		cur = base;
	}
	return *this;
}
