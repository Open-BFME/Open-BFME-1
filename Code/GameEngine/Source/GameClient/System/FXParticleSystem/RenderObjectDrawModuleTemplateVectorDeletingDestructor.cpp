// cl: /O2
// Retail RVA 0x005DE5E0. The wrapper's scalar-destructor operand is ILT
// 0x00027656, which routes directly to the matched destructor at 0x005DE490.
void operator delete[](void *block);

namespace FXParticleSystem
{
class RenderObjectDrawModuleTemplate
{
public:
    virtual ~RenderObjectDrawModuleTemplate();

private:
    unsigned char m_data[0x44];
};

RenderObjectDrawModuleTemplate *MakeRenderObjectDrawModuleTemplateArray()
{
    return new RenderObjectDrawModuleTemplate[2];
}

void DeleteRenderObjectDrawModuleTemplateArray(RenderObjectDrawModuleTemplate *array)
{
    delete[] array;
}
}
