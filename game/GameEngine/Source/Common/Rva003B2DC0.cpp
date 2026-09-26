// The carved body at retail RVA 0x003B2DC0 returns its this pointer.

class Rva003B2DC0
{
public:
	void *m();
};

void *Rva003B2DC0::m()
{
	return this;
}
