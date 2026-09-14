// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for SoundFXNugget.
// Vtable 0x00CF33D8 slots name this class (?doFXPos@SoundFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z and ?doFXObj@SoundFXNugget@@UBEXPBVObject@@0@Z); its slot zero routes
// through ILT 0x0000C5E5 to this 30-byte wrapper, whose complete destructor
// route ILT 0x000020F9 reaches cleanup body 0x00428B50.

class SoundFXNugget
{
protected:
	virtual ~SoundFXNugget();
private:
	friend void forceSoundFXNuggetDeletingDestructor();
};

void forceSoundFXNuggetDeletingDestructor()
{
	SoundFXNugget value;
}
