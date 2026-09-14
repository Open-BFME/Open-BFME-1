// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for BoneFXDamage.
// Vtable 0x00CB1FB4 slots name this class (?getClassMemoryPool@BoneFXDamage@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x000473D4 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00008607 reaches cleanup body 0x00250660.

class BoneFXDamage
{
protected:
	virtual ~BoneFXDamage();
private:
	friend void forceBoneFXDamageDeletingDestructor();
};

void forceBoneFXDamageDeletingDestructor()
{
	BoneFXDamage value;
}
