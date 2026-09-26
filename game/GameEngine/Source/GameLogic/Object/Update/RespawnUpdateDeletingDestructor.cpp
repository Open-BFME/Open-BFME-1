// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for RespawnUpdate.
// Vtable 0x00CC1A84 slots name this class (?getModuleNameKey@RespawnUpdate@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x0003138B to this 30-byte wrapper, whose complete destructor
// route ILT 0x000347DE reaches cleanup body 0x002A16F0.

class RespawnUpdate
{
protected:
	virtual ~RespawnUpdate();
private:
	friend void forceRespawnUpdateDeletingDestructor();
};

void forceRespawnUpdateDeletingDestructor()
{
	RespawnUpdate value;
}
