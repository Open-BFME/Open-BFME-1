// ?method@Rva0023F670@@QAE_NXZ
// partial score=0.5099009901 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/GameEngine/Source/GameLogic/Object
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>
#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Object;
class Coord3D;

class Overridable
{
public:
	virtual void slot00() = 0;
	const Overridable *getFinalOverride() const;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_gap08[0xc8 - 8];
	UnsignedInt m_kindFlags[3];
};

enum KindOfType
{
	KINDOF_INVALID = 0,
};

#define THING_TU_MEMBERS Bool isKindOf(KindOfType kind) const;
#include "object.h"

typedef _STL::list<int> BfmeMemberList;
namespace _STL { template<> _List_base<int,allocator<int> >::~_List_base(); }
typedef _STL::vector<int> BfmeObjectVector;

class Rva0003E80B
{
public:
	Bool compare(void *other);
};

class Rva0023F670
{
public:
	Bool method();
};

class HordeContainMemberInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60(_STL::list<int> *members) = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void slot68() = 0;
	virtual void slot69() = 0;
	virtual void slot70() = 0;
	virtual void slot71() = 0;
	virtual void slot72() = 0;
	virtual void slot73() = 0;
	virtual void slot74() = 0;
	virtual void slot75() = 0;
	virtual void slot76() = 0;
	virtual void slot77() = 0;
	virtual void slot78() = 0;
	virtual void slot79() = 0;
	virtual void slot80() = 0;
	virtual void slot81() = 0;
	virtual void slot82() = 0;
	virtual void slot83() = 0;
	virtual void slot84() = 0;
	virtual void slot85() = 0;
	virtual void slot86() = 0;
	virtual void slot87() = 0;
	virtual void slot88() = 0;
	virtual void slot89() = 0;
	virtual void slot90() = 0;
	virtual void slot91() = 0;
	virtual void slot92() = 0;
	virtual void slot93() = 0;
	virtual void slot94() = 0;
	virtual void slot95() = 0;
	virtual void slot96() = 0;
	virtual void slot97() = 0;
	virtual void slot98() = 0;
	virtual void slot99() = 0;
	virtual void slot100() = 0;
	virtual void slot101() = 0;
	virtual void slot102() = 0;
	virtual void slot103() = 0;
	virtual void slot104() = 0;
	virtual void slot105() = 0;
	virtual void slot106() = 0;
	virtual void slot107() = 0;
	virtual void slot108() = 0;
	virtual void slot109() = 0;
	virtual void slot110() = 0;
	virtual void slot111() = 0;
	virtual void slot112() = 0;
	virtual void slot113() = 0;
	virtual void slot114() = 0;
	virtual void slot115(_STL::vector<int> *members) = 0;
	virtual Bool slot116() = 0;
};

enum EvaMessage
{
	RVA_EVA_MESSAGE = 0,
};

class Eva
{
public:
	Bool setShouldPlay(EvaMessage message, const Coord3D *position);
};

class GameLogic
{
public:
	void destroyObject(Object *object);
};

extern Eva *TheEva;
extern GameLogic *TheGameLogic;

#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?isKindOf@Thing@@QBE_NW4KindOfType@@@Z=?j_0003251f@@YAXXZ")
#pragma comment(linker, "/alternatename:?setShouldPlay@Eva@@QAE_NW4EvaMessage@@PBUCoord3D@@@Z=?j_0002b5f3@@YAXXZ")
#pragma comment(linker, "/alternatename:?destroyObject@GameLogic@@QAEXPAVObject@@@Z=?j_0001d0de@@YAXXZ")
#pragma comment(linker, "/alternatename:?compare@Rva0003E80B@@QAE_NPAX@Z=?j_0003e80b@@YAXXZ")

inline HordeContainMemberInterface *memberInterface(Rva0023F670 *self)
{
	return (HordeContainMemberInterface *)((char *)self + 0xe4);
}

inline ThingTemplate *finalTemplate0023F670(Object *obj) {
 ThingTemplate *t=obj->m_template;
 if(t==0) return 0;
 if(t->m_nextOverride) return (ThingTemplate*)t->m_nextOverride->getFinalOverride();
 return t;
}
Bool Rva0023F670::method()
{
	Object *member = *(Object **)((char *)this + 8);
	Bool result = false;

	if (((unsigned char)member->m_status[0] & 4) == 0
		&& ((BfmeMemberList *)((char *)this + 0x38))->empty()
		&& *(UnsignedInt *)((char *)this + 0x118) == 0)
	{
		void *moduleData = *(void **)((char *)this + 4);
		Eva *eva = TheEva;
		eva->setShouldPlay((EvaMessage)*(Int *)((char *)moduleData + 0x2e4), 0);
		GameLogic *logic = TheGameLogic;
		logic->destroyObject(member);
	}
	else {
	HordeContainMemberInterface *interfaceView = memberInterface(this);
	if (interfaceView->slot116()) {

	ThingTemplate *memberTemplate = finalTemplate0023F670(member);
	if ((memberTemplate->m_kindFlags[2] & 0x10000000) == 0
		&& !member->isKindOf((KindOfType)0x0b))
		return false;

	{
		BfmeMemberList members;
		interfaceView->slot60(&members);
		UnsignedInt memberCount=members.size();

		void *moduleData = *(void **)((char *)this + 4);
		Int memberLimit = *(Int *)((char *)moduleData + 0x2ec);
		if (memberLimit > 0)
		{
			if (memberCount > (UnsignedInt)memberLimit)
				goto listDone;

			{
				BfmeObjectVector selected;
				interfaceView->slot115(&selected);
				result = true;
			}
		}
		else
		{
			if (memberCount == 0)
				goto listDone;

			ThingTemplate *firstTemplate = 0;
			for (BfmeMemberList::iterator it = members.begin(); it != members.end(); ++it)
			{
				Object *current = (Object*)*it;
				if (current == 0 || current->isKindOf((KindOfType)0xa3))
					continue;

                if(firstTemplate==0) firstTemplate=finalTemplate0023F670(current);
                else if(current->m_template!=0) {
                    ThingTemplate *currentTemplate=finalTemplate0023F670(current);
                    if(currentTemplate!=0 && !((Rva0003E80B*)firstTemplate)->compare(currentTemplate)) goto listDone;
                }
			}

			{
				BfmeObjectVector selected;
				interfaceView->slot115(&selected);
				result = true;
			}
		}

listDone:
		;
	}

	}
	}
	return result;
}
