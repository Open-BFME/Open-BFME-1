// cl: /O2 /Ob1 /DNDEBUG /MD
// BFME retail 0x001BDE10: virtual-base constructor shape.

class BfmeCtorFirstBase001BDE10
{
public:
	virtual void slot();
};

class BfmeCtorVirtualBase001BDE10
{
public:
	virtual void slot();
};

class BfmeCtor001BDE10 : public BfmeCtorFirstBase001BDE10,
	public virtual BfmeCtorVirtualBase001BDE10
{
public:
	BfmeCtor001BDE10();
};

BfmeCtor001BDE10::BfmeCtor001BDE10()
{
}
