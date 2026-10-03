// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/locomotor /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "PreRTS.h"
#include "GameClient/Drawable.h"
class Rva00412140 { char storage[0x50]; public: Rva00412140() throw(); };
struct BfmeLinearCoord3D;
class BFMERopeDrawableGetPositionShim { public: const BfmeLinearCoord3D *getPositionLinear() const; };
class BfmeRange970 { public: void bfmeSet970(int,int,int); };
class Rva0041F070Envelope {
public:
    __forceinline void set(const RGBColor &v) {
        typedef void (Rva0041F070Envelope::*Method)(RGBColor);
        typedef void (BfmeRange970::*Original)(int,int,int);
        typedef char Checked[sizeof(Method)==4 && sizeof(Original)==4?1:-1];
        union { Original original; Method method; } p;
        p.original=&BfmeRange970::bfmeSet970;
        (this->*p.method)(v);
    }
};
struct Rva0041F070Vector : Vector3 { Rva0041F070Vector(const Rva0041F070Vector &v):Vector3(v) {} ~Rva0041F070Vector() {} };
class Rva0041F070Global {
public:
    virtual void v00()=0; virtual void v04()=0; virtual void v08()=0; virtual void v0c()=0;
    virtual void v10()=0; virtual void v14()=0; virtual void v18()=0; virtual void v1c()=0;
    virtual void v20()=0; virtual void v24()=0; virtual bool v28()=0; virtual void v2c()=0;
    virtual void v30()=0; virtual void v34()=0; virtual void v38()=0; virtual void v3c()=0;
    virtual float v40(Rva0041F070Vector)=0; virtual float v44(Rva0041F070Vector)=0;
    char unknown04[0x28]; RGBColor value2c; char unknown38[0x70]; int valuea8;
};
class BfmeGlobCC0;
extern BfmeGlobCC0 *g_bfmeGlobCC0;
#define CLOUD ((Rva0041F070Global*)g_bfmeGlobCC0)
class Rva0041F070 {
public:
    void method(bool);
    char unknown00[0x8c]; Rva00412140 *envelope; char unknown90[0x8c]; unsigned value11c;
};
void Rva0041F070::method(bool apply) {
    if(!envelope) envelope=new Rva00412140;
    if(!CLOUD || !CLOUD->v28()) return;
    const Rva0041F070Vector *position=(const Rva0041F070Vector*)((BFMERopeDrawableGetPositionShim*)this)->getPositionLinear();
    float value;
    int kind=CLOUD->valuea8;
    if(kind==1) goto first;
    if(kind==2) goto first;
    if(kind==3) goto second;
    if(kind==4) goto second;
    return;
first: value=CLOUD->v40(*position); goto loaded;
second: value=CLOUD->v44(*position);
loaded:
    if(value <= -25.0f) {
        if(value11c&8) { value11c=4; return; }
        if(!(value11c&2)) value11c=2;
        if(apply) ((Rva0041F070Envelope*)envelope)->set(CLOUD->value2c);
    } else if(value >= 25.0f) {
        if(value11c&4) { value11c=8; return; }
        if(!(value11c&1)) value11c=1;
    } else {
        if(value11c&1) value11c=4;
        else if(value11c&2) value11c=8;
        if(apply) ((Rva0041F070Envelope*)envelope)->set(CLOUD->value2c);
    }
}
