// The retail body conditionally frees its receiver without changing fields.
class Rva009A3860Owner
{
public:
	Rva009A3860Owner *destroyAt9A3860(unsigned int flags);
};

Rva009A3860Owner *Rva009A3860Owner::destroyAt9A3860(unsigned int flags)
{
	if (flags & 1)
		::operator delete(this);
	return this;
}
