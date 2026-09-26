// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: TurretAI scalar-deleting destructor at retail RVA 0x0018D860
// (30 bytes).  The exact TurretAI constructor at 0x0018DED0 installs the
// dedicated primary vtable 0x0109BBF4 (and its secondary 0x0109BBDC); the
// primary slot-zero ILT 0x0003700B reaches this wrapper.  That wrapper calls
// the complete destructor through ILT 0x0003AC3D, whose body is 0x0018D600.
// The complete body preserves both TurretAI vptrs, releases the owned
// AudioEventRTS/member state, and unwinds the pooled Snapshot/notification
// layout before scalar operator delete frees the object.

class TurretAI
{
protected:
	virtual ~TurretAI();
	friend void forceTurretAIDeletingDestructor();
};

void forceTurretAIDeletingDestructor()
{
	TurretAI value;
}
