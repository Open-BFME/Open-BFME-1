// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for OrConditionAllocation.
// Constructor 0x0034F890 installs dedicated vtable 0x00CE84D8; its slot
// zero routes through ILT 0x0002A1DF to this 30-byte wrapper, whose complete
// destructor route ILT 0x00030959 reaches cleanup body 0x0034FC90.

// The scalar-deleting destructor (??_G, matched 30B row) must call the rowed
// complete destructor ??1BfmeDeletingChainOwner (0x0034FC90, defined in
// BfmeDeletingChainCleanup.cpp) rather than an OrConditionAllocation
// complete destructor nothing defines. An explicit empty derived destructor
// inlines into the generated ??_G wrapper, leaving the direct base call.
struct BfmeDeletingChainOwner
{
	virtual ~BfmeDeletingChainOwner();
};

class OrConditionAllocation : public BfmeDeletingChainOwner
{
protected:
	virtual ~OrConditionAllocation();
private:
	friend void forceOrConditionAllocationDeletingDestructor(const OrConditionAllocation &);
};

// ??1OrConditionAllocation@@MAE@XZ present-unmatched
OrConditionAllocation::~OrConditionAllocation()
{
}

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceOrConditionAllocationDeletingDestructor(const OrConditionAllocation &that)
{
	OrConditionAllocation value(that);
}
