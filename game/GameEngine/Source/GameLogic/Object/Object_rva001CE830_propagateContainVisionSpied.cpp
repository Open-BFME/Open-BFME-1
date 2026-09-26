// ?rva001CE830@Rva001CE830Object@@QAEXH@Z
// BFME Object vtable-adjacent containment helper, retail 0x001CE830 (209 bytes).
// The real class/member name is not recovered. The address-derived owner is
// intentional: the body walks m_contain's item-view list and forwards a
// vision-spied notification (a paired vision-unspied twin sits at 0x001CE940).
// stlport

#include <list>

typedef int Int;
typedef unsigned char Bool;

class Object;
class BfmeRva493A0Object;

class BfmeObjectList : public _STL::list<BfmeRva493A0Object *>
{
public:
	BfmeObjectList(const _STL::list<BfmeRva493A0Object *> &source)
		: _STL::list<BfmeRva493A0Object *>(source) {}
	~BfmeObjectList();
};

class BfmeTemplate
{
public:
	char m_pad00[4];
	BfmeTemplate *m_finalOverride;
	char m_pad08[0xcc];
	unsigned int m_flags;
};

class BfmeContainListView
{
public:
	virtual void v00() = 0; virtual void v01() = 0; virtual void v02() = 0; virtual void v03() = 0;
	virtual void v04() = 0; virtual void v05() = 0; virtual void v06() = 0; virtual void v07() = 0;
	virtual void v08() = 0; virtual void v09() = 0; virtual void v10() = 0; virtual void v11() = 0;
	virtual void v12() = 0; virtual void v13() = 0; virtual void v14() = 0; virtual void v15() = 0;
	virtual void v16() = 0; virtual void v17() = 0; virtual void v18() = 0; virtual void v19() = 0;
	virtual void v20() = 0; virtual void v21() = 0; virtual void v22() = 0; virtual void v23() = 0;
	virtual void v24() = 0; virtual void v25() = 0; virtual void v26() = 0; virtual void v27() = 0;
	virtual void v28() = 0; virtual void v29() = 0; virtual void v30() = 0; virtual void v31() = 0;
	virtual void v32() = 0; virtual void v33() = 0; virtual void v34() = 0; virtual void v35() = 0;
	virtual void v36() = 0; virtual void v37() = 0; virtual void v38() = 0; virtual void v39() = 0;
	virtual void v40() = 0; virtual void v41() = 0; virtual void v42() = 0; virtual void v43() = 0;
	virtual void v44() = 0; virtual void v45() = 0; virtual void v46() = 0; virtual void v47() = 0;
	virtual void v48() = 0; virtual void v49() = 0; virtual void v50() = 0; virtual void v51() = 0;
	virtual void v52() = 0; virtual void v53() = 0; virtual void v54() = 0; virtual void v55() = 0;
	virtual void v56() = 0; virtual void v57() = 0; virtual void v58() = 0;
	virtual const _STL::list<BfmeRva493A0Object *> *getContainedItemsList() = 0;
};

class BfmeContain
{
public:
	virtual void v00() = 0; virtual void v01() = 0; virtual void v02() = 0; virtual void v03() = 0;
	virtual void v04() = 0; virtual void v05() = 0; virtual void v06() = 0; virtual void v07() = 0;
	virtual void v08() = 0; virtual void v09() = 0; virtual void v10() = 0; virtual void v11() = 0;
	virtual void v12() = 0; virtual void v13() = 0; virtual void v14() = 0; virtual void v15() = 0;
	virtual void v16() = 0; virtual void v17() = 0; virtual void v18() = 0; virtual void v19() = 0;
	virtual void v20() = 0; virtual void v21() = 0; virtual void v22() = 0; virtual void v23() = 0;
	virtual void v24() = 0; virtual void v25() = 0;
	virtual BfmeContainListView *getContainedItemsView() = 0;
};

class BfmeThingAIA
{
public:
	Bool bfmeAskAIA(Int kind);
};

class BfmeObjE10
{
public:
	void actionA(Int kind);
};

extern void j_000022bb();
extern void j_0003251f();

class Object
{
public:
	virtual void unused() = 0;

protected:
	BfmeTemplate *m_template;
	char m_pad08[0x1f4];
	BfmeContain *m_contain;
	char m_pad200[0x14];
	Object *m_containedBy;
};

typedef BfmeTemplate *(__fastcall *BfmeOverrideCall)(BfmeTemplate *);
typedef Bool (BfmeThingAIA::*BfmeKindOfCall)(Int);

class Rva001CE830Object : public Object
{
public:
	void rva001CE830(Int player);
};

void Rva001CE830Object::rva001CE830(Int player)
{
	BfmeTemplate *objectTemplate = m_template;
	if (objectTemplate != 0 && objectTemplate->m_finalOverride != 0)
	{
		BfmeOverrideCall overrideCall = (BfmeOverrideCall)j_000022bb;
		objectTemplate = overrideCall(objectTemplate->m_finalOverride);
	}

	Object *containerObject;
	if (objectTemplate->m_flags & 0x1000)
	{
		containerObject = this;
	}
	else
	{
		Object *container = m_containedBy;
		if (container == 0)
			return;

		union { void (*raw)(); BfmeKindOfCall member; } kindOf;
		kindOf.raw = j_0003251f;
		if (!(reinterpret_cast<BfmeThingAIA *>(container)->*kindOf.member)(0x6c))
			return;

		containerObject = container;
	}

	if (containerObject == 0)
		return;

	BfmeContain *contain = ((Rva001CE830Object *)containerObject)->m_contain;
	if (contain == 0)
		return;

	BfmeContainListView *view = contain->getContainedItemsView();
	if (view == 0)
		return;

	const _STL::list<BfmeRva493A0Object *> *source = view->getContainedItemsList();
	BfmeObjectList items(*source);
	for (BfmeObjectList::iterator it = items.begin(); it != items.end(); ++it)
	{
		((BfmeObjE10 *)*it)->actionA(player);
	}
	((BfmeObjE10 *)containerObject)->actionA(player);
}
