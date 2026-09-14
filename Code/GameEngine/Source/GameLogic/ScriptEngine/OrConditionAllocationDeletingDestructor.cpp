// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for OrConditionAllocation.
// Constructor 0x0034F890 installs dedicated vtable 0x00CE84D8; its slot
// zero routes through ILT 0x0002A1DF to this 30-byte wrapper, whose complete
// destructor route ILT 0x00030959 reaches cleanup body 0x0034FC90.

class OrConditionAllocation
{
protected:
	virtual ~OrConditionAllocation();
private:
	friend void forceOrConditionAllocationDeletingDestructor();
};

void forceOrConditionAllocationDeletingDestructor()
{
	OrConditionAllocation value;
}
