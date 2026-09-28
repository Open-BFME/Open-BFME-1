// ?checkMember@HordeContainOwner@@QAE_NPAVObject@@@Z
// partial score=0.5771929825 date=2026-09-28
// ?checkMember@HordeContainOwner@@QAE_NPAVObject@@@Z
// Corrects old stash: nonzero model-condition bit cf REJECTS. Virtual slot 68
// receiver is the secondary interface itself; data -e0 supplies filter addresses.
// Virtual arguments are candidate/field d0 or d8/filter/false. First success
// returns true; second success with tracker+28<=1 also returns true. String
// branch uses RESOLVED object template, native AsciiString by value to lookup
// at primary this-e4, then excludes four status checks (not veterancy).
// Real method/owner still unproven; old stash name is retained for continuity.
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameLogic/Object
// Retail 0x0023CAA0. Corrected from banked guard-chain attempt.
#include "ascii_string.h"
typedef bool Bool;
typedef int Int;
class Player;
enum KindOfType { Kind0023CAA0=11 };
#define THING_TU_MEMBERS const ThingTemplate *getTemplate() const; bool isKindOf(KindOfType) const;
#define OBJECT_TU_MEMBERS Player *getControllingPlayer() const; bool testStatus(int) const;
#include "object.h"
class Rva000D3F10 { public: int test(unsigned); };
struct RvaC4390First;
class RvaC4390Second { public: RvaC4390First *resolve(int); };
struct Rva00238740Entry;
class Rva00238740Lookup { public: Rva00238740Entry *find(AsciiString name); };
// Placeholder virtual call surface on the object reached through this-0xe0:
// slot 0x68 called twice with different argument packs, at member offsets
// +0x28c and +0x2b0.
class HordeContainOwner
{
public:
	virtual void pad00(); virtual void pad04(); virtual void pad08(); virtual void pad0C();
	virtual void pad10(); virtual void pad14(); virtual void pad18(); virtual void pad1C();
	virtual void pad20(); virtual void pad24(); virtual void pad28(); virtual void pad2C();
	virtual void pad30(); virtual void pad34(); virtual void pad38(); virtual void pad3C();
	virtual void pad40(); virtual void pad44(); virtual void pad48(); virtual void pad4C();
	virtual void pad50(); virtual void pad54(); virtual void pad58(); virtual void pad5C();
	virtual void pad60(); virtual void pad64();
	virtual Bool slot68(Object *candidate, int field, const void *filter, bool zero);
 Bool checkMember(Object *candidate);
 char pad004[0xd0-4];
 int at0d0; int at0d4; int at0d8;
};


Bool HordeContainOwner::checkMember(Object *candidate)
{
 if(!candidate) return false;
 if(candidate->m_privateStatus & 1) return false;
 if(candidate->m_status[1] & 0x4000000) return false;
 if(candidate->m_status[1] & 0x20000000) return false;
 Object *us=*(Object**)((char*)this-0xdc);
 if(us->m_status[1] & 0x20000000) return false;
 if(candidate->m_disabledMask) return false;
 if((unsigned char)((Rva000D3F10*)candidate)->test(0xcf)) return false;
 Object *resolved=(Object*)((RvaC4390Second*)candidate)->resolve(0);
 Player *p1=us->getControllingPlayer();
 Player *p2=candidate->getControllingPlayer();
 if(p1!=p2) return false;
 if(!resolved) {
  char *data=*(char**)((char*)this-0xe0);
  if(slot68(candidate,at0d0,data+0x28c,false)) return true;
  if(slot68(candidate,at0d8,data+0x2b0,false)) {
   Object *owner=*(Object**)((char*)this-0xdc);
   if(*(int*)((char*)owner->m_experienceTracker+0x28)<=1) return true;
  }
  if(!*(bool*)(data+0x2d0)) return false;
  if(!candidate->isKindOf(Kind0023CAA0)) return false;
  if(!(*(AsciiString*)(data+0x2d4) == *(const AsciiString*)((char*)candidate->getTemplate()+0x20))) return false;
  return true;
 } else {
  if(!us || resolved==us) return false;
  AsciiString name;
  name=*(const AsciiString*)((char*)resolved->getTemplate()+0x20);
  if(((Rva00238740Lookup*)((char*)this-0xe4))->find(name)==0 ||
     resolved->testStatus(2) || resolved->testStatus(3) || us->testStatus(2) || us->testStatus(3)) return false;
  return true;
 }
}
