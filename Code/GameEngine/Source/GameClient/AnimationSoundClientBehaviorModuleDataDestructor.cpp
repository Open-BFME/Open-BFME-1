// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AnimationSoundClientBehaviorModuleData dtor. PropagandaTower SEH pattern.

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

class __declspec(novtable) AnimationSoundClientBehaviorModuleData : public AnimationSoundClientBehaviorModuleDataBase
{
public:
	virtual ~AnimationSoundClientBehaviorModuleData();
private:
	AnimationSoundClientBehaviorModuleDataMember m_member;
};

// ??1AnimationSoundClientBehaviorModuleData@@UAE@XZ
AnimationSoundClientBehaviorModuleData::~AnimationSoundClientBehaviorModuleData()
{
}
