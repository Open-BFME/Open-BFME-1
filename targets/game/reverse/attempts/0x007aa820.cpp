// ?method@Rva007AA820@@QAEXPAPAVCameraClass@@@Z
// partial score=0.8221 date=2026-10-03
// cl: /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Complete experimental reconstruction; not a production or binding claim.
// Retail extent is422B (RET4 at007AA9C3, INT3 starts007AA9C6), while the
// current generated ledger row is416B and omits ADD ESP40/RET4. Do not trim
// this source to that row. Record the boundary only with an exact landing.
// Full422B probe:422 emitted bytes,62 nonrelocation differences,one shifted
// relocation site,shape .957; true-extent quality .8531. Automatic bank score
// uses the stale416B ledger, and is intentionally kept distinct from that.
// Register/frame issue420B/188diff fixed by keeping the freshly reloaded
// feather count live through the repeated-quad loop test. Remaining differences
// are native Vector3 copy scheduling (+B5..+115); do not replace covered types.
// Native std::list iterator matches next pointer0/value8; node vertices54/count58.
// GlobalData's reference m_featherWater offset is NOT98 (compile-time check
// failed). Name oracle identifies BFME+98, so retain this explicit read-only
// BFME offset accessor until canonical layout migration. No new global pin.
// 7A8400 independently decodes RET4 at7A8D88 and reads its node stack arg;
// 7A8FF0 preserves ECX, reads two args and RET8 at7AA346. Both remain existing
// opaque thunk targets. 7A12C0 lazy24B cached-volume accessor is already matched.
// rva009330C0 is deliberately UNBOUND: target is existing BFMECameraCullBox
// bool Cull_Box(const AABoxClass&). Audit its canonical camera binding before
// promotion. No /alternatename, new pin, header edit or guessed owner identity.
#include "PreRTS.h"
#include "Common/GlobalData.h"
#include "vector3.h"
#include "aabox.h"
#include "camera.h"
#include <list>
struct Rva007AA820Node {
 char pad00[4]; bool field04; char pad05[3]; int field08;
 char pad0C[0x48]; Vector3 *field54; int field58;
};
struct Rva007AA820Call {
 const AABoxClass& box();
 bool cull(const AABoxClass&) const;
 void node(Rva007AA820Node*);
 void quad(Rva007AA820Node*,Vector3*);
};
extern void j_0003a8d2(); extern void j_0003cb2d(); extern void j_00015c26();
extern void rva009330C0(); // Unbound draft name for the independently known direct target.
template<class T> static __forceinline T rva007AA820Member(void(*raw)()) {
 union {void(*p)();T m;} u;u.p=raw;return u.m;
}
static __forceinline int rva007AA820Count() {
 return *(const int*)((const char*)TheWritableGlobalData+0x98);
}
class Rva007AA820 {
public:
 void method(CameraClass**);
 char pad0[0x2ac]; std::list<Rva007AA820Node*> field2AC;
};
void Rva007AA820::method(CameraClass **camera)
{
 for(std::list<Rva007AA820Node*>::iterator it=field2AC.begin();it!=field2AC.end();++it) {
  Rva007AA820Node* node=*it;
  typedef const AABoxClass&(Rva007AA820Call::*Box)();
  const AABoxClass& box=((Rva007AA820Call*)node->*rva007AA820Member<Box>(j_0003a8d2))();
  typedef bool(Rva007AA820Call::*Cull)(const AABoxClass&) const;
  if(((const Rva007AA820Call*)*camera->*rva007AA820Member<Cull>(rva009330C0))(box)) continue;
  if(node->field04) {
   typedef void(Rva007AA820Call::*Node)(Rva007AA820Node*);
   ((Rva007AA820Call*)this->*rva007AA820Member<Node>(j_0003cb2d))(node);
  } else {
   int back=node->field08;
   int count=node->field58;
   int front=back+1;
   if(front>=count)front=0;
   if(back>=count-1)return;
   for(int i=0;i<count/2;++i) {
    const Vector3 *v0=&node->field54[back];
    const Vector3 *v1=&node->field54[front];
    ++front; --back;
    if(back<0)back=count-1;
    if(front>=count)front=0;
    Vector3 vertices[4];
    vertices[0]=*v0; vertices[1]=*v1;
    vertices[2]=node->field54[front];vertices[3]=node->field54[back];
    typedef void(Rva007AA820Call::*Quad)(Rva007AA820Node*,Vector3*);
    int passes=rva007AA820Count();
    if(passes!=0) {
     for(int repeat=0;repeat<passes;++repeat) {
      ((Rva007AA820Call*)this->*rva007AA820Member<Quad>(j_00015c26))(node,vertices);
      passes=rva007AA820Count();
      vertices[0].Z+=4.0f/(float)passes;
     }
    } else {
     ((Rva007AA820Call*)this->*rva007AA820Member<Quad>(j_00015c26))(node,vertices);
    }
    count=node->field58;
   }
  }
 }
}
typedef char MemberSize[(sizeof(void(Rva007AA820Call::*)(Rva007AA820Node*))==4)?1:-1];
