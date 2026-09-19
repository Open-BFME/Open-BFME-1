// cl: /DNDEBUG /MD /EHsc
// Retail returns its incoming ECX value. The carved body has no owner
// evidence, so the class name keeps the retail address visible.

class Rva0075CF00Accessor
{
public:
	int value() const;
};

int Rva0075CF00Accessor::value() const
{
	return (int)this;
}
