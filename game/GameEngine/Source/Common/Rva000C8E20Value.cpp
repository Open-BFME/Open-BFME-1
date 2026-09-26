// cl: /O2 /Ob0

// Retail RVA 0x000C8E20 returns the address four bytes after this object.
// The adjacent Rva000C8E10 getter supports this address-derived value-holder shape.

class Rva000C8E20
{
public:
	void *get() const;
};

void *Rva000C8E20::get() const
{
	return (unsigned char *)this + 4;
}
