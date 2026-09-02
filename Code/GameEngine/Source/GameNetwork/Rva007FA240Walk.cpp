// cl: /O2
// 0x007FA240: walk 32 records of size 0x1C. Live slots whose value is not
// above the argument call helper(slot, 0x9A) and suppress the +0x18 store;
// otherwise keep the unsigned minimum in +0x18.

class Rva007FA2C0
{
public:
	void walk(unsigned arg);
	void helper(void *slot, int line);

private:
	char m_pad[0x18];
	unsigned m_18;
};

void Rva007FA2C0::walk(unsigned arg)
{
	unsigned best = 0;
	unsigned char ok = 1;
	char *p = (char *)this + 0x3C;
	int n = 0x20;
	do
	{
		if (*(int *)(p - 0x10))
		{
			unsigned v = *(unsigned *)p;
			if (arg >= v)
			{
				helper(p - 0x14, (signed char)0x9A);
				ok = 0;
			}
			else if (best == 0 || best > v)
				best = v;
		}
		p += 0x1C;
	} while (--n);
	if (ok)
		m_18 = best;
}
