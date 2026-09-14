// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AutoFindHealingUpdate.
// Vtable 0x00CBB3C4 slots name this class (?getClassMemoryPool@AutoFindHealingUpdate@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x00048491 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00015EB5 reaches cleanup body 0x002813E0.

class AutoFindHealingUpdate
{
protected:
	virtual ~AutoFindHealingUpdate();
private:
	friend void forceAutoFindHealingUpdateDeletingDestructor();
};

void forceAutoFindHealingUpdateDeletingDestructor()
{
	AutoFindHealingUpdate value;
}
