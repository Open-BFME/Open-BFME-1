// cl: /DNDEBUG /MD /EHsc
//
// Retail's AnimationSoundClientBehaviorModuleData vtable at 0x011155E0
// names this scalar deleting destructor in slot zero. Its call target is the
// independently matched destructor body at 0x00606120.

class AnimationSoundClientBehaviorModuleDataMember
{
public:
	~AnimationSoundClientBehaviorModuleDataMember();
};

class AnimationSoundClientBehaviorModuleDataBase
{
public:
	virtual ~AnimationSoundClientBehaviorModuleDataBase() {}
private:
	unsigned char m_pad[0x4];
};

class AnimationSoundClientBehaviorModuleData
	: public AnimationSoundClientBehaviorModuleDataBase
{
public:
	virtual ~AnimationSoundClientBehaviorModuleData();
private:
	AnimationSoundClientBehaviorModuleDataMember m_member;
};

AnimationSoundClientBehaviorModuleData::~AnimationSoundClientBehaviorModuleData()
{
}
