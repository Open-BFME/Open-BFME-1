// cl: /DNDEBUG /MD /EHsc
//
// The matched constructor at 0x00201BB0 installs the dedicated
// OathbreakersFadeAwayBehavior vtable 0x010A5124. Slot-zero ILT 0x00006622
// reaches wrapper 0x00201CC0, which calls complete-destructor ILT 0x00038262
// and the matched class destructor body.

class OathbreakersFadeAwayBehavior
{
public:
	virtual ~OathbreakersFadeAwayBehavior();
};

void forceOathbreakersFadeAwayBehaviorDeletingDestructor()
{
	OathbreakersFadeAwayBehavior value;
}
