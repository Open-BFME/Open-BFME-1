// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for TemporarilyDefectUpdate.
// Vtable 0x00CC4DCC slots name this class (?getModuleNameKey@TemporarilyDefectUpdate@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x00038A91 to this 30-byte wrapper, whose complete destructor
// route ILT 0x000356C0 reaches cleanup body 0x002B0A70.

class TemporarilyDefectUpdate
{
protected:
	virtual ~TemporarilyDefectUpdate();
private:
	friend void forceTemporarilyDefectUpdateDeletingDestructor();
};

void forceTemporarilyDefectUpdateDeletingDestructor()
{
	TemporarilyDefectUpdate value;
}
