// cl: /DNDEBUG /MD
// Retail 0x005C0BF0 returns its receiver unchanged.

class Rva005C0BF0Owner
{
public:
	void *identity();
};

void *Rva005C0BF0Owner::identity()
{
	return this;
}
