// cl: /O2 /MD

// Retail 0x006EAC70 returns its this pointer as a 32-bit value. The only
// caller reaches it through ILT 0x0002E181, which proves the return shape but
// does not identify the owning class, so the address stays in the class name.

class Rva006EAC70Owner
{
public:
	unsigned int getAddress() const;
};

unsigned int Rva006EAC70Owner::getAddress() const
{
	return (unsigned int)this;
}
