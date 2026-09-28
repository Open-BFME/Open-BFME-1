// Retail 0x00251530..0x00251630: complete ret-4 body.
// Address-qualified damage-interface view; weapon-name comparison selects
// containment evacuation or the witnessed EvacuateDamage::onDamage fallback.
// Existing name/compare pins are reused with their witnessed ABI; compare
// is nonthrowing (retail 0x5FEB0), so the temporary needs no EH cleanup frame.
// cl: /DNDEBUG /MD /EHsc- /Igame/GameEngine/Source /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
#include "GameLogic/Object/object.h"
extern void j_0001f253(); extern void j_00031a7f();
extern void j_0003251f(); extern void j_00007bcb();
extern void j_0000a5dd(); extern void j_0001bcc5();
class Route00251530 {};
class Rva0016F9E0WeaponNameShim {public: AsciiString getName() const;};
class BfmeSubCW {public: int bfmeCheckCW(void*) throw();};
__forceinline bool equal00251530(AsciiString &a,const AsciiString &b) {return ((BfmeSubCW*)&a)->bfmeCheckCW((void*)&b)==0;}
extern Route00251530 *g00251530Va012F0898;
struct Damage00251530 {char at000[8]; int at008; char at00c[4]; int at010;};
struct Data00251530 {char at000[8]; AsciiString at008; int at00c;};
struct Node00251530 {Node00251530 *next,*prev; Object *object;};
struct List00251530 {Node00251530 *head;};
template<int N> class Slots00251530 : public Slots00251530<N-1> { public: virtual void unused(char (*)[N])=0; };
template<> class Slots00251530<0> {};
class Contain00251530 : public Slots00251530<24> {
public: virtual int slot060()=0;
 virtual void slot064()=0; virtual void slot068()=0;
 virtual void slot06c(int)=0;
 virtual void slot070()=0;
 virtual void slot074()=0;
 virtual void slot078()=0;
 virtual void slot07c()=0;
 virtual void slot080()=0;
 virtual void slot084()=0;
 virtual void slot088()=0;
 virtual void slot08c()=0;
 virtual void slot090()=0;
 virtual void slot094()=0;
 virtual void slot098()=0;
 virtual void slot09c()=0;
 virtual void slot0a0()=0;
 virtual void slot0a4()=0;
 virtual void slot0a8()=0;
 virtual void slot0ac()=0;
 virtual void slot0b0()=0;
 virtual void slot0b4()=0;
 virtual void slot0b8()=0;
 virtual void slot0bc()=0;
 virtual void slot0c0()=0;
 virtual void slot0c4()=0;
 virtual void slot0c8()=0;
 virtual void slot0cc()=0;
 virtual void slot0d0()=0;
 virtual void slot0d4()=0;
 virtual void slot0d8()=0;
 virtual void slot0dc()=0;
 virtual void slot0e0()=0;
 virtual void slot0e4()=0;
 virtual void slot0e8()=0;
 virtual void slot0ec()=0;
 virtual void slot0f0()=0;
 virtual void slot0f4()=0;
 virtual void slot0f8()=0;
 virtual void slot0fc()=0;
 virtual void slot100()=0;
 virtual List00251530 *slot104()=0;
};
class WeaponEvacuate00251530 {public: void run(Damage00251530 *damage);};
void WeaponEvacuate00251530::run(Damage00251530 *damage) {
 Data00251530 *data=*(Data00251530**)((char*)this-12);
 typedef Object *(Route00251530::*Find)(int);
 union {void (*fn)(); Find call;} find={j_0001f253};
 Object *source=(g00251530Va012F0898->*find.call)(damage->at008);
 if(!source) return;
 typedef Route00251530 *(Route00251530::*Weapon)(void*);
 union {void (*fn)(); Weapon call;} weaponCall={j_00031a7f};
 Route00251530 *weapon=(((Route00251530*)source)->*weaponCall.call)(0);
 if(!weapon) return;
 if(equal00251530(data->at008,((Rva0016F9E0WeaponNameShim*)weapon)->getName())) {
  Contain00251530 *contain=(Contain00251530*)(*(Object**)((char*)this-8))->m_contain;
  if(!contain) return;
  if(!contain->slot060()) {contain->slot06c(2);return;}
  List00251530 *list=contain->slot104();
  for(Node00251530 *it=list->head->next;it!=list->head;it=it->next) {
   Object *member=it->object;
   typedef bool (Route00251530::*Kind)(int);
   union {void (*fn)(); Kind call;} kind={j_0003251f};
   typedef void (Route00251530::*Command)(Object*,int);
   if((((Route00251530*)member)->*kind.call)(108)) {
    union {void (*fn)(); Command call;} command={j_00007bcb};
    (((Route00251530*)((char*)member->m_ai+0x20))->*command.call)(*(Object**)((char*)this-8),2);
   } else {
    union {void (*fn)(); Command call;} command={j_0000a5dd};
    (((Route00251530*)((char*)member->m_ai+0x20))->*command.call)(*(Object**)((char*)this-8),2);
   }
  }
 } else if(data->at00c==damage->at010) {
  typedef void (Route00251530::*Fallback)(Damage00251530*);
  union {void (*fn)(); Fallback call;} fallback={j_0001bcc5};
  (((Route00251530*)((char*)this-16))->*fallback.call)(damage);
 }
}
