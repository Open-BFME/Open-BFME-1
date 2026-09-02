// cl: /O2
// 0x007FA310: scan 32 records of size 0x1C starting at +0x28 for the
// argument pointer, then hand the match (or null) to the helper at 0x007FA170.

class Rva007FA2C0
{
public:
	void scan(void *key);
	void helper(void *slot, int line);

private:
	char m_pad[0x28];
};

void Rva007FA2C0::scan(void *key)
{
	int i;
	char *p;
	char *slot;
	for (i = 0, p = (char *)this + 0x28; i < 0x20; ++i, p += 0x1C)
	{
		if (*(void **)p == key)
		{
			slot = p;
			goto found;
		}
	}
	slot = 0;
found:
	helper(slot, (signed char)0x98);
}
