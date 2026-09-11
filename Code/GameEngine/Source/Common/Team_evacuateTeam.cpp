// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/objectdlink
// Retail 0x000F3250, Team::evacuateTeam(), 326 bytes.
// stlport

// The retail Team TU built STLport's list internals with exceptions disabled.
// Keeping this TU-scoped makes node creation inline and preserves the retail
// list destructor's EH-state and epilogue scheduling without changing shared
// STL configuration.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "ObjectDlinkPmf.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;

extern void j_00001140();

#pragma comment(linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVObject@@XZ=?j_00001140@@YAXXZ")

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

template <class OBJCLASS>
class BfmeEvacuateIterator
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

	BfmeEvacuateIterator(OBJCLASS *current, GetNextFunc getNext) :
		m_current(current),
		m_getNext(getNext)
	{
	}

	void advance()
	{
		if (m_current)
			m_current = callMemberFunction(*m_current, m_getNext)();
	}

	Bool done() const { return m_current == 0; }
	OBJCLASS *cur() const { return m_current; }

private:
	OBJCLASS *m_current;
	GetNextFunc m_getNext;
};

class Team
{
public:
	void evacuateTeam();

	void *m_vptr;
	void *m_prototype;
	void *m_id;
	Object *m_memberHead;

	BfmeEvacuateIterator<Object> iterateTeamMembers() const
	{
		return BfmeEvacuateIterator<Object>(m_memberHead, Object::dlink_next_TeamMemberList);
	}
};

struct BfmeEvacuateObjectView
{
	unsigned char m_pad000[0x90];
	unsigned char m_destroyed90;
	unsigned char m_pad091[0x16B];
	void *m_contain1FC;
	unsigned char m_pad200[0x144];
	unsigned char m_effectivelyDead344;

	Bool isDestroyed() const { return (m_destroyed90 & 1) != 0; }
	Bool isEffectivelyDead() const { return (m_effectivelyDead344 & 1) != 0; }
};

class BfmeEvacuateContain
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
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36();
	virtual void removeAllContained(Bool exposeStealthUnits = false);
	virtual void slot38(); virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45();
	virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49();
	virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57();
	virtual void slot58(); virtual void slot59(); virtual void slot60(); virtual void slot61();
	virtual void slot62(); virtual void slot63();
	virtual UnsignedInt getContainCount(Bool includePending = false) const;
};

void Team::evacuateTeam()
{
	std::list<Object *> objectsToProcess;

	for (BfmeEvacuateIterator<Object> iter = iterateTeamMembers(); !iter.done(); iter.advance()) {
		Object *object = iter.cur();
		BfmeEvacuateObjectView *view = (BfmeEvacuateObjectView *)object;
		if (view->isDestroyed() || view->isEffectivelyDead())
			continue;

		BfmeEvacuateContain *contain = (BfmeEvacuateContain *)view->m_contain1FC;
		if (contain != 0 && contain->getContainCount() > 0)
			objectsToProcess.push_back(object);
	}

	for (std::list<Object *>::iterator node = objectsToProcess.begin(); node != objectsToProcess.end(); ++node) {
		BfmeEvacuateObjectView *view = (BfmeEvacuateObjectView *)*node;
		BfmeEvacuateContain *contain = (BfmeEvacuateContain *)view->m_contain1FC;
		if (contain != 0)
			contain->removeAllContained();
	}

	objectsToProcess.clear();
}
