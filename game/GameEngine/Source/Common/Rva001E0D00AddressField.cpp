// cl: /DNDEBUG /MD

class Rva001E0D00AddressField
{
public:
	char *get() const;
};

char *Rva001E0D00AddressField::get() const
{
	return (char *)this + 0x34;
}
