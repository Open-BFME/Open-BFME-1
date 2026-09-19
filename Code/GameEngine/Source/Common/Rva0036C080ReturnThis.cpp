// Retail 0x0036C080 returns its receiver. No caller proves a semantic owner.

struct Rva0036C080Owner
{
	void *value();
};

void *Rva0036C080Owner::value()
{
	return this;
}
