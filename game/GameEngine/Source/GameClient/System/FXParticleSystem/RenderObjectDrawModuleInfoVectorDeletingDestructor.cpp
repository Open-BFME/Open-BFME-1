// cl: /O2
// Retail RVA 0x005DE390. The wrapper's scalar-destructor operand is ILT
// 0x00022903, which routes directly to the matched destructor at 0x005DE1F0.
void operator delete[](void *block);

namespace FXParticleSystem
{
class RenderObjectDrawModuleInfo
{
public:
    virtual ~RenderObjectDrawModuleInfo();

private:
    unsigned char m_data[0x3C];
};

RenderObjectDrawModuleInfo *MakeRenderObjectDrawModuleInfoArray()
{
    return new RenderObjectDrawModuleInfo[2];
}

void DeleteRenderObjectDrawModuleInfoArray(RenderObjectDrawModuleInfo *array)
{
    delete[] array;
}
}
