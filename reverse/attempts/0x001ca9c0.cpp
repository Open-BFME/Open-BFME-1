// ?d_001ca9c0@@YAXXZ
// partial score=0.4 date=2026-08-27
// cl: /O2 /Ob1
// Retail 0x001CA9C0 150 bytes - attempt 1, t=14m
// Pins:
//  +0x34C Rva008F7B00* m_rva (check null then ->get(int))
//  +0x1D8 Team* m_team (arg to Player::getRelationship)
//  -0x64 Object* host = (Object*)((char*)this - 0x64) -> isKindOf(int)
//  global 0x012ED748 ThePlayerList -> getNthPlayer(int)
//  calls:
//   0x001CA9E0: call 0x00044F30 thunk -> 0x004DF240 PlayerList::getNthPlayer (thunk at 0x44F30)
//   0x001CA9EE: call 0x0003E77A thunk -> 0x004D19C0 Player::getRelationship (thunk at 0x3E77A) arg Team* at +0x1D8, this = returned Player*
//   0x001CA9FF/0x001CAA0F/0x001CAA25/0x001CAA45: call 0x0003251F thunk -> 0x004A2CF0 Thing::isKindOf (KindOfType) args 2 (0x02) and 0xB2 (178)
//   0x001CAA35: call 0x008F7B00 Rva008F7B00::get(int) this = [esi+0x34C], arg = playerNdx (edi/bx)
//  constants: Relationship NEUTRAL=1 (cmp eax,1), KindOf 2 and 0xB2
//  Logic approx (see file):
//   if (!m_rva) return false;
//   Player* p = ThePlayerList->getNthPlayer(arg);
//   Relationship r = p->getRelationship(m_team);
//   Object* obj = (Object*)((char*)this - 0x64);
//   if (r == NEUTRAL) { if (!obj->isKindOf(2)) return true; return obj->isKindOf(0xB2); }
//   else { if (!obj->isKindOf(2)) return true; if (!m_rva->get(arg)) return true; return obj->isKindOf(0xB2); }
//  Byte diff shows register allocation mismatch (edi vs ebx) and add vs lea for host adjust, and push hoist for KindOf 2.
//  Requires precise dummy locals to force retail's register choices (push ebx; push edi; mov edi,[esp+10]; push edi).

class Rva008F7B00{ char m_pad[0xA4]; char m_slots[16]; public: char get(int) const; };
class Team; enum Relationship{ENEMIES=0,NEUTRAL=1,ALLIES=2};
class Player{ public: Relationship getRelationship(const Team*) const; };
class PlayerList{ public: Player* getNthPlayer(int); };
extern PlayerList *ThePlayerList;
class Object{ public: bool isKindOf(int) const; };
struct Module{ char _0[0x1D8]; Team* m_team; char _1[0x34C-0x1D8-4]; Rva008F7B00* m_rva; bool isAllowed(int); };
bool Module::isAllowed(int n){ if(m_rva==0) return false; Player* p=ThePlayerList->getNthPlayer(n); Relationship r=p->getRelationship(m_team); Object* o=(Object*)((char*)this-0x64); if(r==NEUTRAL){ if(!o->isKindOf(2)) return true; if(!o->isKindOf(0xB2)) return false; return true; } else { if(!o->isKindOf(2)) return true; if(!m_rva->get(n)) return true; if(o->isKindOf(0xB2)) return true; return false; } }
