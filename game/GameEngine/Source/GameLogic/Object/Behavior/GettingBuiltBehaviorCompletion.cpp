// cl: /DNDEBUG /MD /EHsc
// Retail 0x001FF5C0, 555 bytes. The matched GettingBuiltBehavior::update
// calls this helper through ILT 0x00035EE0. The primary object/data and
// secondary-interface offsets agree with GettingBuiltBehaviorRva001FF360.
// Remaining slot/field names deliberately retain offsets: no semantic guess.
// The 0x00002B49 route consumes thiscall + three stack arguments; its matched
// body reads the position argument as a pointer despite its old integer name.
class Object;
struct Coord3D;
#include "../../command_source_type.h"
class GameLogic { public: Object *findObjectByID(int); };
extern GameLogic *TheGameLogic;
class Body001FF5C0 { public:
virtual void slot00();
virtual void slot04();
virtual void slot08();
virtual void slot0c();
virtual float slot10();
virtual void slot14();
virtual float slot18();
};
class BfmeHelpD820 { public: void bfmeGoD820(Object *, const Coord3D *, int); };
class AICommandInterface { public: void aiMoveToPosition(const Coord3D *, CommandSourceType); };
class AIUpdateInterface { public:
virtual void slot000();
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
virtual bool slot180();
char pad004[0x1cc-4]; BfmeHelpD820 *field1cc;
void ignoreObstacle(const Object *);
};
class Object { public:
char pad000[0x7c]; int m_builderID;
char pad080[0xbc-0x80]; float field0bc;
char pad0c0[0x110-0xc0]; unsigned int flags[4];
char pad120[0x200-0x120]; Body001FF5C0 *field200; AIUpdateInterface *field204;
char pad208[0x220-0x208]; union { float field220; unsigned int bits220; };
void notifyModelConditionChanged(); void setBuilder(const Object *);
__forceinline const Coord3D *position() const { return (const Coord3D *)((const char *)this+0x38); }
__forceinline void clear(unsigned int word, unsigned int mask) { if(((unsigned char *)flags)[word*4]&(unsigned char)mask) { flags[word]&=~mask; notifyModelConditionChanged(); } }
__forceinline void set(unsigned int word, unsigned int mask) { if(!(((unsigned char *)flags)[word*4]&(unsigned char)mask)) { flags[word]|=mask; notifyModelConditionChanged(); } }
};
class Gen_000ED3B0 { public: float bfmeGapSq(const Gen_000ED3B0 *) const; };
class Secondary001FF5C0 { public:
virtual void slot00();
virtual void slot04();
virtual void slot08();
virtual void slot0c(Object *);
virtual void slot10();
virtual bool slot14();
virtual void slot18();
virtual void slot1c();
virtual void slot20();
virtual void slot24();
virtual bool slot28();
};
struct Data001FF5C0 { char pad00[0x20]; unsigned int field20; };
class GettingBuiltBehavior { public:
void *vptr; Data001FF5C0 *field04; Object *m_object; char pad0c[0x20-0xc]; Secondary001FF5C0 secondary;
unsigned int field24, field28, field2c; bool field30,field31,field32,field33,field34,field35,field36;
void rva001FF5C0();
};
void GettingBuiltBehavior::rva001FF5C0()
{
 Object *object=m_object;
 Body001FF5C0 *body=object->field200;
 if(!body) return;
 Object *builder=TheGameLogic->findObjectByID(object->m_builderID);
 if ((secondary.slot28() || body->slot10() >= body->slot18()) &&
     (object->field220 >= 100.0f || object->bits220 == 0xbf800000)) {
  object->setBuilder(builder);
  if(builder && builder->field204 && builder!=object) {
   builder->field204->ignoreObstacle(object);
   ((AICommandInterface *)((char *)builder->field204+0x20))->aiMoveToPosition(object->position(),CMD_FROM_AI);
   field30=true;
  }
  object->clear(0,8); object->clear(0,16); object->clear(2,4); object->clear(2,16); object->clear(2,8);
  if(secondary.slot14()) secondary.slot0c(0);
  field28=field04->field20; field33=true; field36=false;
 } else if(!field33 && !field30 && builder && builder!=object && builder->field204 && builder->field204->slot180()) {
  float radius=builder->field0bc*1.5f;
  if(((Gen_000ED3B0 *)object)->bfmeGapSq((Gen_000ED3B0 *)builder)>radius*radius) builder->set(3,8);
  builder->field204->field1cc->bfmeGoD820(builder,object->position(),0);
 }
}




