// cl: /DNDEBUG /MD /EHsc /DWIN32

// Retail 0x005D2CD0 is the empty reset slot in LocomotorStore's vtable
// 0x01110104. Slot 4 and the adjacent init and update slots identify the
// method as LocomotorStore::reset. The decorated name is already claimed by
// the distinct cleanup body at 0x001B7160, so this row keeps its address.

class LocomotorStore
{
public:
	virtual void reset(void);
};

void LocomotorStore::reset(void)
{
}
