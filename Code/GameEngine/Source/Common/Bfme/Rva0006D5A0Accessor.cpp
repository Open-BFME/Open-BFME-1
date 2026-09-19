// cl: /DNDEBUG /MD /EHsc
// The carved body only returns its incoming ECX value. No caller or owner
// proves a semantic class, so the accessor keeps the retail address in its name.

class Rva0006D5A0Accessor
{
public:
	int value() const;
};

int Rva0006D5A0Accessor::value() const
{
	return (int)this;
}
