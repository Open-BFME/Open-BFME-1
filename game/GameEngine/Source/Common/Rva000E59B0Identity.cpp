// cl: /DNDEBUG /MD
// Retail RVA 0x000E59B0 returns its receiver in EAX.

class Rva000E59B0Identity
{
public:
	void *identity();
};

void *Rva000E59B0Identity::identity()
{
	return this;
}
