// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for FireSpreadUpdate.
// Vtable 0x00CBEBD4 slots name this class (?getClassMemoryPool@FireSpreadUpdate@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x0003F936 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00031AA7 reaches cleanup body 0x00292550.

class FireSpreadUpdate
{
protected:
	virtual ~FireSpreadUpdate();
private:
	friend void forceFireSpreadUpdateDeletingDestructor();
};

void forceFireSpreadUpdateDeletingDestructor()
{
	FireSpreadUpdate value;
}
