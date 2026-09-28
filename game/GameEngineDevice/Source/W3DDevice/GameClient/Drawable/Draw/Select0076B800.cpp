// cl: /O2 /Ob2 /DNDEBUG /MD
// Retail 0x0076B800: normal thiscall, three stack arguments, boolean result.
// EDI is saved at +0x5b and initialized from m_curState at +0x65, not an input.
// W3DModelDraw+0x14 and Drawable+0xfc names are layout-witnessed by name_oracle.
// Secondary interface at +0xc dispatches slot +0x70; full owner identity unproved.
struct State0076B800 { char pad00[0x44]; void* p44; char pad48[0x24]; bool b6c; };
class Secondary0076B800 { public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void refresh();
};
class BfmeCalc919G { public: int bfmeCalc919G(); };
struct Coord3D; class Matrix3D; class Object;
class BFMERopeDrawableGetPositionShim { public: const Coord3D* get() const; };
class FXList { public: static void doFXPos(const FXList*,const Coord3D*,const Matrix3D*,float,const Coord3D*); };
void bfmeLinkRelation(void*,Object*,int);
class Rva0075BA30Owner { friend class Select0076B800; float getCurrentAnimFraction() const; };
class Rva00766A70W3DScriptedModelDraw { friend class Select0076B800; void apply(void*,int,int,int,int); };
class Cleanup0076B550 { public: void stopParticles(bool); };
extern int g_Va012F8064;
struct Drawable0076B800 { char pad00[0xfc]; Object* m_object; char pad100[0x10]; unsigned char b110; };
class Select0076B800 { public:
 char pad00[8]; Drawable0076B800* p08; Secondary0076B800 secondary;
 char pad10[4]; State0076B800* m_curState;
 char pad18[0x14]; bool b2c; char pad2d[0x1f]; void* p4c; void* p50; void* p54; void* p58; void* p5c;
 char pad60[0x3c]; unsigned int u9c;
 char pada0[0xd0]; bool b170,b171; char pad172[0x8a]; bool b1fc;
 bool select(State0076B800*,bool,int);
};
bool Select0076B800::select(State0076B800* state,bool force,int flags) {
 if(m_curState==state) {
  if(m_curState && m_curState->b6c) { if(force) m_curState=state; else return false; }
  else { if(force) secondary.refresh(); else return false; }
 }
 unsigned int now=g_Va012F8064;
 if(now>u9c) b1fc=false;
 u9c=now;
 if(!(p08->b110&8)) b2c=true;
 ((Cleanup0076B550*)this)->stopParticles(true);
 State0076B800* old=m_curState;
 union { float f; int i; } fraction;
 fraction.f=((Rva0075BA30Owner*)this)->getCurrentAnimFraction();
 m_curState=state;
 ((Rva00766A70W3DScriptedModelDraw*)this)->apply(old,fraction.i,0,0,flags);
 if(m_curState==state) {
  if(state && state->p44) {
   Drawable0076B800* d=p08;
   if(d->m_object) bfmeLinkRelation(state->p44,d->m_object,0);
   else FXList::doFXPos((FXList*)state->p44,((BFMERopeDrawableGetPositionShim*)d)->get(),(Matrix3D*)((BfmeCalc919G*)d)->bfmeCalc919G(),0.0f,0);
  }
  if((p58!=p5c && b171)||(p4c!=p50 && b170)) secondary.refresh();
 }
 return true;
}
