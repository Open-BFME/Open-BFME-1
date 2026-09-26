// Retail RVA 0x003373C0 returns its this pointer; no semantic owner is proven.

class Rva003373C0Self
{
public:
	void *getSelf();
};

void *Rva003373C0Self::getSelf()
{
	return this;
}
