// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: BridgeBehavior scalar-deleting destructor at retail RVA
// 0x001F3EE0 (30 bytes).  The exact constructor at 0x001F3390 installs the
// BridgeBehavior vtable 0x010A2764, whose complete virtual destructor is the
// matched 399-byte body at 0x001F36A0.  BridgeBehaviorDestructorThunk.cpp owns
// the concrete bridge, audio-event, and scaffold-list cleanup.

class BridgeBehavior
{
public:
	__declspec(noinline) virtual ~BridgeBehavior();
};

BridgeBehavior::~BridgeBehavior()
{
}

void Force_BridgeBehavior_Deleting_Destructor(BridgeBehavior *value)
{
	delete value;
}
