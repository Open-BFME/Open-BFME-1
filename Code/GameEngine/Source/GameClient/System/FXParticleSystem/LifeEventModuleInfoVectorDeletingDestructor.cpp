// cl: /O2
// Retail RVA 0x005DDEE0. The wrapper's scalar-destructor operand is ILT
// 0x00045CA5, which routes directly to the matched destructor at 0x005DDDC0.
void operator delete[](void *block);

namespace FXParticleSystem
{
class LifeEventModuleInfo
{
public:
    virtual ~LifeEventModuleInfo();

private:
    unsigned char m_data[0x14];
};

LifeEventModuleInfo *MakeLifeEventModuleInfoArray()
{
    return new LifeEventModuleInfo[2];
}

void DeleteLifeEventModuleInfoArray(LifeEventModuleInfo *array)
{
    delete[] array;
}
}
