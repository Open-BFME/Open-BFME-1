// cl: /O2 /EHs-c- /MD
// Retail 0x0013CFF0 returns its receiver unchanged.  The carved body has no
// class, caller, or vtable evidence that supports a more specific identity.

class Rva0013CFF0Owner
{
public:
	void *returnThis();
};

void *Rva0013CFF0Owner::returnThis()
{
	return this;
}
