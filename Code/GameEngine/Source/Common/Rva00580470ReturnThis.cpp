// cl: /O2 /DNDEBUG /MD
// Retail 0x00580470 returns its receiver unchanged.

struct Rva00580470
{
	void *method();
};

void *Rva00580470::method()
{
	return this;
}

struct Rva007D36F0
{
	void *method();
};

void *Rva007D36F0::method()
{
	return this;
}
