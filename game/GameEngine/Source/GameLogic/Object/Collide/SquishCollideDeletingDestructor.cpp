// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for SquishCollide.
// Vtable 0x00CAA074 slots name this class (?getClassMemoryPool@SquishCollide@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x0001C067 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0002421C reaches cleanup body 0x00216AF0.

class SquishCollide
{
protected:
	virtual ~SquishCollide();
private:
	friend void forceSquishCollideDeletingDestructor();
};

void forceSquishCollideDeletingDestructor()
{
	SquishCollide value;
}
