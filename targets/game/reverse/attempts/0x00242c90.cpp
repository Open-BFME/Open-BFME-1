// ?d_00242c90@@YAXXZ
// partial score=0.17 date=2026-09-23
// stlport
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWMath
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

struct ThingTemplate
{
	void *m_vptr;
	Overridable *m_override;
	char m_pad08[0xc8 - 8];
	UnsignedInt m_kindFlags;
};

struct Object
{
	void *m_vptr;
	ThingTemplate *m_template;
	char m_pad08[0x38 - 8];
	Coord3D m_position;
	char m_pad44[0x90 - 0x44];
	UnsignedInt m_status90;
	char m_pad94[0x204 - 0x94];
	MemberAI *m_ai;
};

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
	Rva00242C90Link m_head;
};

class Rva00242C90
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
	Bool m_flag04;
	Bool m_flag05;
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

void Rva00242C90::method(Bool enabled)
{
	Rva00242C90Owner *container = (Rva00242C90Owner *)((char *)this - 0xe4);
	Object *owner = container->m_object;
	int ownerLayer = (owner->*rva00242c90Member<Rva00242C90GetLayer>(j_0003a391))();
	if (ownerLayer != 1 && enabled)
		enabled = false;

	MemberAI *ownerAI = owner->m_ai;
	if (!ownerAI)
		return;

	int attempts = 100;
	Bool didWork = false;
	if (m_memberIndex.m_count)
	{
		do
		{
			--attempts;
			if (attempts < 0)
				break;

			int memberID = m_memberIndex.m_header->m_next->m_key;
			Object *member = TheBfmeGameLogic->findObjectByID((UnsignedInt)memberID);
			if (!member)
			{
				(this->m_memberIndex.*rva00242c90Member<Rva00242C90Erase>(j_0001eb1e))(memberID);
			}
			else
			{
				MemberAI *memberAI = member->m_ai;
				if (!memberAI)
				{
					(this->m_memberIndex.*rva00242c90Member<Rva00242C90Erase>(j_0001eb1e))(memberID);
				}
				else if ((member->*rva00242c90Member<Rva00242C90IsClear>(j_00018223))())
				{
					Rva00242C90Link *head = &m_members.m_head;
					for (Rva00242C90Link *link = head->m_next; link != head; link = link->m_next)
						;

					container->releaseMember(member);
					if ((owner->m_status90 & 4) != 0 && owner->m_template &&
						owner->m_template->m_override)
					{
						const ThingTemplate *finalTemplate = (const ThingTemplate *)
							(owner->m_template->m_override->*rva00242c90Member<Rva00242C90FinalOverride>(j_000022bb))();
						if ((finalTemplate->m_kindFlags & 0x200) == 0 && memberAI)
						{
							Rva00242C90Command *command = (Rva00242C90Command *)((char *)memberAI + 0x20);
						(command->*rva00242c90Member<Rva00242C90CommandCall>(j_0001336d))(0, 2);

							Coord3D memberPosition;
						memberPosition.x = member->m_position.x;
						memberPosition.y = member->m_position.y;
						memberPosition.z = member->m_position.z;
						Coord3D ownerPosition;
						ownerPosition.x = owner->m_position.x;
						ownerPosition.y = owner->m_position.y;
						ownerPosition.z = owner->m_position.z;
						float dx = ownerPosition.x - memberPosition.x;
						float dy = ownerPosition.y - memberPosition.y;
						float dz = ownerPosition.z - memberPosition.z;
						float distance = (float)sqrt(dx * dx + dy * dy + dz * dz);
						if (distance > g_bfmeDirectionWeight1285)
						{
							int layer = (member->*rva00242c90Member<Rva00242C90GetLayer>(j_0003a391))();
							(memberAI->*rva00242c90Member<Rva00242C90BuildPath>(j_0004895a))(
								&memberPosition, &memberPosition, 0x7fffffff, layer,
								&ownerPosition, &ownerPosition);
							if (layer != 1)
								enabled = false;
							didWork = true;
						}
					}
				}
			}
			}
		} while (m_memberIndex.m_count);
	}

	if (didWork)
	{
		while (container->slot34())
			;
		slot16();
		(container->*rva00242c90Member<Rva00242C90GoFDB>(j_00046894))();
	}

	if (enabled)
	{
		slot46();
		Coord3D destination;
		destination.x = owner->m_position.x;
		destination.y = owner->m_position.y;
		destination.z = owner->m_position.z;
		ownerAI = owner->m_ai;
		if (ownerAI)
		{
			AI *ai = TheAI;
			const LocomotorSet *locomotors = (const LocomotorSet *)((char *)ownerAI + 0x1a8);
			(ai->m_pathfinder->*rva00242c90Member<Rva00242C90Adjust>(j_00027ffc))(
				owner, *locomotors, &destination, 0);
		}

		float dx = owner->m_position.x - destination.x;
		float dy = owner->m_position.y - destination.y;
		float dz = owner->m_position.z - destination.z;
		float distance = (float)sqrt(dx * dx + dy * dy + dz * dz);
		if (distance > g_bfmeDirectionWeight1285 &&
			distance < *(const float *)0x0109A028)
		{
			(owner->*rva00242c90Member<Rva00242C90SetPosition>(j_0003a1a7))(&destination);
		}
	}

	m_flag04 = didWork;
	m_flag05 = didWork;
}
