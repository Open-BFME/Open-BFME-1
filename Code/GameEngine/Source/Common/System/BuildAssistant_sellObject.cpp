// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source
// stlport
// readable body of ?sellObject@BuildAssistant@@UAEXPAVObject@@@Z: Code/GameEngine/Source/Common/System/BuildAssistant.cpp

// BuildAssistant::sellObject, retail 0x001003C0 (344 bytes).
//
// Identity: the body news a 12-byte object and installs vftable 0x010860C0,
// the ObjectSellInfo table xferTheSellList (0x000FE240) serializes, then
// pushes it on the front of the list at this+0x10 -- Zero Hour's sell flow.
// BFME drops the model-condition set, the parking-place and mine sweeps, asks
// the AI to idle before the contain module, and adds a NOT_SELLABLE veto.
// The two kind indices are read from retail's KindOf name table at VA
// 0x012AA068: entry 7 is "STRUCTURE" and entry 153 "NOT_SELLABLE".
//
// Thing::isKindOf is out of line in BFME (0x000A2CF0, called for the veto);
// the structure test inlines the template's own bit test instead. The
// Zero Hour search loop, break and all, is what puts NULL in EBX for the
// whole body.

#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#include <bitset>
#include <list>

typedef bool Bool;

enum ObjectID { INVALID_ID = 0 };
#define BFME_HAVE_OBJECTID

enum KindOfType
{
	KINDOF_STRUCTURE = 7,			///< retail KindOf name table entry 7
	KINDOF_NOT_SELLABLE = 153		///< retail KindOf name table entry 153
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT,
	CMD_FROM_AI
};

typedef unsigned short PlayerMaskType;
const PlayerMaskType PLAYERMASK_ALL = 0xffff;

// Retail's LOGICFRAMES_PER_SECOND is 5 (ScriptActions_doNamedFlash_Thunk.cpp).
enum { LOGICFRAMES_PER_SECOND = 5 };
static const float TOTAL_FRAMES_TO_SELL_OBJECT = LOGICFRAMES_PER_SECOND * 3.0f;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <int NUMBITS>
class BitFlags
{
public:
	BitFlags(int idx1, int idx2)
	{
		m_bits.set(idx1);
		m_bits.set(idx2);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

// Indices from retail's 86-entry ObjectStatus name table at VA 0x012A6670:
// entry 3 is "UNSELECTABLE" and entry 19 "SOLD".
enum ObjectStatusTypes
{
	OBJECT_STATUS_UNSELECTABLE = 3,
	OBJECT_STATUS_SOLD = 19
};

typedef BitFlags<86> ObjectStatusMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride(void) const;	///< ILT thunk at 0x000022BB

	Overridable *m_nextOverride;						///< retail this+0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	Bool isKindOf(KindOfType t) const
	{
		return (m_kindof[(unsigned int)t >> 5] & (1 << ((unsigned int)t & 31))) != 0;
	}

private:
	unsigned char m_unreconstructed_08[0xC8 - 0x08];
	unsigned int m_kindof[3];							///< retail this+0xC8
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	// 0x00413490 via ILT 0x000478CA: forwards to each draw module's
	// ObjectDrawInterface slot 24, W3DModelDraw::setAnimationLoopDuration.
	void setAnimationLoopDuration(unsigned int numFrames);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProductionUpdate.h
class ProductionUpdateInterface
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void cancelAndRefundAllProduction(void);	///< vtable +0x34
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void onSelling(void);						///< vtable +0x50 (TunnelContain 0x0022F200)
};

// The upstream AIUpdateInterface inherits UpdateModule and AICommandInterface.
// BFME places the latter's vptr at +0x20 (the retail aiIdle receiver
// adjustment, as in ObjectUpdateContainedTeam.cpp).
class AICommandParms;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;
	void aiIdle(CommandSourceType cmdSource);			///< ILT thunk at 0x00024D70
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class UpdateModule
{
public:
	virtual ~UpdateModule();

private:
	unsigned char m_unmodelled_004[0x1c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public UpdateModule, public AICommandInterface
{
};

#define THING_TU_MEMBERS \
	const ThingTemplate *getTemplate(void) const; \
	Bool isKindOf(KindOfType t) const;

#define OBJECT_TU_MEMBERS \
	ObjectID getID(void) const { return m_id; } \
	void setConstructionPercent(Real percent) { m_constructionPercent = percent; } \
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set = true); \
	ProductionUpdateInterface *getProductionUpdateInterface(void); \
	ContainModuleInterface *getContain(void) const { return m_contain; } \
	AIUpdateInterface *getAI(void) { return m_ai; }

#include "GameLogic/Object/object.h"

inline const ThingTemplate *Thing::getTemplate(void) const
{
	const ThingTemplate *tmpl = m_template;
	if (tmpl == 0)
		return 0;
	if (tmpl->m_nextOverride)
		tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
	return tmpl;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned int getFrame(void) { return m_frame; }
	void deselectObject(Object *obj, PlayerMaskType playerMask, Bool affectClient);

private:
	unsigned char m_unreconstructed_00[0x3C];
	unsigned int m_frame;								///< retail this+0x3C
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BuildAssistant.h
class ObjectSellInfo
{
public:
	ObjectSellInfo(void)
	{
		m_id = INVALID_ID;
		m_sellFrame = 0;
	}
	virtual ~ObjectSellInfo();

	ObjectID m_id;										///< retail this+0x04
	unsigned int m_sellFrame;							///< retail this+0x08
};

typedef _STL::list<ObjectSellInfo *> ObjectSellList;
typedef ObjectSellList::iterator ObjectSellListIterator;

class BuildAssistant
{
public:
	virtual void sellObject(Object *obj);

private:
	unsigned char m_unreconstructed_04[0x10 - 0x04];
	ObjectSellList m_sellList;							///< retail this+0x10
};

// ?sellObject@BuildAssistant@@UAEXPAVObject@@@Z
void BuildAssistant::sellObject(Object *obj)
{
	// sanity
	if (obj == NULL)
		return;

	// we can only sell structures ... sanity check this
	if (obj->getTemplate()->isKindOf(KINDOF_STRUCTURE) == false)
		return;

	if (obj->isKindOf(KINDOF_NOT_SELLABLE))
		return;

	// if object already has an entry in the sell list, we shouldn't try to sell it again
	ObjectSellInfo *sellInfo = NULL;
	ObjectSellListIterator it;
	for (it = m_sellList.begin(); it != m_sellList.end(); ++it)
	{
		sellInfo = (*it);
		if (sellInfo->m_id == obj->getID())
			break;
		else
			sellInfo = NULL;
	}
	if (sellInfo != NULL)
		return;

	// set the construction percent of this object just below 100.0% so we can start counting down
	obj->setConstructionPercent(99.9f);

	// add this object to the list of objects being sold
	sellInfo = new ObjectSellInfo;
	sellInfo->m_id = obj->getID();
	sellInfo->m_sellFrame = TheGameLogic->getFrame();
	m_sellList.push_front(sellInfo);

	obj->setStatus(ObjectStatusMaskType(OBJECT_STATUS_SOLD, OBJECT_STATUS_UNSELECTABLE));

	// for everybody, unselect them at this time
	TheGameLogic->deselectObject(obj, PLAYERMASK_ALL, true);

	Drawable *draw = obj->getDrawable();
	if (draw)
		draw->setAnimationLoopDuration(TOTAL_FRAMES_TO_SELL_OBJECT / 2);

	// We also need to refund all production for the object at start-of-sell time
	ProductionUpdateInterface *production = obj->getProductionUpdateInterface();
	if (production)
		production->cancelAndRefundAllProduction();

	// Tell it to stop attacking or anything else it is doing
	if (obj->getAI())
		obj->getAI()->aiIdle(CMD_FROM_AI);

	// Tell the contain module so it can decide what to do.
	ContainModuleInterface *contain = obj->getContain();
	if (contain)
		contain->onSelling();
}
