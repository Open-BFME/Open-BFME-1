// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for LaserFXNugget.
// Vtable 0x00CF3438 slots name this class (?doFXPos@LaserFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z); its slot zero routes
// through ILT 0x00002ED7 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0001BA5E reaches cleanup body 0x004297D0.

class LaserFXNugget
{
protected:
	virtual ~LaserFXNugget();
private:
	friend void forceLaserFXNuggetDeletingDestructor();
};

void forceLaserFXNuggetDeletingDestructor()
{
	LaserFXNugget value;
}
