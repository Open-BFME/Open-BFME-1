// cl: /O2 /Ob2 /DNDEBUG /MD
// Retail 0x0076B6E0: W3DScriptedModelDraw primary vtable slot 20 (ILT
// 0x00002180; owner proof in targets/game/reverse/identity_evidence/
// 0076b6e0-w3dscriptedmodeldraw-radius-decal.md). It copies the radius-decal
// template into +0x188 and refreshes the decal colour through slot 24. The
// method spelling is unknown, so the view keeps the address.
enum KindOfType { KINDOF_7 = 7 };
struct Rva0076B6E0Drawable;
class Thing
{
public:
 virtual void thingSlot00();
 virtual void thingSlot01();
 virtual void thingSlot02();
 virtual void thingSlot03();
 virtual void thingSlot04();
 virtual void thingSlot05();
 virtual void thingSlot06();
 virtual void thingSlot07();
 virtual void thingSlot08();
 virtual void thingSlot09();
 virtual Rva0076B6E0Drawable *thingSlot10() const;
 bool isKindOf(KindOfType kind) const;
};
class Object : public Thing
{
public:
 int bfmeGetHordeMemberCount() const;
 Object *bfmeResolveMeleeTarget(int which);
 void *unidentified_001BFE20() const;
};
class ObjectAttemptDamageFlagHook
{
public:
 int value();
};
class Rva0076B6E0ColorSource
{
public:
 virtual void colorSlot00();
 virtual void colorSlot01();
 virtual void colorSlot02();
 virtual void colorSlot03();
 virtual void colorSlot04();
 virtual void colorSlot05();
 virtual void colorSlot06();
 virtual void colorSlot07();
 virtual void colorSlot08();
 virtual void colorSlot09();
 virtual void colorSlot10();
 virtual void colorSlot11();
 virtual void colorSlot12();
 virtual void colorSlot13();
 virtual void colorSlot14();
 virtual void colorSlot15();
 virtual void colorSlot16();
 virtual void colorSlot17();
 virtual void colorSlot18();
 virtual void colorSlot19();
 virtual void colorSlot20();
 virtual void colorSlot21();
 virtual void colorSlot22();
 virtual void colorSlot23();
 virtual void colorSlot24();
 virtual void colorSlot25();
 virtual void colorSlot26();
 virtual void colorSlot27();
 virtual void colorSlot28();
 virtual void colorSlot29();
 virtual void colorSlot30();
 virtual void colorSlot31();
 virtual void colorSlot32();
 virtual void colorSlot33();
 virtual void colorSlot34();
 virtual void colorSlot35();
 virtual void colorSlot36();
 virtual void colorSlot37();
 virtual void colorSlot38();
 virtual void colorSlot39();
 virtual void colorSlot40();
 virtual void colorSlot41();
 virtual void colorSlot42();
 virtual void colorSlot43();
 virtual void colorSlot44();
 virtual void colorSlot45();
 virtual void colorSlot46();
 virtual void colorSlot47();
 virtual void colorSlot48();
 virtual void colorSlot49();
 virtual void colorSlot50();
 virtual void colorSlot51();
 virtual void colorSlot52();
 virtual void colorSlot53();
 virtual void colorSlot54();
 virtual void colorSlot55();
 virtual void colorSlot56();
 virtual void colorSlot57();
 virtual void colorSlot58();
 virtual void colorSlot59();
 virtual void colorSlot60();
 virtual void colorSlot61();
 virtual void colorSlot62();
 virtual void colorSlot63();
 virtual void colorSlot64();
 virtual void colorSlot65();
 virtual void colorSlot66();
 virtual void colorSlot67();
 virtual void colorSlot68();
 virtual void colorSlot69();
 virtual void colorSlot70();
 virtual void colorSlot71();
 virtual void colorSlot72();
 virtual void colorSlot73();
 virtual void colorSlot74();
 virtual void colorSlot75();
 virtual void colorSlot76();
 virtual void colorSlot77();
 virtual void colorSlot78();
 virtual void colorSlot79();
 virtual void colorSlot80();
 virtual void colorSlot81();
 virtual void colorSlot82();
 virtual void colorSlot83();
 virtual void colorSlot84();
 virtual void colorSlot85();
 virtual void colorSlot86();
 virtual void colorSlot87();
 virtual void colorSlot88();
 virtual int colorSlot89(Object *object);
};
struct Rva0076B6E0Drawable
{
 char m_pad000[0xfc];
 Object *m_object;
 char m_pad100[0x3ac - 0x100];
 bool m_flag3ac;
};
class GlobalData
{
public:
 char m_pad000[0xa76];
 bool m_flagA76;
};
// The defined global is ?TheWritableGlobalData@@3PAVGlobalData@@A (data_rows).
extern GlobalData *TheWritableGlobalData;
class RadiusDecalTemplate
{
public:
 void operator=(const RadiusDecalTemplate &other);
 char m_pad[0x40];
};
class Rva0076B6E0View
{
public:
 virtual void drawSlot00();
 virtual void drawSlot01();
 virtual void drawSlot02();
 virtual void drawSlot03();
 virtual void drawSlot04();
 virtual void drawSlot05();
 virtual void drawSlot06();
 virtual void drawSlot07();
 virtual void drawSlot08();
 virtual void drawSlot09();
 virtual void drawSlot10();
 virtual void drawSlot11();
 virtual void drawSlot12();
 virtual void drawSlot13();
 virtual void drawSlot14();
 virtual void drawSlot15();
 virtual void drawSlot16();
 virtual void drawSlot17();
 virtual void drawSlot18();
 virtual void drawSlot19();
 virtual void drawSlot20();
 virtual void drawSlot21();
 virtual void drawSlot22();
 virtual void drawSlot23();
 virtual void drawSlot24(int mode, int color);
 void rva0076B6E0(const RadiusDecalTemplate *decal);
 int m_field04;
 Rva0076B6E0Drawable *m_drawable;
 char m_pad0c[0x188 - 0x0c];
 RadiusDecalTemplate m_decal;
};
// ?rva0076B6E0@Rva0076B6E0View@@QAEXPBVRadiusDecalTemplate@@@Z
void Rva0076B6E0View::rva0076B6E0(const RadiusDecalTemplate *decal)
{
 if (decal == 0)
  return;
 m_decal = *decal;
 Rva0076B6E0Drawable *drawable = m_drawable;
 Object *object = drawable->m_object;
 if (object == 0 || object->isKindOf(KINDOF_7))
  return;
 if (TheWritableGlobalData->m_flagA76)
 {
  if (drawable->m_flag3ac)
   drawSlot24(object->bfmeGetHordeMemberCount(), ((ObjectAttemptDamageFlagHook *)object)->value());
  return;
 }
 Object *other = object->bfmeResolveMeleeTarget(0);
 bool otherShown = false;
 int color = ((ObjectAttemptDamageFlagHook *)object)->value();
 if (other != 0)
 {
  Rva0076B6E0Drawable *otherDrawable = other->thingSlot10();
  if (otherDrawable != 0 && otherDrawable->m_flag3ac)
  {
   otherShown = true;
   Rva0076B6E0ColorSource *source = (Rva0076B6E0ColorSource *)other->unidentified_001BFE20();
   if (source != 0)
    color = source->colorSlot89(other);
  }
 }
 if (m_drawable->m_flag3ac || otherShown)
  drawSlot24(1, color);
}

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
class FXList { public:
 static void doFXObj(const FXList*,const Object*,const Object*);
 static void doFXPos(const FXList*,const Coord3D*,const Matrix3D*,float,const Coord3D*);
};
class Rva0075BA30Owner { friend class Select0076B800; float getCurrentAnimFraction() const; };
// The transition call goes through ILT 0x00001CA8, the ledger's 5-byte row
// ?j_00001ca8@@YAXXZ (game/gen_small/thunks_000.cpp), as tools/callees.py
// 0x76b800 299 prints.  Nothing defines the pinned
// ?apply@Rva00766A70W3DScriptedModelDraw@@AAEXPAXHHHH@Z, so the call names the
// thunk through a raw pointer bridge that keeps the thiscall shape.
void j_00001ca8();
class Rva00766A70W3DScriptedModelDraw {};
class Cleanup0076B550 { public: void stopParticles(bool); };
extern unsigned int g_rva0075b2e0_value;
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
 unsigned int now=g_rva0075b2e0_value;
 if(now>u9c) b1fc=false;
 u9c=now;
 if(!(p08->b110&8)) b2c=true;
 ((Cleanup0076B550*)this)->stopParticles(true);
 State0076B800* old=m_curState;
 union { float f; int i; } fraction;
 fraction.f=((Rva0075BA30Owner*)this)->getCurrentAnimFraction();
 m_curState=state;
 union { void (*raw)(void); void (Rva00766A70W3DScriptedModelDraw::*typed)(void*,int,int,int,int); } apply;
 apply.raw = &j_00001ca8;
 (((Rva00766A70W3DScriptedModelDraw*)this)->*apply.typed)(old,fraction.i,0,0,flags);
 if(m_curState==state) {
  if(state && state->p44) {
   Drawable0076B800* d=p08;
   if(d->m_object) FXList::doFXObj((const FXList*)state->p44,d->m_object,0);
   else FXList::doFXPos((FXList*)state->p44,((BFMERopeDrawableGetPositionShim*)d)->get(),(Matrix3D*)((BfmeCalc919G*)d)->bfmeCalc919G(),0.0f,0);
  }
  if((p58!=p5c && b171)||(p4c!=p50 && b170)) secondary.refresh();
 }
 return true;
}
