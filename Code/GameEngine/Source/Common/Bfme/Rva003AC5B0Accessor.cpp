// cl: /DNDEBUG /MD /EHsc
// The carved body returns its incoming ECX value. No caller identifies an
// owner, so the class name keeps the retail address visible.

class Rva003AC5B0Accessor
{
public:
	int value() const;
};

int Rva003AC5B0Accessor::value() const
{
	return (int)this;
}
