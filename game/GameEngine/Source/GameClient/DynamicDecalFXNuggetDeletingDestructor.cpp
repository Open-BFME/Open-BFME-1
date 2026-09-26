// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DynamicDecalFXNugget.
// Vtable 0x00CF3420 slots name this class (?doFXObj@DynamicDecalFXNugget@@UBEXPBVObject@@0@Z); its slot zero routes
// through ILT 0x00027F52 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0002E3FC reaches cleanup body 0x004293F0.

class DynamicDecalFXNugget
{
protected:
	virtual ~DynamicDecalFXNugget();
private:
	friend void forceDynamicDecalFXNuggetDeletingDestructor();
};

void forceDynamicDecalFXNuggetDeletingDestructor()
{
	DynamicDecalFXNugget value;
}
