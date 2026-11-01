// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AttachedModelFXNugget.
// Vtable 0x00CF3480 slots name this class (?doFXObj@AttachedModelFXNugget@@UBEXPBVObject@@0@Z); its slot zero routes
// through ILT 0x000227D7 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00008823 reaches cleanup body 0x00429B60.

class AttachedModelFXNugget
{
protected:
	virtual ~AttachedModelFXNugget();
private:
	friend void forceAttachedModelFXNuggetDeletingDestructor(const AttachedModelFXNugget &);
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceAttachedModelFXNuggetDeletingDestructor(const AttachedModelFXNugget &that)
{
	AttachedModelFXNugget value(that);
}
