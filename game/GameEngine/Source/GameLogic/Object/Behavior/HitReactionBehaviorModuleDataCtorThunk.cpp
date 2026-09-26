// cl: /DNDEBUG /MD /EHsc
// The byte-verified ModuleFactory friend allocator fixes this class at 0x30
// bytes. Its clean destructor proves the two member subobjects at +0x18/+0x1C.

class HRBMD_Buffer
{
public:
    HRBMD_Buffer();
    ~HRBMD_Buffer();

private:
    unsigned int m_value;
};

class HRBMD_Base
{
public:
    virtual ~HRBMD_Base() {}

protected:
    unsigned int m_field04;
    unsigned int m_field08;
    unsigned int m_field0c;
    unsigned int m_field10;
    float m_field14;
};

class HitReactionBehaviorModuleData : public HRBMD_Base
{
public:
    HitReactionBehaviorModuleData();
    virtual ~HitReactionBehaviorModuleData();

private:
    HRBMD_Buffer m_bufferA;
    HRBMD_Buffer m_bufferB;
    unsigned int m_field20;
    unsigned int m_field24;
    unsigned int m_field28;
    unsigned int m_field2c;
};

// ??0HitReactionBehaviorModuleData@@QAE@XZ
HitReactionBehaviorModuleData::HitReactionBehaviorModuleData()
{
    m_field0c = 0;
    m_field10 = 0;
    m_field20 = 0;
    m_field24 = 0;
    m_field28 = 0;
    m_field2c = 0;
    m_field08 = 5;
    m_field14 = 300.0f;
}
