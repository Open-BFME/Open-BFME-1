// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift ModuleData dtor MASM dump to standalone C++ thunk.

class BehaviorModuleData
{
public:
    virtual ~BehaviorModuleData() {}

private:
    unsigned char m_base[0x04];
};

class AnimationSoundMember
{
public:
    ~AnimationSoundMember();
};

class __declspec(novtable) AnimationSoundClientBehaviorModuleData : public BehaviorModuleData
{
public:
    virtual ~AnimationSoundClientBehaviorModuleData();

private:
    AnimationSoundMember m_sound;
};

// ??1AnimationSoundClientBehaviorModuleData@@UAE@XZ
AnimationSoundClientBehaviorModuleData::~AnimationSoundClientBehaviorModuleData()
{
}
