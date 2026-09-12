// cl: /O2
// Retail RVA 0x005DE770. The wrapper's scalar-destructor operand is ILT
// 0x0004B00B, which routes directly to the matched destructor at 0x005DE650.
void operator delete[](void *block);

namespace FXParticleSystem
{
class TerrainCollisionModuleInfo
{
public:
    virtual ~TerrainCollisionModuleInfo();

private:
    unsigned char m_data[0x18];
};

TerrainCollisionModuleInfo *MakeTerrainCollisionModuleInfoArray()
{
    return new TerrainCollisionModuleInfo[2];
}

void DeleteTerrainCollisionModuleInfoArray(TerrainCollisionModuleInfo *array)
{
    delete[] array;
}
}
