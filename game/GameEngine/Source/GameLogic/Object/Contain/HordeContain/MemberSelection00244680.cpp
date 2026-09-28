// Retail 0x00244680 complete 624-byte thiscall ending ret 0x58; address-qualified identity.
// Receiver is the HordeContain secondary interface: UpdateModule at this-0xe4, member list at this-0xac.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath
// stlport
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>
#include "coord.h"
extern void j_00034a54();
extern int GetGameLogicRandomValue(int,int,char *,int);
extern float Rva0002CCA5GetGameLogicRandomValueRealThunk(float,float,char *,int);
enum UpdateSleepTime {UPDATE_SLEEP_NONE=1};
class Object;
class Update00244680;
class UpdateModule {
protected: void setWakeFrame(Object *,UpdateSleepTime);
 friend class Update00244680;
};
class BfmeSubDSU {public: void **bfmeTwoDSU(void **what);};
struct Packet00244680 {int words[10];};
class Member00244680 {public: char pad000[0x38]; Coord3D position; char pad044[0x74-0x44]; int field074;};
struct TreeNode00244680 {int color;TreeNode00244680 *parent,*left,*right;};
class Map00244680 {public: TreeNode00244680 *head;unsigned count;
 void erase(TreeNode00244680 *node) {union {void (*p)();void (Map00244680::*m)(TreeNode00244680 *);} c;c.p=j_00034a54;(this->*c.m)(node);}
 void clear() {if(count) {erase(head->parent);head->left=head;head->parent=0;head->right=head;count=0;}}
 int &lookup(const int &key) {return *(int *)((BfmeSubDSU *)this)->bfmeTwoDSU((void **)&key);}
};
class Update00244680 {public: void wake(Member00244680 *o,int t) {((UpdateModule *)this)->setWakeFrame((Object *)o,(UpdateSleepTime)t);}};
class MemberSelection00244680 {public:
 virtual void unused0()=0;
 virtual void unused1()=0;
 virtual void unused2()=0;
 virtual void unused3()=0;
 virtual void unused4()=0;
 virtual void unused5()=0;
 virtual void unused6()=0;
 virtual void unused7()=0;
 virtual void unused8()=0;
 virtual void unused9()=0;
 virtual void unused10()=0;
 virtual void unused11()=0;
 virtual void unused12()=0;
 virtual void unused13()=0;
 virtual void unused14()=0;
 virtual void unused15()=0;
 virtual void unused16()=0;
 virtual void unused17()=0;
 virtual void unused18()=0;
 virtual void unused19()=0;
 virtual void unused20()=0;
 virtual void unused21()=0;
 virtual void unused22()=0;
 virtual void unused23()=0;
 virtual void unused24()=0;
 virtual void unused25()=0;
 virtual void unused26()=0;
 virtual void unused27()=0;
 virtual void unused28()=0;
 virtual void unused29()=0;
 virtual void unused30()=0;
 virtual void unused31()=0;
 virtual void unused32()=0;
 virtual void unused33()=0;
 virtual void unused34()=0;
 virtual void unused35()=0;
 virtual void unused36()=0;
 virtual void unused37()=0;
 virtual void unused38()=0;
 virtual void unused39()=0;
 virtual void unused40()=0;
 virtual void unused41()=0;
 virtual void unused42()=0;
 virtual void unused43()=0;
 virtual void unused44()=0;
 virtual void unused45()=0;
 virtual void unused46()=0;
 virtual void unused47()=0;
 virtual void unused48()=0;
 virtual void unused49()=0;
 virtual void unused50()=0;
 virtual void unused51()=0;
 virtual void unused52()=0;
 virtual void unused53()=0;
 virtual void unused54()=0;
 virtual void unused55()=0;
 virtual void unused56()=0;
 virtual void unused57()=0;
 virtual void unused58()=0;
 virtual void unused59()=0;
 virtual void unused60()=0;
 virtual void unused61()=0;
 virtual void unused62()=0;
 virtual void unused63()=0;
 virtual void unused64()=0;
 virtual void unused65()=0;
 virtual void unused66()=0;
 virtual void unused67()=0;
 virtual void unused68()=0;
 virtual void unused69()=0;
 virtual void unused70()=0;
 virtual void unused71()=0;
 virtual void unused72()=0;
 virtual void unused73()=0;
 virtual void unused74()=0;
 virtual void unused75()=0;
 virtual void unused76()=0;
 virtual void unused77()=0;
 virtual void unused78()=0;
 virtual void unused79()=0;
 virtual void unused80()=0;
 virtual void unused81()=0;
 virtual void unused82()=0;
 virtual void unused83()=0;
 virtual void unused84()=0;
 virtual void unused85()=0;
 virtual void unused86()=0;
 virtual void unused87()=0;
 virtual void unused88()=0;
 virtual void unused89()=0;
 virtual void unused90()=0;
 virtual void unused91()=0;
 virtual void unused92()=0;
 virtual void unused93()=0;
 virtual void unused94()=0;
 virtual void slot17C()=0;
 char pad004[0x6c-4];int field06C,field070;Packet00244680 field074,field09C;Map00244680 field0C4;
 void select(int low,int high,Packet00244680 packetA,Packet00244680 packetB);
};
void MemberSelection00244680::select(int low,int high,Packet00244680 packetA,Packet00244680 packetB) {
 field0C4.clear();
 _STL::list<Member00244680 *> &members=*(_STL::list<Member00244680 *> *)((char *)this-0xac);
 int count=members.size();
 if(count<2) return;
 int closest=-1;
 Coord3D center;center.zero();
 float best=10000.0f;
 int index=1;
 for(_STL::list<Member00244680 *>::iterator it=members.begin();it!=members.end();++it) {
  Member00244680 *member=*it;
  if(!member) {slot17C();return;}
  center.add(&member->position);
 }
 center.scale(1.0f/count);
 for(_STL::list<Member00244680 *>::iterator it=members.begin();it!=members.end();++it,++index) {
  Member00244680 *member=*it;
  if(!member) {slot17C();return;}
  Coord3D diff;diff.set(&member->position);diff.sub(&center);
  float distance=diff.x*diff.x+diff.y*diff.y;
  if(distance<best) {closest=index;best=distance;}
 }
 int leader=closest;
 if(leader==-1) leader=1;
 int other=leader+GetGameLogicRandomValue(1,count-1,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp",0x1b34);
 if(other>count) other-=count;
 field074=packetB;field09C=packetA;
 index=1;
 for(_STL::list<Member00244680 *>::iterator it=members.begin();it!=members.end();++it,++index) {
  Member00244680 *member=*it;
  if(!member) {slot17C();return;}
  if(index==other) field06C=member->field074;
  else if(index==leader) field070=member->field074;
  else {int id=member->field074;int &value=field0C4.lookup(id);
   value=(int)Rva0002CCA5GetGameLogicRandomValueRealThunk((float)low,(float)high,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp",0x1b4f);
  }
 }
 ((Update00244680 *)((char *)this-0xe4))->wake(*(Member00244680 **)((char *)this-0xdc),1);
}

