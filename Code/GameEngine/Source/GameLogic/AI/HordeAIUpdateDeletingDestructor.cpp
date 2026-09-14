// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for HordeAIUpdate.
// Vtable 0x00CC8398 slots name this class (?getModuleNameKey@HordeAIUpdate@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x00011B44 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00033A37 reaches cleanup body 0x002C4190.

class HordeAIUpdate
{
protected:
	virtual ~HordeAIUpdate();
private:
	friend void forceHordeAIUpdateDeletingDestructor();
};

void forceHordeAIUpdateDeletingDestructor()
{
	HordeAIUpdate value;
}
