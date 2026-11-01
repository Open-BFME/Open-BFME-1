// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for FXListAtBonePosFXNugget.
// Vtable 0x00CF3508 slots name this class (?doFXObj@FXListAtBonePosFXNugget@@UBEXPBVObject@@0@Z); its slot zero routes
// through ILT 0x00007D79 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00009F6B reaches cleanup body 0x00429EF0.

class FXListAtBonePosFXNugget
{
protected:
	virtual ~FXListAtBonePosFXNugget();
private:
	friend void forceFXListAtBonePosFXNuggetDeletingDestructor(const FXListAtBonePosFXNugget &);
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceFXListAtBonePosFXNuggetDeletingDestructor(const FXListAtBonePosFXNugget &that)
{
	FXListAtBonePosFXNugget value(that);
}
