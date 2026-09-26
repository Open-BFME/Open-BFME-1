// ??0GarrisonContainModuleData@@QAE@XZ
// partial score=0.5882 date=2026-09-26
// ??0GarrisonContainModuleData@@QAE@XZ
// cl: /O2
// Retail 0x0022F7E0..0x0022F879. The base call routes through ILT
// 0x0000ED77 to the matched 0x002472D0 body; its semantic base name is
// disputed, so this source uses an address-derived ABI view.
// All 18 derived stores and the vtable address match. Remaining codegen:
// retail loads 1.0f into ECX before eleven zero stores and preserves it for
// two later fields; MSVC sinks the load to after the zero run in EAX.
class Rva002472D0Base
{
public:
    Rva002472D0Base();
private:
    unsigned char m_storage[0x2f4];
};
#pragma comment(linker, "/alternatename:??0Rva002472D0Base@@QAE@XZ=?j_0000ed77@@YAXXZ")

class GarrisonContainModuleData : public Rva002472D0Base
{
public:
    GarrisonContainModuleData();
private:
    unsigned char m_tail[0x48];
};

#define S32(off, value) (*(volatile unsigned int *)((unsigned char *)this + off) = (value))
GarrisonContainModuleData::GarrisonContainModuleData()
{
    const unsigned int one = 0x3f800000u;
    S32(0x2f4, 0);
    S32(0x2f8, 0);
    S32(0x2fc, 0);
    S32(0x300, 0);
    S32(0x304, 0);
    S32(0x308, 0);
    S32(0x30c, 0);
    S32(0x310, 0);
    S32(0x314, 0);
    S32(0x318, 0);
    S32(0x324, 0);
    S32(0x000, 0x010ade98u);
    S32(0x31c, one);
    S32(0x320, 0x3ee66666u);
    S32(0x328, 0x497423f0u);
    S32(0x32c, 2);
    S32(0x330, one);
    S32(0x334, 0x3e99999au);
    S32(0x338, 0x3ecccccd);
}
