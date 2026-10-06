// cl: /DNDEBUG /MD /EHsc
// Complete destructor 0x00604B40 and emitted scalar wrapper 0x00604E60.
// Constructor 0x00605380, module factories, and the installed vtables prove
// identity. This family already has its data/global sources in GameClient.
// Retail stores its two vtables (primary at +0, interface at +0x0C),
// calls a method on the global at 0x012F10D0 with this when non-null, then
// runs the middle base dtor (vtable store) and calls the out-of-line root
// base dtor, all under an SEH frame.

class AnimationSoundClientBehavior;

class AnimationSoundClientBehaviorGlobal
{
public:
    void unregister(AnimationSoundClientBehavior *);
};

class AnimationSoundModuleManager;
extern AnimationSoundModuleManager *TheAnimationSoundModuleManager;

class ASCB_RootBase
{
public:
    virtual ~ASCB_RootBase();

private:
    unsigned char m_pad[8];
};

class ASCB_Iface
{
public:
    virtual void ascbIfaceVslot();
};

class ASCB_MiddleBase : public ASCB_RootBase
{
public:
    virtual ~ASCB_MiddleBase() {}
};

class AnimationSoundClientBehavior : public ASCB_MiddleBase, public ASCB_Iface
{
protected:
    virtual ~AnimationSoundClientBehavior();
};

// ??1AnimationSoundClientBehavior@@MAE@XZ
AnimationSoundClientBehavior::~AnimationSoundClientBehavior()
{
    if (TheAnimationSoundModuleManager) {
        ((AnimationSoundClientBehaviorGlobal *)TheAnimationSoundModuleManager)->unregister(this);
    }
}
