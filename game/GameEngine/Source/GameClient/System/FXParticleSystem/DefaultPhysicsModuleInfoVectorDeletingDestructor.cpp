// cl: /O2
// Retail RVA 0x005D7F70. The wrapper's scalar-destructor operand is ILT
// 0x00042F28, which routes directly to the matched destructor at 0x005D7E90.
void operator delete[](void *block);

namespace FXParticleSystem
{
class DefaultPhysicsModuleInfo
{
public:
    virtual ~DefaultPhysicsModuleInfo();

private:
    unsigned char m_data[0x1C];
};

DefaultPhysicsModuleInfo *MakeDefaultPhysicsModuleInfoArray()
{
    return new DefaultPhysicsModuleInfo[2];
}

void DeleteDefaultPhysicsModuleInfoArray(DefaultPhysicsModuleInfo *array)
{
    delete[] array;
}
}
