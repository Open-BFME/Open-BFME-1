// cl: /O2 /DNDEBUG /MD
// Retail 0x00438FA0 returns its receiver unchanged.

struct Rva00438FA0
{
	void *method();
};

void *Rva00438FA0::method()
{
	return this;
}
