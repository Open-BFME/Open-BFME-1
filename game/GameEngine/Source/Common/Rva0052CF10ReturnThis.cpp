// Retail 0x0052CF10 returns its this pointer. No caller proves a semantic owner.

class Rva0052CF10Owner
{
public:
	void *value();
};

void *Rva0052CF10Owner::value()
{
	return this;
}
