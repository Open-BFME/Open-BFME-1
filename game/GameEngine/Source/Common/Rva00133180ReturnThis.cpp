// Retail 0x00133180 returns its receiver; no class evidence names the owner.
class Rva00133180Self
{
public:
	void *returnThis();
};

void *Rva00133180Self::returnThis()
{
	return this;
}
