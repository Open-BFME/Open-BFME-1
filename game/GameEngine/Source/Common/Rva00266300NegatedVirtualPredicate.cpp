// Address-derived reconstruction of the 15-byte predicate wrapper at 0x00266300.

class Rva00266300PredicateOwner
{
public:
	virtual void reserved0();
	virtual void reserved1();
	virtual bool test();
};

class Rva00266300NegatedVirtualPredicate
{
public:
	bool evaluate();
};

bool Rva00266300NegatedVirtualPredicate::evaluate()
{
	Rva00266300PredicateOwner *owner = reinterpret_cast<Rva00266300PredicateOwner *>(
		reinterpret_cast<char *>( this ) - 4 );
	return !owner->test();
}
