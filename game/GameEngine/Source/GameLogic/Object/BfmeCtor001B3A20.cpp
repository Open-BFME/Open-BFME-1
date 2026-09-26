// cl: /O2 /Ob1 /DNDEBUG /MD
// BFME retail 0x001B3A20: virtual-base constructor shape.

class BfmeCtorFirstBase001B3A20
{
public:
	virtual void slot();
};

class BfmeCtorVirtualBase001B3A20
{
public:
	virtual void slot();
};

class BfmeCtor001B3A20 : public BfmeCtorFirstBase001B3A20,
	public virtual BfmeCtorVirtualBase001B3A20
{
public:
	BfmeCtor001B3A20();
};

BfmeCtor001B3A20::BfmeCtor001B3A20()
{
}
