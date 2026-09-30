// ?drawGroupNumeral00410F90@Drawable@@QAEXXZ
// partial score=0.5543 date=2026-09-28
// This attempt file keeps its earlier method spelling. The current verdict rejects that identity.
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
struct Group00410F90 {
char pad[9]; bool field09; char pad0a[2]; unsigned field0c,field10; int field14,field18;
union { int int1c; float float1c; }; bool field20; char pad21[3];
union { int int24; float float24; }; bool field28;
};
extern Group00410F90* GroupInfo00410F90;
extern Manager00410F90* ManagerInfo00410F90;
class Drawable {
public:
void drawGroupNumeral00410F90();
char pad[0xfc]; Object* fieldfc; char pad100[0x3c4-0x100]; int field3c4,field3c8,field3cc;
};
#pragma comment(linker, "/alternatename:?getSquadNumberForObject@Player@@QBEHPBVObject@@@Z=?j_000211fc@@YAXXZ")
void Drawable::drawGroupNumeral00410F90() {
Object* obj = fieldfc;
Player* owner = obj->getControllingPlayer();
int groupNum = owner->getSquadNumberForObject(obj);
unsigned color = GroupInfo00410F90->field09 ? owner->field1c4 : GroupInfo00410F90->field0c;
if (groupNum > -1 && groupNum < 10) {
struct { int x,y; } pos = {field3c4,field3c8};
int &xPos=pos.x; int &yPos=pos.y;
if(GroupInfo00410F90->field20) xPos += GroupInfo00410F90->int1c;
else xPos += (field3cc-field3c4)*GroupInfo00410F90->float1c;
if(GroupInfo00410F90->field28) yPos += GroupInfo00410F90->int24;
else yPos += (field3cc-field3c4)*GroupInfo00410F90->float24;
Numeral00410F90* str = ManagerInfo00410F90->numeral(groupNum);
str->colors(color,GroupInfo00410F90->field10);
str->draw(xPos,yPos,GroupInfo00410F90->field14,GroupInfo00410F90->field18);
}
}
