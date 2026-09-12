// cl: /O2
// Retail RVA 0x005DEA10. The wrapper's scalar-destructor operand is ILT
// 0x00038410, which routes directly to the matched destructor at 0x005DE870.
void operator delete[](void *block);

namespace FXParticleSystem
{
class TerrainCollisionModuleTemplate
{
public:
    virtual ~TerrainCollisionModuleTemplate();

private:
    unsigned char m_data[0x24];
};

TerrainCollisionModuleTemplate *MakeTerrainCollisionModuleTemplateArray()
{
    return new TerrainCollisionModuleTemplate[2];
}

void DeleteTerrainCollisionModuleTemplateArray(TerrainCollisionModuleTemplate *array)
{
    delete[] array;
}
}
