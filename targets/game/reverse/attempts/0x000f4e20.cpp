// ?isIdle@Team@@QBE_NXZ
// partial score=0.98 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/objectdlink

typedef bool Bool;

class Object;

class BfmeObjectVirtualTail
{
public:
	unsigned char m_vt[4];
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0(void);
};

class Overridable
{
public:
	const Overridable &getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
	unsigned char m_padding[0xc8 - 8];
	unsigned int m_kindOf0;
	unsigned int m_kindOf1;
	unsigned int m_kindOf2;
	unsigned int m_kindOf3;
};

template <class T>
class BfmeOverride
{
public:
	const T *operator->() const
	{
		const T *value = m_overridable;
		if (value != 0 && value->m_nextOverride != 0)
			value = &value->m_nextOverride->getFinalOverride();
		return value;
	}

	const T *m_overridable;
};

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
	BfmeOverride<Overridable> m_template;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x60];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	const Overridable *getTemplate() const
	{
		return m_template.operator->();
	}
};

template <class T>
class BfmeDlinkIterator
{
public:
	typedef T *(T::*GetNextFunc)() const;

	BfmeDlinkIterator(T *cur, GetNextFunc getNext) : m_cur(cur), m_getNext(getNext)
	{
	}

	Bool done() const
	{
		return m_cur == 0;
	}

	T *cur() const
	{
		return m_cur;
	}

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNext)();
	}

	public:
	T *m_cur;
	GetNextFunc m_getNext;
};

class HordeContainInterface
{
public:
	virtual int slot00() = 0; virtual int slot01() = 0; virtual int slot02() = 0; virtual int slot03() = 0;
	virtual int slot04() = 0; virtual int slot05() = 0; virtual int slot06() = 0; virtual int slot07() = 0;
	virtual int slot08() = 0; virtual int slot09() = 0; virtual int slot10() = 0; virtual int slot11() = 0;
	virtual int slot12() = 0; virtual int slot13() = 0; virtual int slot14() = 0; virtual int slot15() = 0;
	virtual int slot16() = 0; virtual int slot17() = 0; virtual int slot18() = 0; virtual int slot19() = 0;
	virtual int slot20() = 0; virtual int slot21() = 0; virtual int slot22() = 0; virtual int slot23() = 0;
	virtual int slot24() = 0; virtual int slot25() = 0; virtual int slot26() = 0; virtual int slot27() = 0;
	virtual int slot28() = 0; virtual int slot29() = 0; virtual int slot30() = 0; virtual int slot31() = 0;
	virtual int slot32() = 0; virtual int slot33() = 0; virtual int slot34() = 0; virtual int slot35() = 0;
	virtual int slot36() = 0; virtual int slot37() = 0; virtual int slot38() = 0; virtual Bool slot39() = 0;
	virtual int slot40() = 0; virtual int slot41() = 0; virtual int slot42() = 0; virtual int slot43() = 0;
	virtual int slot44() = 0; virtual int slot45() = 0; virtual int slot46() = 0; virtual int slot47() = 0;
	virtual int slot48() = 0; virtual int slot49() = 0; virtual int slot50() = 0; virtual int slot51() = 0;
	virtual int slot52() = 0; virtual int slot53() = 0; virtual int slot54() = 0; virtual int slot55() = 0;
	virtual int slot56() = 0; virtual int slot57() = 0; virtual int slot58() = 0; virtual int slot59() = 0;
	virtual int slot60() = 0; virtual int slot61() = 0; virtual int slot62() = 0; virtual int slot63() = 0;
	virtual int slot64() = 0; virtual int slot65() = 0; virtual int slot66() = 0; virtual int slot67() = 0;
	virtual int slot68() = 0; virtual int slot69() = 0; virtual int slot70() = 0; virtual int slot71() = 0;
	virtual int slot72() = 0; virtual int slot73() = 0; virtual int slot74() = 0; virtual int slot75() = 0;
	virtual int slot76() = 0; virtual int slot77() = 0; virtual int slot78() = 0; virtual int slot79() = 0;
	virtual int slot80() = 0; virtual int slot81() = 0; virtual int slot82() = 0; virtual int slot83() = 0;
	virtual int getHordeMemberCount(Bool countRiders) = 0;
	virtual int slot85() = 0; virtual int slot86() = 0; virtual int slot87() = 0; virtual int slot88() = 0;
	virtual int slot89() = 0; virtual int slot90() = 0; virtual int slot91() = 0; virtual int slot92() = 0;
	virtual int slot93() = 0; virtual int slot94() = 0; virtual int slot95() = 0; virtual int slot96() = 0;
	virtual int slot97() = 0; virtual int slot98() = 0; virtual int slot99() = 0; virtual int slot100() = 0;
	virtual int slot101() = 0; virtual int slot102() = 0; virtual int slot103() = 0; virtual int slot104() = 0;
	virtual int slot105() = 0; virtual int slot106() = 0; virtual int slot107() = 0; virtual int slot108() = 0;
};

class ContainModuleInterface
{
public:
	virtual int slot00() = 0; virtual int slot01() = 0; virtual int slot02() = 0; virtual int slot03() = 0;
	virtual int slot04() = 0; virtual int slot05() = 0; virtual int slot06() = 0; virtual int slot07() = 0;
	virtual int slot08() = 0; virtual int slot09() = 0; virtual int slot10() = 0; virtual int slot11() = 0;
	virtual int slot12() = 0; virtual int slot13() = 0; virtual int slot14() = 0; virtual int slot15() = 0;
	virtual int slot16() = 0; virtual int slot17() = 0; virtual int slot18() = 0; virtual int slot19() = 0;
	virtual int slot20() = 0; virtual int slot21() = 0; virtual int slot22() = 0; virtual int slot23() = 0;
	virtual int slot24() = 0; virtual int slot25() = 0;
	virtual HordeContainInterface *getHordeContainInterface() = 0;
};

class Team
{
public:
	Bool isIdle() const;

public:
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;
	unsigned char m_padding[0xe6 - 0x10];
	unsigned char m_isActive;
};

static __forceinline Bool teamIsIdleActive(const Team *team)
{
	BfmeDlinkIterator<Object> iter(team->m_head, BfmeObjectDlinkBase::dlink_next_TeamMemberList);
	Object *object;
	const Overridable *objectTemplate;
	ContainModuleInterface *contain;
	HordeContainInterface *horde;
	if (team->m_head == 0)
		return true;

	while (!iter.done())
	{
		object = iter.cur();
		if ((*(const unsigned char *)((const char *)object + 0x90) & 4) != 0)
			return false;

		objectTemplate = object->m_template.m_overridable;
		if (objectTemplate != 0 && objectTemplate->m_nextOverride != 0)
			objectTemplate = &objectTemplate->m_nextOverride->getFinalOverride();
		if ((objectTemplate->m_kindOf3 & 0x1000) != 0)
			goto next;

		contain = *(ContainModuleInterface **)((const char *)object + 0x1fc);
		if (contain == 0)
			goto next;
		horde = contain->getHordeContainInterface();
		if (horde == 0)
			goto next;
		if (horde->getHordeMemberCount(false) == 0)
			return false;
		if (!horde->slot39())
			goto next;
		if (!horde->slot38())
			return false;

	next:
		iter.advance();
	}

	return true;
}
Bool Team::isIdle() const
{
	if (m_isActive)
		return teamIsIdleActive(this);
	return true;
}
extern void j_00001140();
#pragma comment(linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVObject@@@Z=?j_00001140@@YAXXZ")
