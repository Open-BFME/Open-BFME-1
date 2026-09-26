// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for CommandSetUpgrade.
// Vtable 0x00CCC444 slots name this class (?getClassMemoryPool@CommandSetUpgrade@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x0003E12B to this 30-byte wrapper, whose complete destructor
// route ILT 0x0000433B reaches cleanup body 0x002D40E0.

class CommandSetUpgrade
{
protected:
	virtual ~CommandSetUpgrade();
private:
	friend void forceCommandSetUpgradeDeletingDestructor();
};

void forceCommandSetUpgradeDeletingDestructor()
{
	CommandSetUpgrade value;
}
