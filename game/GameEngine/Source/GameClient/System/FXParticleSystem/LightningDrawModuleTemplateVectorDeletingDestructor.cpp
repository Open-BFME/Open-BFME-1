// cl: /O2
// Retail RVA 0x005D9230. The wrapper's scalar-destructor operand is ILT
// 0x00011A3B, which routes directly to the matched destructor at 0x005D9130.
void operator delete[](void *block);

namespace FXParticleSystem
{
class LightningDrawModuleTemplate
{
public:
    virtual ~LightningDrawModuleTemplate();

private:
    unsigned char m_data[0x34];
};

LightningDrawModuleTemplate *MakeLightningDrawModuleTemplateArray()
{
    return new LightningDrawModuleTemplate[2];
}

void DeleteLightningDrawModuleTemplateArray(LightningDrawModuleTemplate *array)
{
    delete[] array;
}
}
