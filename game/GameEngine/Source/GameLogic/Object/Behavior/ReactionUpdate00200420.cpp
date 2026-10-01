// RVA 0x00200420; update-interface this pointer; original owner unproved.
// Retail this-8 Object and this-12 data pointers are accessed explicitly.
// Object model-condition interior word +0x124 and status +0x344 witnessed in retail.
// AI slot +0x180 and body slot +0x10 retain neutral names.
// Bit-test callee 0x000D2F40 is independently decoded and takes one unsigned index.
// cl: /DNDEBUG /MD /EHsc
struct WordBitTest000D2F40 { bool test(unsigned index) const; };
class DrawableApplyPendingThunk { public: void apply(bool); };
struct Drawable00200420 { char pad00[0x250]; WordBitTest000D2F40 conditions250; };
class Body00200420 { public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual float value10();
};
class AI00200420 { public:
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
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual void slot72();
 virtual void slot73();
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual void slot77();
 virtual void slot78();
 virtual void slot79();
 virtual void slot80();
 virtual void slot81();
 virtual void slot82();
 virtual void slot83();
 virtual void slot84();
 virtual void slot85();
 virtual void slot86();
 virtual void slot87();
 virtual void slot88();
 virtual void slot89();
 virtual void slot90();
 virtual void slot91();
 virtual void slot92();
 virtual void slot93();
 virtual void slot94();
 virtual void slot95();
 virtual bool predicate180();
};
class BfmeInterface001BF6B0 { public: virtual void slot0(); virtual void slot1(); virtual void slot2(int); };
enum DisabledType { Disabled00200420=4 };
class Object { public:
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
 virtual Drawable00200420* drawable28();
 char pad04[0x120]; unsigned flags124; char pad128[0xd8];
 Body00200420* body200; AI00200420* ai204; char pad208[0x13c]; unsigned status344;
 void notifyModelConditionChanged();
 BfmeInterface001BF6B0* queryInterfaceRva001BF6B0();
 void setDisabledUntil(DisabledType,unsigned);
 template<int bit> void clearBit() { if(*(unsigned char*)&flags124 & (1u<<bit)) { flags124 &= ~(1u<<bit); notifyModelConditionChanged(); } }
 template<int bit> __forceinline void setBit() { if(!(*(unsigned char*)&flags124 & (1u<<bit))) { flags124 |= 1u<<bit; notifyModelConditionChanged(); } }
};
struct ReactionData00200420 { char pad00[8]; int counts08[3]; float thresholds14[3]; bool flag20,flag21; };
struct Frame00200420 { char pad00[0x3c]; unsigned frame3C; };
class GameLogic;
extern GameLogic *TheGameLogic;
static inline Frame00200420 *frameView00200420() { return (Frame00200420 *)TheGameLogic; }
class ReactionUpdate00200420 { public:
 int update(); char pad00[0x10]; int count10; float previous14;
 Object* object() { return *(Object**)((char*)this-8); }
 ReactionData00200420* data() { return *(ReactionData00200420**)((char*)this-12); }
};
__forceinline void clearReaction00200420(Object* object,Drawable00200420* drawable) {
 object->clearBit<2>(); object->clearBit<3>(); object->clearBit<4>(); object->clearBit<5>();
 ((DrawableApplyPendingThunk*)drawable)->apply(false);
}
int ReactionUpdate00200420::update() {
 Object* obj=object();
 AI00200420* ai=obj->ai204;
 Body00200420* body=obj->body200;
 Drawable00200420* drawable=obj->drawable28();
 ReactionData00200420* settings=data();
 if(ai && drawable && body) {
 float current=body->value10();
 bool active=count10>0;
 if(active) {
  --count10;
  if(count10<=0 || (obj->status344&1) || !ai->predicate180()) {
   if(*(unsigned*)((char*)drawable+0x264)&4) clearReaction00200420(obj,drawable);
   count10=0;
  }
 }
 if(!active || settings->flag20) {
  if((ai->predicate180() || settings->flag21) && current<previous14) {
   if(drawable->conditions250.test(162)) clearReaction00200420(obj,drawable);
   float difference=previous14-current;
   int level;
   if(difference>=settings->thresholds14[2]) level=2;
   else if(difference>=settings->thresholds14[1]) level=1;
   else if(difference>=settings->thresholds14[0]) level=0;
   else goto done;
   count10=settings->counts08[level];
   if(count10>0 && !drawable->conditions250.test(162)) {
    obj->setBit<2>();
    switch(level) { case 0: obj->setBit<3>();break; case 1: obj->setBit<4>();break; case 2: obj->setBit<5>();break; }
    BfmeInterface001BF6B0* interface=obj->queryInterfaceRva001BF6B0();
    if(interface) interface->slot2(0);
    if(settings->flag21) obj->setDisabledUntil(Disabled00200420,frameView00200420()->frame3C+count10);
    ((DrawableApplyPendingThunk*)drawable)->apply(false);
   }
  }
 }
done:
 previous14=current;
 if(!(obj->status344&1)) return 1;
 }
 return 0x3fffffff;
}




