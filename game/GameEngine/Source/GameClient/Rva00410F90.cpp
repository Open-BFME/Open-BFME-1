// cl: /DNDEBUG /MD /EHsc
// Retail 0x00410F90: opaque Drawable view for group-label placement.
// The tagged offset words are copied to integers with memcpy, never union-punned.
#include <string.h>
static __forceinline int asInt(const float &bits) { int value; memcpy(&value,&bits,4); return value; }
// ?method@Rva00410F90@@QAEXXZ
// Retail body at RVA 0x00410F90. Its method name is unproven.
class Player { public: int getSquadNumberForObject(const class Object*) const; char pad[0x1c4]; unsigned field1c4; };
class Object { public: Player* getControllingPlayer() const; };
class Numeral00410F90 {
public:
#define SLOT(n) virtual void slot##n();
SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9)
virtual void colors(unsigned, unsigned);
SLOT(11) SLOT(12) SLOT(13)
virtual void draw(int,int,int,int);
};
class Manager00410F90 {
public:
SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10)
virtual Numeral00410F90* numeral(int);
};
#undef SLOT
struct Group00410F90 {
char pad[9]; bool field09; char pad0a[2]; unsigned field0c,field10; int field14,field18;
float float1c; bool field20; char pad21[3];
float float24; bool field28;
};
struct DrawGroupInfo;
extern DrawGroupInfo *TheDrawGroupInfo;
class DisplayStringManager;
extern DisplayStringManager *TheDisplayStringManager;
class Rva00410F90 {
public:
void method();
char pad[0xfc]; Object* fieldfc; char pad100[0x3c4-0x100]; volatile int field3c4; int field3c8,field3cc;
};
void Rva00410F90::method() {
Object* obj = fieldfc;
Player* owner = obj->getControllingPlayer();
int groupNum = owner->getSquadNumberForObject(obj);
unsigned color = ((Group00410F90 *)TheDrawGroupInfo)->field09 ? owner->field1c4 : ((Group00410F90 *)TheDrawGroupInfo)->field0c;
if (groupNum > -1 && groupNum < 10) {
int xPos=field3c4; int yPos=field3c8;
if(((Group00410F90 *)TheDrawGroupInfo)->field20) xPos += asInt(((Group00410F90 *)TheDrawGroupInfo)->float1c);
else { int delta=field3cc; delta-=field3c4; xPos += delta*((Group00410F90 *)TheDrawGroupInfo)->float1c; }
if(((Group00410F90 *)TheDrawGroupInfo)->field28) yPos += asInt(((Group00410F90 *)TheDrawGroupInfo)->float24);
else { int lo=field3c4; yPos += (field3cc-lo)*((Group00410F90 *)TheDrawGroupInfo)->float24; }
Numeral00410F90* str = ((Manager00410F90 *)TheDisplayStringManager)->numeral(groupNum);
str->colors(color,((Group00410F90 *)TheDrawGroupInfo)->field10);
str->draw(xPos,yPos,((Group00410F90 *)TheDrawGroupInfo)->field14,((Group00410F90 *)TheDrawGroupInfo)->field18);
}
}
