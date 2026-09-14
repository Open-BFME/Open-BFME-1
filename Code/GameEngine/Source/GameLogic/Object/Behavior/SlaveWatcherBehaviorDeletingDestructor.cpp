// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: SlaveWatcherBehavior scalar-deleting destructor at retail RVA
// 0x002076E0 (30 bytes).  The named module constructor at 0x00207300 and
// matched complete virtual destructor at 0x00207580 share the
// SlaveWatcherBehavior vtable (0x00CA64DC); the module factory and update
// method independently establish the class identity.

class SlaveWatcherBehavior
{
public:
	__declspec(noinline) virtual ~SlaveWatcherBehavior();
};

SlaveWatcherBehavior::~SlaveWatcherBehavior()
{
}

// ??_GSlaveWatcherBehavior@@UAEPAXI@Z
void Force_SlaveWatcherBehavior_Deleting_Destructor(SlaveWatcherBehavior *value)
{
	delete value;
}
