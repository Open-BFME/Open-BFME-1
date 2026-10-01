// RVA 0x00206960: unknown owner; retained address-derived identity.
// Retail witnesses a pointer vector at +4/+8 and 36-byte records with position +8,
// direction +0x14 and occupied ID +0x20. The this pointer may be a subobject.
// Calls: ILT 0x1F253 -> GameLogic::findObjectByID (0x9A510);
// ILT 0x22BB -> Overridable::getFinalOverride (0x87A80). Existing ABI pins reused.
// cl: /DNDEBUG /MD /EHsc
#include <math.h>
struct Position00206960 {
 float x,y,z;
 void scale(float k) { x*=k;y*=k;z*=k; }
 void sub(const Position00206960* p) { x-=p->x;y-=p->y;z-=p->z; }
 float length() const { return (float)sqrt(x*x+y*y+z*z); }
};
class BfmeSubBIA { public: int ask(); };
struct Override00206960 {
 unsigned vptr; BfmeSubBIA* next;
 char pad08[0xd0]; unsigned flagsD8;
 Override00206960* final() { return next ? (Override00206960*)next->ask() : this; }
};
class BfmeX1011 { public: unsigned vptr; Override00206960* data04; char pad08[0x30]; Position00206960 position38;
 Override00206960* data() { Override00206960* p=data04; if(p && p->next) p=(Override00206960*)p->next->ask(); return p; }
};
class BfmeLook1011 { public: BfmeX1011* bfmeFind1011(int); };
// The global at 0x012F0898 is retail's `GameLogic *TheGameLogic`; the lookup below
// goes through this TU's BfmeLook1011 view, cast at the use.
class GameLogic;
extern GameLogic* TheGameLogic;
static inline BfmeLook1011 *g_bfmeLook1011View() { return (BfmeLook1011 *)TheGameLogic; }
struct DockRecord00206960 { int field00; int field04; Position00206960 position08; Position00206960 direction14; int occupied20; };
class NearestPosition00206960 { public:
 unsigned field00; DockRecord00206960** begin04; DockRecord00206960** end08; DockRecord00206960** capacity0C;
 bool find(int id, Position00206960* out);
};
bool NearestPosition00206960::find(int id, Position00206960* out) {
 BfmeX1011* object=g_bfmeLook1011View()->bfmeFind1011(id);
 if(!object) return false;
 unsigned count=end08-begin04;
 if(!count) return false;
 int best=-1;
 float distance=99999.0f;
 for(unsigned i=0;i<count;++i) {
  DockRecord00206960* entry=begin04[i];
  if(entry->occupied20) continue;
  if(!(object->data()->flagsD8 & 0x400) && entry->field04!=0) continue;
  Position00206960 position; position.x=entry->position08.x; position.y=entry->position08.y; position.z=entry->position08.z;
  Position00206960 direction; direction.x=entry->direction14.x; direction.y=entry->direction14.y; direction.z=entry->direction14.z;
  direction.scale(30.0f);
  position.sub(&direction);
  float dx=position.x-object->position38.x;
  float dy=position.y-object->position38.y;
  float dz=position.z-object->position38.z;
  float d=(float)sqrt(dx*dx+dy*dy+dz*dz);
  if(d<distance) { distance=d; best=i; *out=position; }
 }
 if(best>=0) return true; return false;
}





