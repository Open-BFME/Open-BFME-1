// ?update@Rva003A4FD0State@@QAEXPAX@Z
// partial score=0.54545455 date=2026-09-25
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
struct Coord3D { float x, y, z; };
class LivingWorldRegion;
class LivingWorldRegionManager {
public:
    LivingWorldRegion *rva003C8160(Coord3D *position);
    void rva003C9CB0(void *, void *, void *, void *);
};
class Glo012F1028Type {
public:
    void rva003BE020(LivingWorldRegion *region);
    char opaque00[0x28];
    LivingWorldRegionManager *manager;
};
extern Glo012F1028Type *Glo012F1028;
class BfmeHostCB { public: char bfmePopCB(); };
struct BfmeArgFHA;
extern bool __stdcall bfmeGoFHA(BfmeArgFHA *);
class Rva003A4FD0State {
public:
    void update(void *argument);
    AsciiString stringAt003A4390();
    char opaque00[0xC];
    float value0C;
    float value10;
    char opaque14[8];
    unsigned char byte1C, byte1D, byte1E;
};
void Rva003A4FD0State::update(void *argument)
{
    if (((BfmeHostCB *)this)->bfmePopCB())
        return;
    if (byte1D && byte1E) {
        LivingWorldRegionManager *manager = Glo012F1028->manager;
        Coord3D point = {value0C, value10, 0.0f};
        LivingWorldRegion *region = manager->rva003C8160(&point);
        if (region && bfmeGoFHA((BfmeArgFHA *)region)) {
            AsciiString temporary = stringAt003A4390();
            manager->rva003C9CB0((char *)region + 4, &temporary, 0, argument);
            Glo012F1028->rva003BE020(region);
        }
    }
    byte1C = 0;
}
