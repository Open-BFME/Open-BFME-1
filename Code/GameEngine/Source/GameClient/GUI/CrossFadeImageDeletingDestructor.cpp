// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for CrossFadeImage.
// Vtable 0x00D0C878 slots name this class (?draw@CrossFadeImage@@UAEXXZ); its slot zero routes
// through ILT 0x0003F026 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00017D64 reaches cleanup body 0x0059D850.

class CrossFadeImage
{
protected:
	virtual ~CrossFadeImage();
private:
	friend void forceCrossFadeImageDeletingDestructor();
};

void forceCrossFadeImageDeletingDestructor()
{
	CrossFadeImage value;
}
