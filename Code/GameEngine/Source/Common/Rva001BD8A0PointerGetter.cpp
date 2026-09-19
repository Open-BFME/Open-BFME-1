// cl: /O2 /MD /EHsc-

// Retail 0x001BD8A0 returns this plus 0x30.  No caller or identity table
// proves a semantic owner, so the class name remains address-derived.
class Rva001BD8A0PointerGetter
{
public:
	void *get() const;

	char fields[0x30];
	char value;
};

void *Rva001BD8A0PointerGetter::get() const
{
	return (void *)&value;
}
