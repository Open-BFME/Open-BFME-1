// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// RVA 00230BF0, 1020 bytes, ret16, no EH. Analyst pack 002417E0 supplies
// hub/owner/Object contracts. Remaining layouts follow the complete retail body.
// The transform is native Matrix3D: identity, Set_X/Y/Z_Translation, Rotate_Z.
// Retail's c-first x87 schedule (fcos; fstp; fsin; fld c; fld st(1); fmul zero)
// comes from the three single-axis translation setters; Set_Translation(Vector3)
// gives the sine-first schedule instead. The cached-position copy is a 12-byte
// block copy (memcpy), which lets the flag store and +208 load schedule between
// its first and second words exactly as retail does.
// Record00230BF0 is the ignored 16-byte hidden result of 002350C0; it
// shares the delta slot. Preserve the nested scopes and original argument homes.
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>
#include <math.h>
#include <string.h>
#include "coord3d.h"
#define _OPERATOR_NEW_DEFINED_
#include "WWMath/matrix3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &p) : Coord3DBase(p) {}
inline Coord3DBase& Coord3DBase::operator=(const Coord3DBase &p) {
 struct Raw { unsigned x,y,z; }; *(Raw*)this=*(const Raw*)&p; return *this;
}
inline Coord3D& Coord3D::operator=(const Coord3D &p) {
 Coord3DBase *base=this; *base=p; return *this;
}
inline Coord3D& Coord3D::Sub(const Coord3DBase &p) {x-=p.x; y-=p.y; z-=p.z; return *this;}
inline float Coord3D::length() const {float v=x*x;v=v+z*z;v=v+y*y;return (float)sqrt(v);}
inline void Coord3D::scale(float a) {x*=a;y*=a;z*=a;}
inline void Coord3D::add(const Coord3DBase *p) {x+=p->x;y+=p->y;z+=p->z;}

class Call00230BF0 {};
template<class T> __forceinline T method230BF0(void (*raw)()) {
 union { void (*raw)(); T m; } u; u.raw=raw; return u.m;
}
#define CALL(T,p,j) (((Call00230BF0*)(p))->*method230BF0<T>(j))
extern void j_000423c0(); extern void j_0002191d(); extern void j_0001fb9a();
extern void j_0001f000(); extern void j_00006c12(); extern void j_00021017();
extern void j_000230ab(); extern void j_00024ea6(); extern void j_00019736();
extern void j_00049413(); extern void j_000361ce(); extern void j_0003a1a7(); extern void j_0000d81e();
typedef void (Call00230BF0::*Void0)();
typedef void (Call00230BF0::*VoidBool)(bool);
typedef void (Call00230BF0::*VoidPtr)(const void*);
typedef void *(Call00230BF0::*Pointer0)();
typedef float (Call00230BF0::*FloatPtr)(const void*);
typedef void (Call00230BF0::*Apply4)(void*,const Coord3D*,float,bool);
typedef void (Call00230BF0::*Apply3)(void*,const Coord3D*,float);

class Conditions00230BF0 {
 _STL::bitset<320> bits;
public:
 bool test(int bit) const {return bits.test(bit);}
 void set(int bit) {bits.set(bit);}
 void reset(int bit) {bits.reset(bit);}
};
// Receiver is the Object AI pointer; only slot184 is used in this body.
class MemberAI00230BF0 {
public:
 virtual void slots000();
 virtual void slot004();
 virtual void slot008();
 virtual void slot00c();
 virtual void slot010();
 virtual void slot014();
 virtual void slot018();
 virtual void slot01c();
 virtual void slot020();
 virtual void slot024();
 virtual void slot028();
 virtual void slot02c();
 virtual void slot030();
 virtual void slot034();
 virtual void slot038();
 virtual void slot03c();
 virtual void slot040();
 virtual void slot044();
 virtual void slot048();
 virtual void slot04c();
 virtual void slot050();
 virtual void slot054();
 virtual void slot058();
 virtual void slot05c();
 virtual void slot060();
 virtual void slot064();
 virtual void slot068();
 virtual void slot06c();
 virtual void slot070();
 virtual void slot074();
 virtual void slot078();
 virtual void slot07c();
 virtual void slot080();
 virtual void slot084();
 virtual void slot088();
 virtual void slot08c();
 virtual void slot090();
 virtual void slot094();
 virtual void slot098();
 virtual void slot09c();
 virtual void slot0a0();
 virtual void slot0a4();
 virtual void slot0a8();
 virtual void slot0ac();
 virtual void slot0b0();
 virtual void slot0b4();
 virtual void slot0b8();
 virtual void slot0bc();
 virtual void slot0c0();
 virtual void slot0c4();
 virtual void slot0c8();
 virtual void slot0cc();
 virtual void slot0d0();
 virtual void slot0d4();
 virtual void slot0d8();
 virtual void slot0dc();
 virtual void slot0e0();
 virtual void slot0e4();
 virtual void slot0e8();
 virtual void slot0ec();
 virtual void slot0f0();
 virtual void slot0f4();
 virtual void slot0f8();
 virtual void slot0fc();
 virtual void slot100();
 virtual void slot104();
 virtual void slot108();
 virtual void slot10c();
 virtual void slot110();
 virtual void slot114();
 virtual void slot118();
 virtual void slot11c();
 virtual void slot120();
 virtual void slot124();
 virtual void slot128();
 virtual void slot12c();
 virtual void slot130();
 virtual void slot134();
 virtual void slot138();
 virtual void slot13c();
 virtual void slot140();
 virtual void slot144();
 virtual void slot148();
 virtual void slot14c();
 virtual void slot150();
 virtual void slot154();
 virtual void slot158();
 virtual void slot15c();
 virtual void slot160();
 virtual void slot164();
 virtual void slot168();
 virtual void slot16c();
 virtual void slot170();
 virtual void slot174();
 virtual void slot178();
 virtual void slot17c();
 virtual void slot180();
 virtual bool slot184();
};
struct MemberObject00230BF0 {
 char pad00[0x38]; Coord3D m_position; float m_orientation;
 char pad48[0x74-0x48]; int m_id;
 char pad78[0x110-0x78]; Conditions00230BF0 m_modelConditionFlags;
 char pad138[0x178-0x138]; Coord3D value178;
 char pad184[2]; bool flag186;
 char pad187[0x204-0x187]; MemberAI00230BF0 *m_ai; void *ptr208;
};
static __forceinline void clear230BF0(MemberObject00230BF0 *o,int bit) {
 if(o->m_modelConditionFlags.test(bit)) {o->m_modelConditionFlags.reset(bit);CALL(Void0,o,j_0002191d)();}
}
static __forceinline void set230BF0(MemberObject00230BF0 *o,int bit) {
 if(!o->m_modelConditionFlags.test(bit)) {o->m_modelConditionFlags.set(bit);CALL(Void0,o,j_0002191d)();}
}
struct BfmeMemberIndexNode {char pad00[0x14];int value14;};
struct BfmeMemberIndexIterator {BfmeMemberIndexNode *node;};
class BfmeMemberIndexMap {public: BfmeMemberIndexIterator find(const int &); BfmeMemberIndexNode *header;char pad04[8];};
typedef BfmeMemberIndexIterator (Call00230BF0::*Find)(const int&);
// 002301A0 copies two words into its hidden result and returns with ret8.
class BfmePairDH {
public:
 float value00,value04;
 BfmePairDH() {}
 BfmePairDH(const BfmePairDH &p):value00(p.value00),value04(p.value04) {}
};
class Gen_002301A0 {public: BfmePairDH bfmeGet(int) const;};
// 002350C0 uses 00233C80 ctor and 00232470 copy: four dwords, ret8.
struct Record00230BF0 {
 unsigned word00; float value04,value08,value0C;
 Record00230BF0() {}
 Record00230BF0(const Record00230BF0 &p):word00(p.word00),value04(p.value04),value08(p.value08),value0C(p.value0C) {}
};
typedef Record00230BF0 (Call00230BF0::*RecordInt)(int);
struct Sample00230BF0 {unsigned word00;float value04,orientation08;char pad0C[12];};
class MemberMotion00230BF0 {
public:
 char pad00[8];MemberObject00230BF0 *owner08;
 char pad0C[0x120-12];BfmeMemberIndexMap index120;
 char pad12C[0x1FC-0x12C];bool flag1FC;
 char pad1FD[0x610-0x1FD];char samples610[0x7F4-0x610];int count7F4;
 Sample00230BF0 &sample(int n) {return ((Sample00230BF0*)samples610)[n];}
 void apply(MemberObject00230BF0 *,const Coord3D *,float,bool);
};
void MemberMotion00230BF0::apply(MemberObject00230BF0 *obj,const Coord3D *destination,float orientation,bool flag)
{
 if(obj->m_modelConditionFlags.test(207)) {
  CALL(Apply4,this,j_000423c0)(obj,destination,orientation,flag);
  clear230BF0(obj,207);
  return;
 }
 if(obj->m_ai && obj->m_ai->slot184()) {clear230BF0(obj,60);return;}
 if(flag1FC) {CALL(Apply3,this,j_0001fb9a)(obj,destination,orientation);return;}
 Coord3D position;
 {
 int index;
 {
 int id=obj->m_id;
 BfmeMemberIndexIterator found=index120.find(id);
 index=found.node!=index120.header ? found.node->value14 : 0;
 BfmePairDH pair=((Gen_002301A0*)this)->bfmeGet(index);
 int n=count7F4-1;
 while(n>0) {if(sample(n).value04==pair.value00) break;--n;}
 if(n<0)n=0;
 orientation=sample(n).orientation08;
 }
 float speed=9999.0f;
 float turn=3.1415927f;
 void *locomotor=CALL(Pointer0,obj,j_00021017)();
 if(locomotor) {
  speed=CALL(FloatPtr,locomotor,j_000230ab)(obj)*1.25f;
  turn=CALL(FloatPtr,locomotor,j_00024ea6)(obj);
 }
 if((((const unsigned*)&owner08->m_modelConditionFlags)[1]&0x10000000)!=0)set230BF0(obj,60);
 else clear230BF0(obj,60);
 if((((const unsigned*)&owner08->m_modelConditionFlags)[6]&0x1000)!=0) {
  set230BF0(obj,204);
  CALL(RecordInt,this,j_00019736)(index);
  float relative=CALL(FloatPtr,obj,j_00049413)(destination);
  if(relative>turn)relative=turn;
  else if(relative < -turn)relative=-turn;
  orientation=relative+obj->m_orientation;
 } else clear230BF0(obj,204);
 position.x=obj->m_position.x;
 position.y=obj->m_position.y;
 position.z=obj->m_position.z;
 {
 Coord3D delta;
 delta.x=destination->x;
 delta.y=destination->y;
 delta.z=destination->z;
 delta.Sub(position);
 if(delta.length()>speed) {
  delta.normalize();
  delta.scale(speed);
  position.add(&delta);
 } else position=*destination;
 }
 }
 Matrix3D transform(true);
 transform.Set_X_Translation(position.x);
 transform.Set_Y_Translation(position.y);
 transform.Set_Z_Translation(position.z);
 transform.Rotate_Z(orientation);
 CALL(VoidPtr,obj,j_000361ce)(&transform);
 CALL(VoidPtr,obj,j_0003a1a7)(&position);
 memcpy(&obj->value178,&position,sizeof(Coord3D));
 obj->flag186=true;
 if(obj->ptr208)CALL(VoidBool,obj->ptr208,j_0000d81e)(false);
}
