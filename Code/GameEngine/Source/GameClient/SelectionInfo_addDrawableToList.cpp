// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// addDrawableToList, retail 0x00459640 (273 bytes): the iterateDrawablesInRegion
// callback from Zero Hour's SelectionInfo.cpp, placed between the matched
// PickDrawableStruct constructor (0x00459140) and contextCommandForNewSelection
// (0x00459200).  cdecl (Drawable *, void *userData) returning Bool, as the Zero
// Hour twin.  BFME reworks the body: a second PickDrawableStruct mask at +0x20
// rejects, the +5 flag applies CanSelectDrawable's status-bit 0x48 / kind 14
// rejection, Drawable::isMassSelectable replaces isSelectable, and an object
// whose producer (Object+0x78 m_producerID, layout witness) is of kind 0x6c
// hands that producer's drawable to the list instead.

#include <list>

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

const Bool FALSE = 0;
const Bool TRUE = 1;

class Drawable;
typedef _STL::list<Drawable *> DrawableList;

enum KindOfType
{
	KINDOF_DOZER = 14,
	KINDOF_BFME_PRODUCER_SELECTS = 0x6c
};

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID,
	OBJECTSHROUD_CLEAR,
	OBJECTSHROUD_PARTIAL_CLEAR,
	OBJECTSHROUD_FOGGED
};

typedef Int ObjectID;

// The kind-of mask at ThingTemplate+0xc8.  Its any-intersection member is the
// matched body at 0x00132A20, which retail reaches through ILT 0x000497D3.
class Rva00132A20ThingMask
{
public:
	bool rva00132a20(const Rva00132A20ThingMask &that) const;

private:
	UnsignedInt m_bits[6];
};

typedef Rva00132A20ThingMask KindOfMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
private:
	void *m_vtable;
	const Overridable *m_nextOverride;

public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride != 0)
			return m_nextOverride->getFinalOverride();
		return this;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
private:
	unsigned char m_opaque[0xC8 - sizeof(Overridable)];
	KindOfMaskType m_kindof;

public:
	Bool isAnyKindOf(const KindOfMaskType &anyKindOf) const
	{
		return m_kindof.rva00132a20(anyKindOf);
	}
};

template <class T> class OverridePtr
{
private:
	const T *m_overridable;

public:
	operator const T *() const
	{
		if (m_overridable == 0)
			return 0;
		return static_cast<const T *>(m_overridable->getFinalOverride());
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
private:
	void *m_vtable;
	OverridePtr<ThingTemplate> m_template;

public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Bool isKindOf(KindOfType kind) const;
};

// The producer's drawable is read through vtable slot 10; that slot's owner
// is not proven, so the view keeps the address.
class Rva00459640ProducerView
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Drawable *slot10();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
private:
	unsigned char m_opaque[0x78 - sizeof(Thing)];
	ObjectID m_producerID;

public:
	ObjectID getProducerID() const { return m_producerID; }
	ObjectShroudStatus getShroudedStatus(Int playerIndex) const;
};

class BFMESelectionObjectStatus
{
public:
	Bool testStatus(int status) const;
};

class BFMESelectionStatusBits
{
public:
	Bool test(UnsignedInt bit) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable : public Thing
{
private:
	unsigned char m_opaque[0xFC - sizeof(Thing)];
	Object *m_object;

public:
	Object *getObject() const { return m_object; }
	Bool isMassSelectable() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
private:
	unsigned char m_opaque[0x24];
	Int m_playerIndex;

public:
	Int getPlayerIndex() const { return m_playerIndex; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
private:
	unsigned char m_opaque[0x0C];
	Player *m_local;

public:
	Player *getLocalPlayer() { return m_local; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern PlayerList *ThePlayerList;
extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/SelectionInfo.h
struct PickDrawableStruct
{
	DrawableList *drawableListToFill;
	Bool forceAttackMode;
	Bool m_reserved;
	KindOfMaskType kindofsToMatch;
	KindOfMaskType m_reservedMask;
};

// ?addDrawableToList@@YA_NPAVDrawable@@PAX@Z
Bool addDrawableToList(Drawable *draw, void *userData)
{
	PickDrawableStruct *pds = (PickDrawableStruct *)userData;

	if (!pds->drawableListToFill)
		return FALSE;

	if (!draw->getTemplate()->isAnyKindOf(pds->kindofsToMatch))
		return FALSE;

	if (draw->getTemplate()->isAnyKindOf(pds->m_reservedMask))
		return FALSE;

	Object *obj = draw->getObject();
	if (pds->m_reserved && obj
		&& reinterpret_cast<const BFMESelectionStatusBits *>(obj)->test(0x48)
		&& obj->isKindOf(KINDOF_DOZER))
		return FALSE;

	if (!draw->isMassSelectable())
		return FALSE;

	if (obj)
	{
		Player *player = ThePlayerList->getLocalPlayer();
		if (player && obj->getShroudedStatus(player->getPlayerIndex()) > OBJECTSHROUD_PARTIAL_CLEAR)
			return FALSE;

		ObjectID producerID = obj->getProducerID();
		if (producerID)
		{
			Object *producer = TheGameLogic->findObjectByID(producerID);
			if (producer && producer->isKindOf(KINDOF_BFME_PRODUCER_SELECTS))
			{
				if (reinterpret_cast<const BFMESelectionObjectStatus *>(producer)->testStatus(3))
					return FALSE;
				draw = reinterpret_cast<Rva00459640ProducerView *>(producer)->slot10();
			}
		}
	}

	pds->drawableListToFill->push_back(draw);
	return TRUE;
}
