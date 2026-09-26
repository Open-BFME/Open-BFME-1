// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DetachableRiderUpdate.
// Vtable 0x00CBDC8C slots name this class (?getModuleNameKey@DetachableRiderUpdate@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x0002B7DD to this 30-byte wrapper, whose complete destructor
// route ILT 0x00029672 reaches cleanup body 0x0028D3A0.

class DetachableRiderUpdate
{
protected:
	virtual ~DetachableRiderUpdate();
private:
	friend void forceDetachableRiderUpdateDeletingDestructor();
};

void forceDetachableRiderUpdateDeletingDestructor()
{
	DetachableRiderUpdate value;
}
