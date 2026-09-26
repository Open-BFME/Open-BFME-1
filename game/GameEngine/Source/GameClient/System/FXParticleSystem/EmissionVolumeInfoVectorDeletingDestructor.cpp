// cl: /O2
// Retail RVA 0x005BD730. The wrapper's scalar-destructor operand is ILT
// 0x0004AA61, which routes to the matched destructor at 0x005BD6B0.
void operator delete[](void *block);

namespace FXParticleSystem
{
class EmissionVolumeInfo
{
public:
    virtual ~EmissionVolumeInfo();
private:
    unsigned char m_data[0x04];
};

EmissionVolumeInfo *MakeEmissionVolumeInfoArray()
{ return new EmissionVolumeInfo[2]; }

void DeleteEmissionVolumeInfoArray(EmissionVolumeInfo *array)
{ delete[] array; }
}
