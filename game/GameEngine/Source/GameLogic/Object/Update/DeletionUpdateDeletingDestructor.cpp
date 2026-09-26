// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DeletionUpdate.
// Vtable 0x00CBD69C slots name this class (?getClassMemoryPool@DeletionUpdate@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x00041849 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00021B93 reaches cleanup body 0x0028C490.

class DeletionUpdate
{
protected:
	virtual ~DeletionUpdate();
private:
	friend void forceDeletionUpdateDeletingDestructor();
};

void forceDeletionUpdateDeletingDestructor()
{
	DeletionUpdate value;
}
