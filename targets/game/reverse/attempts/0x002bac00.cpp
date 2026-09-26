// ?update@FoundationAIUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.621 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
#include "../../../../../../../inputs/reference/shims/stringinline/StringInline.h"

class Drawable
{
public:
	void setSelectable(bool value);
};
enum KindOfType { KINDOF_FOUNDATION = 0x95 };
enum ObjectStatusTypes { OBJECT_STATUS_UNSELECTABLE = 3 };
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
class Thing
{
public:
	bool isKindOf(KindOfType kind) const;
};
class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	unsigned char m_unreconstructed[0xd8];
	unsigned int m_flags;
};
class Module;
class Object
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual Drawable *getDrawable() const = 0;
	Module *findModule(NameKeyType key) const;
	void clearStatus(ObjectStatusTypes status);
	unsigned char m_fields04[0x340];
};
class Gen002BA170
{
public:
	void bfmeSet(AsciiString value);
};
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *text);
};
class GameLogic
{
public:
	Object *findObjectByID(int id);
};
class Module
{
public:
	unsigned char m_fields00[0x14];
	Object *m_pending;
	int m_pendingID;
	unsigned char m_fields1c[0x84];
	int m_pendingData;
	bool isPendingObjectUnavailable() const;
};
class CastleBehavior : public Module
{
public:
	bool isPendingObjectUnavailable() const;
};
class InGameUI
{
public:
	virtual void v00() = 0; virtual void v04() = 0;
	virtual void v08() = 0; virtual void v0c() = 0;
	virtual void v10() = 0; virtual void v14() = 0;
	virtual void v18() = 0; virtual void v1c() = 0;
	virtual void v20() = 0; virtual void v24() = 0;
	virtual void v28() = 0; virtual void v2c() = 0;
	virtual void v30() = 0; virtual void v34() = 0;
	virtual void v38() = 0; virtual void v3c() = 0;
	virtual void v40() = 0; virtual void v44() = 0;
	virtual void v48() = 0; virtual void v4c() = 0;
	virtual void v50() = 0; virtual void v54() = 0;
	virtual void v58() = 0; virtual void v5c() = 0;
	virtual void v60() = 0; virtual void v64() = 0;
	virtual void v68() = 0; virtual void v6c() = 0;
	virtual void v70() = 0; virtual void v74() = 0;
	virtual void v78() = 0; virtual void v7c() = 0;
	virtual void v80() = 0; virtual void v84() = 0;
	virtual void v88() = 0; virtual void v8c() = 0;
	virtual void v90() = 0; virtual void v94() = 0;
	virtual void v98() = 0; virtual void v9c() = 0;
	virtual void va0() = 0; virtual void va4() = 0;
	virtual void va8() = 0; virtual void vac() = 0;
	virtual void vb0() = 0; virtual void vb4() = 0;
	virtual void vb8() = 0; virtual void vbc() = 0;
	virtual void vc0() = 0; virtual void vc4() = 0;
	virtual void vc8() = 0; virtual void vcc() = 0;
	virtual void vd0() = 0; virtual void vd4() = 0;
	virtual void vd8() = 0; virtual void vdc() = 0;
	virtual void ve0() = 0;
	virtual void slotE4(Drawable *drawable) = 0;
};
class BfmeA1057
{
public:
	void bfmeGo1057A(int value);
};
class UpdateOwner
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual Object *getObject() = 0;
};
class FoundationAIUpdate
{
public:
	virtual UpdateSleepTime update();
	char m_fields04[0x80];
	int m_currentID;
	bool m_updatePending;
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameLogic *TheBfmeGameLogic;
extern InGameUI *TheInGameUI;

UpdateSleepTime FoundationAIUpdate::update()
{
	if (m_updatePending)
	{
		UpdateOwner *module = (UpdateOwner *)((char *)this - 0x10);
		module->getObject();
		m_updatePending = false;
		static NameKeyType castleMemberKey = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
		Object *owner = *(Object **)((char *)this - 8);
		Module *member = owner->findModule(castleMemberKey);
		if (member && !member->m_pending && member->m_pendingID)
		{
			Object *pending = TheBfmeGameLogic->findObjectByID(member->m_pendingID);
			if (pending)
			{
				static NameKeyType castleKey = TheNameKeyGenerator->nameToKey("CastleBehavior");
				Module *castle = pending->findModule(castleKey);
				if (castle)
					member->m_pending = *(Object **)((char *)castle + 0xa0);
			}
		}
	}
	Object *owner = *(Object **)((char *)this - 8);
	if (*(unsigned int *)((char *)owner + 0x344) & 1)
	{
		Object *playerObject = *(Object **)((char *)owner + 4);
		Overridable *source = playerObject ? *(Overridable **)((char *)playerObject + 4) : 0;
		if (source && (source->getFinalOverride()->m_flags & 0x200000))
		{
			((Gen002BA170 *)owner)->bfmeSet(AsciiString("empty"));
			owner->getDrawable();
			return UPDATE_SLEEP_NONE;
		}
	}
	if (m_currentID && TheBfmeGameLogic->findObjectByID(m_currentID))
		return UPDATE_SLEEP_NONE;
	if (m_currentID)
	{
		m_currentID = 0;
		if (!((Thing *)owner)->isKindOf(KINDOF_FOUNDATION))
		{
			owner->clearStatus(OBJECT_STATUS_UNSELECTABLE);
			Drawable *drawable = owner->getDrawable();
			if (drawable && !((Thing *)owner)->isKindOf(KINDOF_FOUNDATION))
			{
				drawable->setSelectable(true);
				((BfmeA1057 *)drawable)->bfmeGo1057A(0x1e);
			}
		}
	}
	static NameKeyType memberKey = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
	Module *member = owner->findModule(memberKey);
	if (member)
	{
		if (member->m_pending)
		{
			if (((CastleBehavior *)member)->isPendingObjectUnavailable())
			{
				((Gen002BA170 *)owner)->bfmeSet(AsciiString("empty"));
				Drawable *object = owner->getDrawable();
				if (object && *(unsigned char *)((char *)object + 0x3ac))
					TheInGameUI->slotE4(object);
			}
		}
		else
			((Gen002BA170 *)owner)->bfmeSet(AsciiString(""));
	}
	return UPDATE_SLEEP_NONE;
}
