// stlport
// Intended home: Code/GameEngine/Source/GameClient/Drawable.cpp.
// Banked: instruction-shape exact; unresolved typed callees prevent a landing.
// Identity: Drawable secondary vtable VA 0x010F154C slot +0x0C ->
// ILT 0x00037F10 -> 0x0041D290. Its +8 name getter returns "Drawable".
// Constructor 0x00418DE8 installs this vtable at the full object +0x60.
// 4763-byte extent: RVA 0041D290 through RET 4 at 0041E528.
// cl: /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /DNDEBUG /DWIN32 /MD /EHsc /Ob2 /Ireference/shims/stringbaseascii /ICode/Libraries/Source/WWVegas/WWLib /ICode/GameEngine/Source/Common/System /ICode/Libraries/Source/WWVegas/WWMath /Ireference/shims/sweep
#include "Common/AsciiString.h"
#include "xfer.h"
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
// BFME Drawable::xfer reconstruction. Offsets below are from Snapshot subobject
// this (full Drawable + 0x60), independently witnessed in 0041d290.asm.
// See CALLEES.md for existing bindings and the remaining unresolved contracts.
template<class T> inline T &field(void *p, int o) { return *(T*)((char*)p+o); }
struct RGBColor { float r,g,b; };
#define _OPERATOR_NEW_DEFINED_
#include "matrix3d.h"
typedef Matrix3D RvaMatrix;
struct XferException { void *p; int tag; XferException(int,const char*,...);XferException(const XferException&);~XferException(); };
extern "C" XferException* __cdecl bfmeFormatText(XferException*,int,const char*,...);
extern void __stdcall _CxxThrowException(void*,void*);
#define invalidData() throw XferException(5,0)
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char*,const char*);
extern "C" unsigned __cdecl strlen(const char*);
#pragma intrinsic(strlen)
class Rva000B56F0Object {public:void *selectStorage();};
class Rva0041D290AudioInfo {
public:
 virtual ~Rva0041D290AudioInfo(); void addRef(){InterlockedIncrement(&refs);} long releaseRef(){long n=InterlockedDecrement(&refs);if(n<=0)delete this;return n;} long refs; char rest[0x9c];
 Rva0041D290AudioInfo(int); Rva0041D290AudioInfo(const Rva0041D290AudioInfo&,int);
 void rva000b5710(Xfer*); const AsciiString& rva000b56f0(){return *(AsciiString*)((Rva000B56F0Object*)this)->selectStorage();}
};
template<class T> class Rva0041D290Ref {
public:
 T *p;
 operator const void*()const{return p;}
 Rva0041D290Ref():p(0){}
 Rva0041D290Ref(T *v):p(v){if(p)p->addRef();}
 Rva0041D290Ref(const Rva0041D290Ref&v):p(v.p){if(p)p->addRef();}
 ~Rva0041D290Ref(){if(p)p->releaseRef();}
 Rva0041D290Ref& operator=(const Rva0041D290Ref&v){if(this!=&v){if(v.p)v.p->addRef();if(p)p->releaseRef();p=v.p;}return *this;}
 void operator=(T *v){if(p!=v){clear();p=v;if(p)p->addRef();}}
 void clear(){if(p){p->releaseRef();p=0;}}
};
class AudioEventRTS {
public: char bytes[0x70]; AudioEventRTS(const AsciiString&,int); void rva000b2ba0(Xfer*);
};
extern AsciiString Rva01336e50;
class Rva0041D290Ambient { public: virtual ~Rva0041D290Ambient(); AudioEventRTS event; Rva0041D290Ambient():event(Rva01336e50,0){} };
class Rva0041D290Audio {
public:
 virtual void v00();
#define V(n) virtual void v##n();
 V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(0a) V(0b) V(0c) V(0d) V(0e) V(0f) V(10) V(11) V(12)
 virtual void v13(unsigned); virtual void v14(unsigned);
 V(15) V(16) V(17) V(18) V(19) V(1a) V(1b) V(1c) V(1d) V(1e) V(1f) V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(2a) V(2b) V(2c) V(2d) V(2e) V(2f) V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(3a) V(3b) V(3c) V(3d) V(3e) V(3f) V(40) V(41) V(42) V(43) V(44)
 virtual void v45(Rva0041D290AudioInfo*); virtual Rva0041D290Ref<Rva0041D290AudioInfo> v46(const AsciiString&);
};
extern Rva0041D290Audio *Rva012ed668;
class TintEnvelope { public: char bytes[0x50]; TintEnvelope() throw(); };
class DrawableLocoInfo { public: char bytes[0x58]; DrawableLocoInfo() throw(); };
class Anim2DTemplate { public: AsciiString getName() const; };
class Anim2DCollection;
class Anim2D { public: char bytes[0x34]; Anim2D(Anim2DTemplate*,Anim2DCollection*);Anim2DTemplate *getTemplate()const{return *(Anim2DTemplate**)(bytes+0xc);} };
class DrawableIconInfo { public: void *v; Anim2D *icon[14]; unsigned keep[14]; void clear(); };
extern const char *Rva012b4f5c[14];
__forceinline int rvaIconIndex(const char *name){for(int i=0;i<14;++i)if(!_strcmpi(Rva012b4f5c[i],name))return i;return -1;}
class Anim2DCollection { public: Anim2DTemplate *findTemplate(const AsciiString&); };
extern Anim2DCollection *Rva012f4ca8;
extern const char *Rva012b4f5c[14];
class Rva0041D290VObject { public: virtual void v00(); V(01) V(02) virtual void v03(Xfer*); };
class BuffManager:public Rva0041D290VObject { char bytes[0x19c]; public: BuffManager(int); };
class Rva0041D290DrawModule {public: virtual void v00(); V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(0a) V(0b) V(0c) V(0d) V(0e) V(0f) V(10) virtual void v11(unsigned); V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(1a) V(1b) V(1c) V(1d) V(1e) V(1f) V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(2a) V(2b) V(2c) V(2d) V(2e) V(2f) V(30) V(31) virtual bool v32();};
class Rva0041D290Client {public: virtual void v00(); V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(0a) V(0b) V(0c) V(0d) V(0e) V(0f) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(1a) V(1b) V(1c) V(1d) V(1e) V(1f) virtual void *v20(unsigned);};
#undef V
extern Rva0041D290Client *Rva012ef4cc;
class Object;
class Pathfinder { public: void removeObjectFromPathfindMap(Object*); void addObjectToPathfindMap(Object*); };
class Rva0041D290Manager {char bytes[0xc];Pathfinder *p;public:Pathfinder *get()const{return p;}};
extern Rva0041D290Manager *Rva012ef214;
typedef _STL::vector<void*> Rva0041D290Vector;
enum Rva0041D290Decal {RvaDecalZero};
class Rva00410F10Allocation;
class Rva00410F10Owner { public: Rva00410F10Allocation *ensure(); };
class BfmeCalc919G { public: int bfmeCalc919G(); };
class Thing {public:void rva00132200(const Matrix3D*);};
class Rva0041D290FullDrawable {public:
 char pad_a8[0xa8];Rva0041D290Decal m_a8;char pad_ac[0xa4];Rva0041D290DrawModule **m_150;
 Rva0041D290DrawModule **getDrawModules()const{return m_150;}
 void setDecal(Rva0041D290Decal type){Rva0041D290Decal &v=m_a8;if(v==type)return;v=type;Rva0041D290DrawModule **dm=getDrawModules();if(*dm)(*dm)->v11(type);}
 void rva00411600(unsigned); RvaMatrix* rva0041cec0(){return (RvaMatrix*)((BfmeCalc919G*)this)->bfmeCalc919G();} void rva00132200(const RvaMatrix* m){((Thing*)this)->rva00132200(m);}
 void rva00417e20(Xfer*); DrawableIconInfo* rva00410f10(){return (DrawableIconInfo*)((Rva00410F10Owner*)this)->ensure();} void rva00411cd0();
 void rva0041abe0(); void rva00417330(Rva0041D290Ref<Rva0041D290AudioInfo>);
 void rva0041ccd0(void*,bool,bool);
};
class Rva0041D290Condition {public:void rva001cb270(Xfer*);};
class Overridable {public:const Overridable *getFinalOverride()const;};
class Rva0041D290Override {public:Rva0041D290Override *rva00087a80(){return (Rva0041D290Override*)((Overridable*)this)->getFinalOverride();}};
static __declspec(noinline) Rva0041D290Ref<Rva0041D290AudioInfo> rva00415c20() { static Rva0041D290Ref<Rva0041D290AudioInfo> marker; if(!marker.p) marker=new Rva0041D290AudioInfo(0);return marker; }
extern void BfmeParticleSystemXferHandle(Xfer&,void*);
extern void BfmeParticleSystemXferMatrix(Xfer&,void*);
class MidVirtualSlot90Receiver;
extern void Rva0010C3C0(MidVirtualSlot90Receiver*,void*); extern void Rva0010C1C0(MidVirtualSlot90Receiver*,void*);
extern void Rva0010BE80(MidVirtualSlot90Receiver*,void*); class BfmeSeedTarget;extern void bfmeHandOver_00001A50(BfmeSeedTarget*,void*);
class Rva0041D290ThingBase {public: virtual ~Rva0041D290ThingBase(); char bytes[0x5c];};
class Rva0041D290SnapshotBase {
public: virtual ~Rva0041D290SnapshotBase();
protected: virtual void loadPostProcess(); virtual const char *v02() const; virtual void xfer(Xfer*);
};
enum ObjectID {RvaInvalidID};
class Object {char pad[0x74];ObjectID m_74;public:ObjectID getID()const{return m_74;}};
__forceinline ObjectID getObjectID(void *o) {return o?field<ObjectID>(o,0x74):RvaInvalidID;}
class ModelConditionFlags;
enum DrawableID {DrawableInvalid};
class Drawable:public Rva0041D290ThingBase,public Rva0041D290SnapshotBase {
TintEnvelope* m_4;
TintEnvelope* m_8;
RGBColor m_c;
unsigned m_18;
unsigned m_1c;
unsigned m_20;
float m_24;
float m_28;
char pad_2c[4];
char m_30[12];
char m_3c[12];
unsigned m_48;
float m_4c;
float m_50;
float m_54;
float m_58;
float m_5c;
float m_60;
float m_64;
float m_68;
float m_6c;
float m_70;
unsigned m_74;
float m_78;
float m_7c;
float m_80;
bool m_84;
char pad_85[3];
char m_88[8];
int m_90;
float m_94;
float m_98;
Object* m_9c;
unsigned m_a0;
char pad_a4[8];
Rva0041D290Ref<Rva0041D290AudioInfo> m_ac;
unsigned m_b0;
unsigned m_b4;
unsigned m_b8;
char pad_bc[8];
unsigned m_c4;
unsigned m_c8;
unsigned m_cc;
char pad_d0[4];
unsigned m_d4;
DrawableLocoInfo* m_d8;
float m_dc;
bool m_e0;
bool m_e1;
bool m_e2;
bool m_e3;
Rva0041D290Ambient* m_e4;
Rva0041D290Ambient* m_e8;
Rva0041D290Ambient* m_ec;
Rva0041D290DrawModule** m_f0;
char pad_f4[8];
int m_fc;
int m_100;
int m_104;
RvaMatrix m_108;
RvaMatrix m_138;
RvaMatrix m_168;
float m_198;
char pad_19c[68];
unsigned m_1e0;
char pad_1e4[12];
char m_1f0[40];
char m_218[40];
char m_240[40];
float m_268;
char pad_26c[8];
AsciiString m_274;
AsciiString m_278;
unsigned m_27c;
void* m_280;
float m_284;
int m_288;
unsigned m_28c;
int m_290;
int m_294;
Rva0041D290Vector m_298;
unsigned m_2a4;
unsigned m_2a8;
unsigned m_2ac;
unsigned m_2b0;
unsigned m_2b4;
bool m_2b8;
bool m_2b9;
bool m_2ba;
char pad_2bb[146];
bool m_34d;
bool m_34e;
bool m_34f;
bool m_350;
bool m_351;
bool m_352;
bool m_353;
bool m_354;
char pad_355[7];
BuffManager* m_35c;
int m_360;
char m_364[16];
public:
friend class Rva0041D290FullDrawable;
void setID(DrawableID);
void replaceModelConditionState(const ModelConditionFlags&,unsigned,unsigned);
protected:void xferDrawableModules(Xfer*); virtual void xfer(Xfer*); };

// Inline forwarders onto the real Drawable members; they emit no body.
// ?rva00411600@Rva0041D290FullDrawable@@QAEXI@Z absent-from-retail
inline void Rva0041D290FullDrawable::rva00411600(unsigned id){((Drawable*)this)->setID((DrawableID)id);}
// ?rva00417e20@Rva0041D290FullDrawable@@QAEXPAVXfer@@@Z absent-from-retail
inline void Rva0041D290FullDrawable::rva00417e20(Xfer *x){((Drawable*)this)->xferDrawableModules(x);}
// ?rva0041ccd0@Rva0041D290FullDrawable@@QAEXPAX_N1@Z absent-from-retail
inline void Rva0041D290FullDrawable::rva0041ccd0(void *p,bool a,bool b){((Drawable*)this)->replaceModelConditionState(*(ModelConditionFlags*)p,a,b);}
void Drawable::xfer(Xfer *x)
{
 char *p=(char*)this+0x60;
 Xfer::Version version; version.data[0]=1;version.data[1]=4; *x==version;
 if(x->IsLoading()) {
#define KILL(O) if(field<Rva0041D290Ambient*>(p,O)){unsigned handle=field<unsigned>(field<Rva0041D290Ambient*>(p,O),0x10);Rva012ed668->v14(handle);delete field<Rva0041D290Ambient*>(p,O);field<Rva0041D290Ambient*>(p,O)=0;}
 KILL(0xe4) KILL(0xe8) KILL(0xec)
#undef KILL
 }
 unsigned id=m_a0;BfmeParticleSystemXferHandle(*x,&id);
 Rva0041D290FullDrawable *full=(Rva0041D290FullDrawable*)(p-0x60);full->rva00411600(id);
 field<Rva0041D290Condition>(p,0x1f0).rva001cb270(x);field<Rva0041D290Condition>(p,0x218).rva001cb270(x);field<Rva0041D290Condition>(p,0x240).rva001cb270(x);
 RvaMatrix matrix=*full->rva0041cec0();BfmeParticleSystemXferMatrix(*x,&matrix);full->rva00132200(&matrix);
 bool sel=m_4!=0;*x==sel;if(sel){if(!m_4)m_4=new TintEnvelope;*x==field<Snapshot>(m_4,0);}
 bool col=m_8!=0;*x==col;if(col){if(!m_8)m_8=new TintEnvelope;*x==field<Snapshot>(m_8,0);}
 Rva0041D290Decal decal=(Rva0041D290Decal)m_48;*x==reinterpret_cast<unsigned&>(decal);
 if(x->IsLoading()) full->setDecal(decal);
#define F(O) *x==field<float>(p,O);
#define U(O) *x==field<unsigned>(p,O);
#define I(O) *x==field<int>(p,O);
#define B(O) *x==field<bool>(p,O);
 *x==m_4c; *x==m_50; *x==m_54; *x==m_58; *x==m_5c; *x==m_60; *x==m_64; *x==m_68; *x==m_6c; *x==m_74; *x==m_70; *x==m_350; *x==m_78; *x==m_7c; *x==m_80; *x==m_2b0;
 ObjectID oid=m_9c?m_9c->getID():RvaInvalidID;Rva0010C3C0((MidVirtualSlot90Receiver*)x,&oid);
 if(x->IsLoading()){if(m_9c){if(oid!=m_9c->getID())invalidData();}else if(oid)invalidData();}
 *x==m_b0; *x==m_b4; *x==m_b8; x->XferRawBytes(p+0xc4,4);*x==m_c8; *x==m_cc; *x==m_dc;
 bool loco=m_d8!=0;*x==loco;
 if(loco){if(x->IsLoading()&&!m_d8)m_d8=new DrawableLocoInfo;
#define L(O) *x==field<float>(m_d8,O);
 L(4) L(8) L(0xc) L(0x10) L(0x14) L(0x18) L(0x1c) L(0x20) L(0x24) L(0x28) L(0x2c) L(0x30) L(0x3c) L(0x40) L(0x44) L(0x48) L(0x4c)
#undef L
 *x==field<int>(m_d8,0x50);*x==field<int>(m_d8,0x54);
 }
 if(version.data[1]<4)full->rva00417e20(x);
 Rva0010C1C0((MidVirtualSlot90Receiver*)x,p+0xfc);*x==m_100; *x==m_104; *x==m_34d; *x==m_34e; *x==m_284; *x==m_34f;
 BfmeParticleSystemXferMatrix(*x,p+0x138);BfmeParticleSystemXferMatrix(*x,p+0x108);BfmeParticleSystemXferMatrix(*x,p+0x168);
 *x==m_2a4; *x==m_198; Rva0010C3C0((MidVirtualSlot90Receiver*)x,p+0x1e0);*x==m_27c;
 unsigned char icons=0;if(m_280){for(unsigned char i=0;i<14;++i)if(full->rva00410f10()->icon[i])++icons;}*x==icons;
 AsciiString indexName,templateName;unsigned keep;
 if(x->IsStoring()){
  for(unsigned char i=0;i<14;++i){if(!m_280||!full->rva00410f10()->icon[i])continue;
   const char *name=Rva012b4f5c[i];field<StringBase<char> >(&indexName,0).set(name,name?strlen(name):0);*x==indexName;
   keep=full->rva00410f10()->keep[i];*x==keep;
   templateName=full->rva00410f10()->icon[i]->getTemplate()->getName();*x==templateName;
   x->operator==(*reinterpret_cast<Snapshot*>(full->rva00410f10()->icon[i]));
  }
 }else{
  if(m_280)full->rva00410f10()->clear();
  for(int i=0;i<icons;++i){*x==indexName;int index=rvaIconIndex(indexName.str());
   *x==keep;full->rva00410f10()->keep[index]=keep;*x==templateName;Anim2DTemplate*t=Rva012f4ca8->findTemplate(templateName);if(!t)invalidData();
   full->rva00410f10()->icon[index]=new Anim2D(t,Rva012f4ca8);x->operator==(*reinterpret_cast<Snapshot*>(full->rva00410f10()->icon[index]));
  }
 }
 if(x->IsLoading()){m_fc=0;if(m_34d||m_34e)full->rva00411cd0();}
 if(!x->IsStoring())m_353=true;
 *x==m_e0; *x==m_e1; *x==m_e2; *x==m_e3;
 bool custom=m_ac.p!=0;*x==custom;
 if(custom){bool silence=m_ac==rva00415c20();*x==silence;
  if(x->IsLoading()){
   if(silence)full->rva0041abe0();
   else{AsciiString name;*x==name;Rva0041D290Ref<Rva0041D290AudioInfo> base=Rva012ed668->v46(name);Rva0041D290Ref<Rva0041D290AudioInfo> info;bool success=true;
    if(!base.p){info=new Rva0041D290AudioInfo(0);success=false;}else info=new Rva0041D290AudioInfo(*base.p,0);
    full->rva00417330(info);info.p->rva000b5710(x);
    if(success){Rva012ed668->v45(info.p);
     if(field<Rva0041D290Ambient*>(full,0x144)){unsigned handle=field<unsigned>(field<Rva0041D290Ambient*>(full,0x144),0x10);Rva012ed668->v13(handle);}
     if(field<Rva0041D290Ambient*>(full,0x148)){unsigned handle=field<unsigned>(field<Rva0041D290Ambient*>(full,0x148),0x10);Rva012ed668->v13(handle);}
     field<Rva0041D290Ref<Rva0041D290AudioInfo> >(full,0x10c).clear();m_ac=info;
    }
   }
  }else if(!silence){AsciiString name=m_ac.p->rva000b56f0();*x==name;m_ac.p->rva000b5710(x);}
 }
 bool absent=m_e4==0;*x==absent;if(!absent){if(!m_e4)m_e4=new Rva0041D290Ambient;m_e4->event.rva000b2ba0(x);}
 absent=m_e8==0;*x==absent;if(!absent){if(!m_e8)m_e8=new Rva0041D290Ambient;m_e8->event.rva000b2ba0(x);}
 absent=m_ec==0;*x==absent;if(!absent){if(!m_ec)m_ec=new Rva0041D290Ambient;m_ec->event.rva000b2ba0(x);}
 *x==m_290; *x==m_294; *x==m_2a8; *x==m_2ac;

 if(x->IsLoading()){unsigned count;*x==count;while(count--){unsigned value;Rva0010BE80((MidVirtualSlot90Receiver*)x,&value);void *v=Rva012ef4cc->v20(value);m_298.push_back(v);}}
 else{unsigned count=m_298.size();*x==count;for(void **it=m_298.begin();it!=m_298.end();++it){unsigned value=field<unsigned>(*it,4);Rva0010BE80((MidVirtualSlot90Receiver*)x,&value);}}
 *x==m_c;*x==m_18; *x==m_1c; *x==m_20; *x==m_24; *x==m_28; *x==m_2b4; *x==m_2b8; *x==m_2b9; *x==m_360;
 *x==m_274;*x==m_278;*x==m_2ba; *x==m_351; *x==m_354;
 bfmeHandOver_00001A50((BfmeSeedTarget*)x,p+0x30);bfmeHandOver_00001A50((BfmeSeedTarget*)x,p+0x3c);*x==m_84; *x==field<ICoord2D>(p,0x88);*x==m_90; *x==m_94; *x==m_98; *x==m_d4; *x==m_268; *x==m_288; *x==field<IRegion2D>(p,0x364);x->XferRawBytes(p+0x28c,4);
 if(x->IsLoading())full->rva0041ccd0(p+0x1f0,true,true);
 if(version.data[1]>=4)full->rva00417e20(x);
 if(x->IsCRC())return;
 {
  if(version.data[1]>=2){bool has=m_35c!=0;*x==has;if(has){if(x->IsLoading())m_35c=new BuffManager((int)full);m_35c->v03(x);}}
  if(version.data[1]>=3){*x==m_352;}
  if(x->IsLoading()&&m_9c){
   void *t=field<void*>(m_9c,4);if(t&&field<Rva0041D290Override*>(t,4))t=field<Rva0041D290Override*>(t,4)->rva00087a80();
   if(field<unsigned>(t,0xd8)&0x200000){bool found=false;for(Rva0041D290DrawModule **m=m_f0;*m;++m)found|=(*m)->v32();if(found){Rva012ef214->get()->removeObjectFromPathfindMap(m_9c);Rva012ef214->get()->addObjectToPathfindMap(m_9c);}}
  }
 }
}
