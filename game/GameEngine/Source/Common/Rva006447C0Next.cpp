// cl: /O2 /Ob0

class Rva006447C0
{
	char *cur;
	char *base;
	char *end;
	char **block;

public:
	Rva006447C0 &next();
};

Rva006447C0 &Rva006447C0::next()
{
	cur += 0x330;
	if (cur == end)
	{
		++block;
		base = *block;
		end = base + 0x330;
		cur = base;
	}
	return *this;
}
