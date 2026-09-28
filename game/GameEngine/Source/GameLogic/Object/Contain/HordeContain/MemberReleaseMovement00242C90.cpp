// Retail RVA 0x00242C90: 791 bytes; secondary interface +0xE4 slot 4.
// The precise retail method name is unproven. Keep the address identity.
// Member index +0x30; owning Object at this-0xDC; member-list pointer +0x54.
// Read-only disassembly and callees.py establish every ILT call below.
// Scope the primary owner view to the drain loop; subtract the final
// coordinates in place to reproduce the native x87 local-slot reuse.
// stlport
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWMath /Igame/GameEngine/Source/GameLogic/Object
// Address-derived body for the +0xe4 interface subobject's slot 4.
// The member-index value type stays opaque; only its verified key word is read.

typedef bool Bool;
typedef unsigned int UnsignedInt;

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <math.h>
#include "coord3d.h"

inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}

class Object;
class MemberAI;
class Pathfinder;
class Overridable;
struct LocomotorSet;

template <class T> __forceinline T rva00242c90Member(void (*raw)())
{
	union { void (*raw)(); T member; } u;
	u.raw = raw;
	return u.member;
}

extern void j_000022bb();
extern void j_0001336d();
extern void j_00018223();
extern void j_0001eb1e();
extern void j_00027ffc();
extern void j_0003a1a7();
extern void j_0003a391();
extern void j_00046894();
extern void j_0004895a();

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	void *m_vptr;
	Overridable *m_nextOverride;
};

struct ThingTemplate : public Overridable
{
	char m_pad08[0xc8 - 8];
	UnsignedInt m_kindof;
};

#define BFME_HAVE_COORD3D 1
#include "object.h"

struct Rva00242C90TreeNode
{
	UnsignedInt m_color;
	Rva00242C90TreeNode *m_parent;
	Rva00242C90TreeNode *m_next;
	Rva00242C90TreeNode *m_previous;
	int m_key;
};

struct Rva00242C90MemberIndex
{
	Rva00242C90TreeNode *m_header;
	UnsignedInt m_count;
	UnsignedInt m_opaque;
	UnsignedInt erase(const int &key);
};

struct Rva00242C90Link
{
	Rva00242C90Link *m_next;
	Rva00242C90Link *m_previous;
};

struct Rva00242C90MemberPair
{
	UnsignedInt first;
	Object *second;
};

typedef _STL::hash_map<UnsignedInt, Object *, _STL::hash<UnsignedInt>,
	_STL::equal_to<UnsignedInt> > Rva00242C90ObjectHash;

struct Rva00367E30Logic
{
	__forceinline Object *findObjectByID(UnsignedInt objectID)
	{
		if (objectID == 0)
			return 0;
		Rva00242C90ObjectHash::iterator it = objects.find(objectID);
		if (it == objects.end())
			return 0;
		return (*it).second;
	}

	char m_pad00[0xb0];
	Rva00242C90ObjectHash objects;
};

extern Rva00367E30Logic *TheBfmeGameLogic;
extern const float g_bfmeDirectionWeight1285;

class Pathfinder
{
public:
	Bool adjustDestination(Object *object, const LocomotorSet &locomotors,
		Coord3D *destination, const Coord3D *groupDestination);
};

class AI
{
public:
	char m_pad00[0x0c];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

class MemberAI
{
public:
	void buildPath_00271010(const Coord3D *first, const Coord3D *third,
		int cost, int layer, const Coord3D *middle, const Coord3D *destination);
	char m_pad00[0x1a8];
	LocomotorSet *m_locomotorSetAddressOnly;
};

class Rva00242C90Command
{
public:
	void call(int first, int second);
};

class Rva00242C90Owner
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33();
	virtual Bool slot34();
	virtual void releaseMember(Object *member);
	char m_pad04[4];
	Object *m_object;
};

struct Rva00242C90List
{
	Rva00242C90Link *m_head;
};

class MemberReleaseMovement00242C90
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void method(Bool enabled);
	virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10();
	virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22();
	virtual void slot23(); virtual void slot24(); virtual void slot25();
	virtual void slot26(); virtual void slot27(); virtual void slot28();
	virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34();
	virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void slot38(); virtual void slot39(); virtual void slot40();
	virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46();
	unsigned char m_flag04;
	unsigned char m_flag05;
	char m_pad06[0x2a];
	Rva00242C90MemberIndex m_memberIndex;
	char m_pad3c[0x18];
	Rva00242C90List m_members;
};

typedef int (Object::*Rva00242C90GetLayer)() const;
typedef unsigned char (Object::*Rva00242C90IsClear)() const;
typedef const Overridable *(Overridable::*Rva00242C90FinalOverride)() const;
typedef UnsignedInt (Rva00242C90MemberIndex::*Rva00242C90Erase)(const int &);
typedef void (Rva00242C90Command::*Rva00242C90CommandCall)(int, int);
typedef void (MemberAI::*Rva00242C90BuildPath)(const Coord3D *, const Coord3D *,
	int, int, const Coord3D *, const Coord3D *);
typedef Bool (Pathfinder::*Rva00242C90Adjust)(Object *, const LocomotorSet &,
	Coord3D *, const Coord3D *);
typedef void (Object::*Rva00242C90SetPosition)(const Coord3D *);
typedef void (Rva00242C90Owner::*Rva00242C90GoFDB)();

void MemberReleaseMovement00242C90::method(Bool enabled) {

 int layer=((*(Object**)((char*)this-0xdc))->*rva00242c90Member<Rva00242C90GetLayer>(j_0003a391))();
 if(layer!=1 && enabled) enabled=false;
 Object *owner=(*(Object**)((char*)this-0xdc));
 if(!owner->m_ai) return;
 int attempts=100;
 unsigned char didWork=0;
 if(m_memberIndex.m_count) {
  do {
   int memberID=m_memberIndex.m_header->m_next->m_key;
   if(--attempts<0) break;
   Object *member=TheBfmeGameLogic->findObjectByID((UnsignedInt)memberID);
   if(!member) (m_memberIndex.*rva00242c90Member<Rva00242C90Erase>(j_0001eb1e))(memberID);
   else if((member->*rva00242c90Member<Rva00242C90IsClear>(j_00018223))()) {
    Rva00242C90Link *head=m_members.m_head;
    for(Rva00242C90Link *link=head->m_next;link!=head;link=link->m_next) ;
    ((Rva00242C90Owner*)((char*)this-0xe4))->releaseMember(member);
    if(owner->m_status[0]&4) {
     const ThingTemplate *t=owner->m_template;
     if(t && t->m_nextOverride) t=(const ThingTemplate*)(t->m_nextOverride->*rva00242c90Member<Rva00242C90FinalOverride>(j_000022bb))();
     if(!(t->m_kindof&0x200)) {
      MemberAI *ai=(MemberAI*)member->m_ai;
      if(ai) {
       (((Rva00242C90Command*)((char*)ai+0x20))->*rva00242c90Member<Rva00242C90CommandCall>(j_0001336d))(0,2);
       Coord3D memberPosition; memberPosition.x=member->m_cachedPos.x; memberPosition.y=member->m_cachedPos.y; memberPosition.z=member->m_cachedPos.z;
       Coord3D ownerPosition; ownerPosition.x=owner->m_cachedPos.x; ownerPosition.y=owner->m_cachedPos.y; ownerPosition.z=owner->m_cachedPos.z;
       float dx=ownerPosition.x-memberPosition.x,dy=ownerPosition.y-memberPosition.y,dz=ownerPosition.z-memberPosition.z;
       float distance=(float)sqrt(dz*dz+dy*dy+dx*dx);
       if(distance>g_bfmeDirectionWeight1285) {
        (ai->*rva00242c90Member<Rva00242C90BuildPath>(j_0004895a))(&memberPosition,&memberPosition,0x7fffffff,(member->*rva00242c90Member<Rva00242C90GetLayer>(j_0003a391))(),&ownerPosition,&ownerPosition);
       }
      }
     }
    }
    if((member->*rva00242c90Member<Rva00242C90GetLayer>(j_0003a391))()!=1) enabled=false;
    didWork=true;
   }
  }while(m_memberIndex.m_count);
  if(didWork) {
   Rva00242C90Owner *container=(Rva00242C90Owner*)((char*)this-0xe4);
   while(container->slot34()) ;
   slot16();
   (container->*rva00242c90Member<Rva00242C90GoFDB>(j_00046894))();
   if(enabled) {
    slot46();
    Object *object=*(Object**)((char*)this-0xdc);
    Coord3D destination; destination.x=object->m_cachedPos.x; destination.y=object->m_cachedPos.y; destination.z=object->m_cachedPos.z;
    MemberAI *ai=(MemberAI*)object->m_ai;
    if(!ai) return;
    (TheAI->m_pathfinder->*rva00242c90Member<Rva00242C90Adjust>(j_00027ffc))(object,*(const LocomotorSet*)((char*)ai+0x1a8),&destination,0);
    Coord3D current; current.x=object->m_cachedPos.x; current.y=object->m_cachedPos.y; current.z=object->m_cachedPos.z;
    current.x-=destination.x; current.y-=destination.y; current.z-=destination.z;
    float distance=(float)sqrt(current.z*current.z+current.y*current.y+current.x*current.x);
    if(distance>g_bfmeDirectionWeight1285 && distance<150.0f) {
     (object->*rva00242c90Member<Rva00242C90SetPosition>(j_0003a1a7))(&destination);
    }
   }
  }
 }
 m_flag04=didWork; m_flag05=didWork;
}
