// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#include "PreRTS.h"
#include <math.h>
#include "Common/Overridable.h"
#include "Common/Override.h"
#include "WWMath/vector3.h"
#include "WWMath/aabox.h"
#include "WWMath/lineseg.h"
#include "WWMath/colmath.h"

class Rva003BF540 { public: bool test(); };
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
extern bool __cdecl Rva007397E0(void *, float, float, float);
struct Rva00618A90Data : Overridable {
    unsigned int wordC;
    float float10, float14;
};
struct Rva00618A90Holder {
    unsigned int word0, word4;
    void *ptr8;
    void *ptrC;
};
// Drawable view: vslot +0x104 hands back the bounding box.
#define RVA00618C90_SLOT(n) virtual void slot##n();
class Rva00618C90Drawable {
public:
    RVA00618C90_SLOT(000) RVA00618C90_SLOT(004) RVA00618C90_SLOT(008) RVA00618C90_SLOT(00C)
    RVA00618C90_SLOT(010) RVA00618C90_SLOT(014) RVA00618C90_SLOT(018) RVA00618C90_SLOT(01C)
    RVA00618C90_SLOT(020) RVA00618C90_SLOT(024) RVA00618C90_SLOT(028) RVA00618C90_SLOT(02C)
    RVA00618C90_SLOT(030) RVA00618C90_SLOT(034) RVA00618C90_SLOT(038) RVA00618C90_SLOT(03C)
    RVA00618C90_SLOT(040) RVA00618C90_SLOT(044) RVA00618C90_SLOT(048) RVA00618C90_SLOT(04C)
    RVA00618C90_SLOT(050) RVA00618C90_SLOT(054) RVA00618C90_SLOT(058) RVA00618C90_SLOT(05C)
    RVA00618C90_SLOT(060) RVA00618C90_SLOT(064) RVA00618C90_SLOT(068) RVA00618C90_SLOT(06C)
    RVA00618C90_SLOT(070) RVA00618C90_SLOT(074) RVA00618C90_SLOT(078) RVA00618C90_SLOT(07C)
    RVA00618C90_SLOT(080) RVA00618C90_SLOT(084) RVA00618C90_SLOT(088) RVA00618C90_SLOT(08C)
    RVA00618C90_SLOT(090) RVA00618C90_SLOT(094) RVA00618C90_SLOT(098) RVA00618C90_SLOT(09C)
    RVA00618C90_SLOT(0A0) RVA00618C90_SLOT(0A4) RVA00618C90_SLOT(0A8) RVA00618C90_SLOT(0AC)
    RVA00618C90_SLOT(0B0) RVA00618C90_SLOT(0B4) RVA00618C90_SLOT(0B8) RVA00618C90_SLOT(0BC)
    RVA00618C90_SLOT(0C0) RVA00618C90_SLOT(0C4) RVA00618C90_SLOT(0C8) RVA00618C90_SLOT(0CC)
    RVA00618C90_SLOT(0D0) RVA00618C90_SLOT(0D4) RVA00618C90_SLOT(0D8) RVA00618C90_SLOT(0DC)
    RVA00618C90_SLOT(0E0) RVA00618C90_SLOT(0E4) RVA00618C90_SLOT(0E8) RVA00618C90_SLOT(0EC)
    RVA00618C90_SLOT(0F0) RVA00618C90_SLOT(0F4) RVA00618C90_SLOT(0F8) RVA00618C90_SLOT(0FC)
    RVA00618C90_SLOT(100)
    virtual const AABoxClass &getBoundingBox();                    // +0x104
};
#undef RVA00618C90_SLOT
// Living-world view at retail 0x012F7048 (data_rows.csv); vslot +0x1C turns a
// screen point into a pick ray (start, direction).
class Rva006092D0State {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14(); virtual void slot18();
    virtual void getPickRay(const ICoord2D *screen, Vector3 *start, Vector3 *dir);    // +0x1C
};
extern Rva006092D0State *g_rva012F7048LivingWorld;
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
    bool rva0004a444(const ICoord2D *point);
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
        if (reinterpret_cast<Rva003BF540 *>(TheLivingWorldLogic)->test()) {
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

// Retail 0x00618C90 (276 bytes, ret 4), reached through ILT 0x0004A444 by the
// matched 0x00615D50 lookup, which tests each living-world object against the
// screen point. The holder's drawable (+0x0C, else +0x08) supplies a bounding
// box through vslot +0x104; the living-world view turns the point into a pick
// ray, stretched 3000 units into a LineSegClass (out-of-line recalculate at
// 0x003FE770) and handed to CollisionMath::Overlap_Test; anything but OUTSIDE
// is a hit. Retail copies the start (x87 for X/Y, a stored Z) before summing in
// place, and reads each direction component before its start component; the
// volatile reads reproduce that operand order (docs/shape_levers.md).
bool Rva00615D50Object::rva0004a444(const ICoord2D *point)
{
    if (ptrC == 0)
        return false;

    Rva00618C90Drawable *drawable = (Rva00618C90Drawable *)ptrC->ptrC;
    if (drawable == 0)
    {
        drawable = (Rva00618C90Drawable *)ptrC->ptr8;
        if (drawable == 0)
            return false;
    }

    AABoxClass box = drawable->getBoundingBox();
    Vector3 start, dir;
    g_rva012F7048LivingWorld->getPickRay(point, &start, &dir);
    dir *= 3000.0f;
    Vector3 origin = start;
    start.X = *(volatile float *)&dir.X + start.X;
    start.Y = *(volatile float *)&dir.Y + start.Y;
    start.Z = *(volatile float *)&dir.Z + start.Z;
    LineSegClass ray(origin, start);
    if (CollisionMath::Overlap_Test(box, ray) == CollisionMath::OUTSIDE)
        return false;
    return true;
}
