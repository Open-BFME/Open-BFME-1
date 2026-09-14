// cl: /O2

// The constructor at 0x002074C0 identifies this 30-byte scalar-deleting
// destructor as the SlaveWatcherBehaviorModuleData vtable slot.
class SlaveWatcherBehaviorModuleData
{
public:
	virtual ~SlaveWatcherBehaviorModuleData();
};

void forceSlaveWatcherBehaviorModuleDataDeletingDestructor()
{
	SlaveWatcherBehaviorModuleData value;
}
