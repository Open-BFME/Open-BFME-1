struct Rva221A50Triple
{
	unsigned long first;
	unsigned long second;
	unsigned long third;
};

class Rva221A50Inner
{
public:
	Rva221A50Triple getTriple(int index) const;
};

Rva221A50Triple Rva221A50Inner::getTriple(int) const
{
	const char *owner = *(const char *const *)((const char *)this - 0x1C);
	return *(const Rva221A50Triple *)(owner + 0x12C);
}
