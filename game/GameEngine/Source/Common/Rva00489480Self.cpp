// ?get@Rva00489480Owner@@QAEPAXXZ
// Retail 0x00489480 returns its this pointer and ends at the first ret.

class Rva00489480Owner
{
public:
	void *get();
};

void *Rva00489480Owner::get()
{
	return this;
}

// The carved boundary at 0x00489490 contains one ret and no known semantic owner.
void b_00489490(void)
{
}

// The carved boundary at 0x004894B0 contains one ret and no known semantic owner.
void b_004894b0(void)
{
}
