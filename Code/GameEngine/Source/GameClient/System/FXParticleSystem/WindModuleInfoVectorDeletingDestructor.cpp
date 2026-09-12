// cl: /O2
// Retail RVA 0x005BDAD0. The wrapper's scalar-destructor operand is ILT
// 0x0001B31F, which routes to the matched destructor at 0x005BD960.
void operator delete[](void *block);

namespace FXParticleSystem
{
class WindModuleInfo
{
public:
    virtual ~WindModuleInfo();
private:
    unsigned char m_data[0x44];
};

WindModuleInfo *MakeWindModuleInfoArray()
{ return new WindModuleInfo[2]; }

void DeleteWindModuleInfoArray(WindModuleInfo *array)
{ delete[] array; }
}
