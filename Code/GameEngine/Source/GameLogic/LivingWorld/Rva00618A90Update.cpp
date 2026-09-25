// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#include "PreRTS.h"
#include <math.h>
#include "Common/Overridable.h"
#include "Common/Override.h"

class Rva003BF540 { public: bool test(); };
class Glo012F1028Type;
extern Glo012F1028Type *Glo012F1028;
extern bool __cdecl Rva007397E0(void *, float, float, float);
struct Rva00618A90Data : Overridable {
    unsigned int wordC;
    float float10, float14;
};
struct Rva00618A90Holder {
    unsigned int word0, word4;
    void *ptr8;
};
class Rva00615D50Object {
public:
    unsigned int word0;
    OVERRIDE<Rva00618A90Data> data4;
    unsigned int word8;
    Rva00618A90Holder *ptrC;
    bool byte10;
    unsigned char pad11[3];
    float float14, float18;
    void rva00618a90();
};
static inline const float &Rva00618A90Min(const float &a, const float &b) {
    return a < b ? a : b;
}
// Matched 00616110 map traversal names this member via ILT 00010186.
// OVERRIDE<T> supplies the witnessed next-override resolution at +4.
// Float constants are retail 010B75EC=0.15, 01080BBC=0.2, and
// 01097114=pi/2. The initial holder remains cached in the zero-state arm;
// other arms reload ptrC after callbacks, matching retail alias behavior.
void Rva00615D50Object::rva00618a90()
{
    Rva00618A90Holder *holder = ptrC;
    if (holder->ptr8 && float18 != 0.0f) {
        if (reinterpret_cast<Rva003BF540 *>(Glo012F1028)->test()) {
            float angle = float14 + 0.15f;
            float14 = angle;
            float base = data4->float10;
            float color = base + data4->float14 * fabs(cos(angle));
            Rva007397E0(ptrC->ptr8, color, color, color);
        } else {
            float14 = 0.0f;
            float color = data4->float10;
            Rva007397E0(ptrC->ptr8, color, color, color);
        }
    } else if (holder->ptr8 && byte10) {
        float14 += 0.2f;
        float angle = Rva00618A90Min(float14, 1.5707963705062866f);
        float14 = angle;
        float base = data4->float10;
        float color = base + data4->float14 * fabs(cos(angle));
        Rva007397E0(holder->ptr8, color, color, color);
    }
}
