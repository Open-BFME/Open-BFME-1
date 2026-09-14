// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for HeightDieUpdate.
// Vtable 0x00CBF6DC slots name this class (?getClassMemoryPool@HeightDieUpdate@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x0001DB65 to this 30-byte wrapper, whose complete destructor
// route ILT 0x000155F0 reaches cleanup body 0x002954C0.

class HeightDieUpdate
{
protected:
	virtual ~HeightDieUpdate();
private:
	friend void forceHeightDieUpdateDeletingDestructor();
};

void forceHeightDieUpdateDeletingDestructor()
{
	HeightDieUpdate value;
}
