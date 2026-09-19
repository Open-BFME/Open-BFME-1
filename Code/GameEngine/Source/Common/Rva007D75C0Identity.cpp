// The anonymous body proves only that it returns its this pointer.
// Its class and semantic role remain unknown, so the type keeps the address.

class Rva007D75C0
{
public:
	Rva007D75C0 *self();
};

Rva007D75C0 *Rva007D75C0::self()
{
	return this;
}
