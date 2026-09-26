// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?isIdle@Rva000EDB30Team@@QBE_NXZ
// The AIPlayer::checkReadyTeams call through ILT 0x0003A143 proves this body
// checks every team member's AI state. The member list head sits at +0x0c.
// Each object exposes its AI interface at +0x204. The dead flag sits at +0x344.

typedef bool Bool;

class AIUpdateInterface;
class Object;
class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };
class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};
class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(); };
class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
};
class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };

extern void j_00001140();
#pragma comment(linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVObject@@XZ=?j_00001140@@YAXXZ")

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	AIUpdateInterface *getAIUpdateInterface() const
	{
		return *(AIUpdateInterface *const *)((const char *)this + 0x204);
	}

	Bool isEffectivelyDead() const
	{
		return (*(const unsigned char *)((const char *)this + 0x344) & 1) != 0;
	}

	unsigned char m_tail[0x2c0];
};

template <class ObjectType>
class BfmeDlinkIterator
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)() const;

	BfmeDlinkIterator(ObjectType *current, GetNextFunc getNext) :
		m_current(current), m_getNext(getNext) { }

	void advance()
	{
		if (m_current)
			m_current = (m_current->*m_getNext)();
	}

	bool done() const { return m_current == 0; }
	ObjectType *current() const { return m_current; }

private:
	ObjectType *m_current;
	GetNextFunc m_getNext;
};

class AIUpdateInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0; virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0; virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0; virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void slot32() = 0; virtual void slot33() = 0; virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0; virtual void slot38() = 0; virtual void slot39() = 0;
	virtual void slot40() = 0; virtual void slot41() = 0; virtual void slot42() = 0; virtual void slot43() = 0;
	virtual void slot44() = 0; virtual void slot45() = 0; virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0; virtual void slot50() = 0; virtual void slot51() = 0;
	virtual void slot52() = 0; virtual void slot53() = 0; virtual void slot54() = 0; virtual void slot55() = 0;
	virtual void slot56() = 0; virtual void slot57() = 0; virtual void slot58() = 0; virtual void slot59() = 0;
	virtual void slot60() = 0; virtual void slot61() = 0; virtual void slot62() = 0; virtual void slot63() = 0;
	virtual void slot64() = 0; virtual void slot65() = 0; virtual void slot66() = 0; virtual void slot67() = 0;
	virtual void slot68() = 0; virtual void slot69() = 0; virtual void slot70() = 0; virtual void slot71() = 0;
	virtual void slot72() = 0; virtual void slot73() = 0; virtual void slot74() = 0; virtual void slot75() = 0;
	virtual void slot76() = 0; virtual void slot77() = 0; virtual void slot78() = 0; virtual void slot79() = 0;
	virtual void slot80() = 0; virtual void slot81() = 0; virtual void slot82() = 0; virtual void slot83() = 0;
	virtual void slot84() = 0; virtual void slot85() = 0; virtual void slot86() = 0; virtual void slot87() = 0;
	virtual void slot88() = 0; virtual void slot89() = 0; virtual void slot90() = 0; virtual void slot91() = 0;
	virtual void slot92() = 0; virtual void slot93() = 0; virtual void slot94() = 0; virtual void slot95() = 0;
	virtual Bool isIdle() = 0;
};

class Rva000EDB30Team
{
public:
	Bool isIdle() const;

private:
	unsigned char m_beforeMemberList[0x0c];
	Object *m_memberList;
};

Bool Rva000EDB30Team::isIdle() const
{
	BfmeDlinkIterator<Object> iter(m_memberList,
		BfmeObjectDlinkBase::dlink_next_TeamMemberList);

	for (; !iter.done(); iter.advance())
	{
		Object *object = iter.current();
		AIUpdateInterface *ai = object->getAIUpdateInterface();
		if (ai == 0)
			continue;
		if (object->isEffectivelyDead())
			continue;
		if (!ai->isIdle())
			return false;
	}

	return true;
}
