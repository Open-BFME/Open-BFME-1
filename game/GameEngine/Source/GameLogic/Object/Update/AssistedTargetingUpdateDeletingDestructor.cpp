// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AssistedTargetingUpdate.
// Vtable 0x00CBACD4 slots name this class (?getClassMemoryPool@AssistedTargetingUpdate@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x00005957 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00044A21 reaches cleanup body 0x0027FAF0.

class AssistedTargetingUpdate
{
protected:
	virtual ~AssistedTargetingUpdate();
private:
	friend void forceAssistedTargetingUpdateDeletingDestructor();
};

void forceAssistedTargetingUpdateDeletingDestructor()
{
	AssistedTargetingUpdate value;
}
