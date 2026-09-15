// cl: /DNDEBUG /MD /EHsc
//
// LivingWorldLogic scalar-deleting destructor, retail 0x003C3730 (30 bytes).
// Its constructor at 0x003C2FC0 installs vtable 0x010EDBDC; that table's
// slot-zero ILT 0x000436A3 reaches this wrapper.  The wrapper calls the
// complete destructor through ILT 0x00042BBD (body 0x003C31D0).

class LivingWorldLogic
{
public:
	virtual ~LivingWorldLogic();
};

void forceLivingWorldLogicDeletingDestructor()
{
	LivingWorldLogic value;
}
