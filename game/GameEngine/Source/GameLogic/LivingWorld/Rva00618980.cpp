// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#include "PreRTS.h"
#include "Common/Overridable.h"
#include "Common/Override.h"

extern bool __cdecl Rva007397E0(void *, float, float, float);
struct BfmeThingGN : Overridable {
    unsigned int wordC;
    float float10, float14;
};
struct BfmeSourceGN {
    unsigned int word0, word4;
    void *ptr8;
};
class Rva00618980Object {
public:
    unsigned int word0;
    OVERRIDE<BfmeThingGN> data4;
    unsigned int word8;
    BfmeSourceGN *ptrC;
    bool byte10;
    unsigned char pad11[3];
    float float14, float18;
    void rva00618980(int value);
};
// Address-qualified owner; layout follows the matched neighboring update.
// Evidence: targets/game/reverse/identity_evidence/00618980-native-override.md
void Rva00618980Object::rva00618980(int value)
{
    unsigned char active = (unsigned char)value;
    if (byte10 && !active) {
        byte10 = false;
        float14 = 0.0f;
        float color = data4->float10;
        Rva007397E0(ptrC->ptr8, color, color, color);
        return;
    }
    if (!byte10 && active) {
        byte10 = true;
        float14 = 0.0f;
    }
}
