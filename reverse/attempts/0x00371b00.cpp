// ?checkRepairsPending@CastleBehavior@@QAE_NXZ
// partial score=0.65 date=2026-09-21
// present-unmatched
//
// No named caller (one ILT-mediated site, unnamed). This+0xa0/+0xa5 and
// +0xb8/+0xbc/+0xdc/+0xe0 sit past CastleBehavior's proven 12-byte prefix
// (vtable/m_moduleData/m_object, from the landed sibling
// CastleBehaviorIsPlayerAllowedToPackOrUnpack.cpp at 0x00371550, 1456 bytes
// before this body), so the class stays CastleBehavior -- that prefix is
// proven -- but every new field past +8 is address-derived: nothing proves
// their real names.
//
// Behavior: computes a frame threshold from TheWritableGlobalData (a scaled
// GlobalData field when present, else a fallback constant), and returns
// false immediately if TheGameLogic hasn't reached it yet. Otherwise it
// walks TWO ObjectID vectors (+0xb8/+0xbc and +0xdc/+0xe0) hung off this;
// for each ID it resolves the Object, reaches a nested pointer chain
// (obj+4 -> +4) and asks that Overridable's final-override for a status
// bit (+0xd8 & 0x200000); if that bit is already set the entry is skipped,
// otherwise it asks the object's ProjectileUpdateInterface (slot +0xc) a
// question -- if that answers true, return false right away (something is
// still pending). Finishing both vectors without an early exit returns
// true. This "false on first pending item, true when clean" shape matches
// a completion gate over castle repair/rebuild queues; the exact meaning
// of +0xa0/+0xa5 (this method's own leading ID + bool) and the KindOf/bit
// checks in the pre-loop object status test (+0x344 bit 1, +0x118 bits
// 4/8, +0x114 bit 0x8000000) are not independently proven, so they keep
// address-derived member/local names too.
//
// callees, in body order (all already matched/pinned):
//   __ftol2 -> Ftol2Thunk.cpp
//   ?findObjectByID@GameLogic@@QAEPAVObject@@H@Z ILT 0x0001F253 -> 0x0009A510 (x4)
//   ?isKindOf@Thing@@QBE_NW4KindOfType@@@Z ILT 0x0003251F -> 0x000A2CF0
//     (KindOfType 0xE = KINDOF_COMMANDCENTER, per
//     reference/.../Common/KindOf.h with ALLOW_SURRENDER not defined)
//   ?getFinalOverride@Overridable@@QBEPBV1@XZ ILT 0x000022BB -> 0x00087A80 (x2)
//   ?getProjectileUpdateInterface@Object@@QBEPAVProjectileUpdateInterface@@XZ
//     ILT 0x0000DE9F -> 0x001BF630 (x2)
//
// globals: TheWritableGlobalData (0x012ED5C8), TheGameLogic (0x012F0898),
// a GlobalData float field at +0x11f8 scaled by a constant at 0x01075344,
// and a fallback float constant at 0x010E1F40 used when GlobalData is null.

typedef int Int;
typedef bool Bool;
enum KindOfType { KINDOF_COMMANDCENTER = 14 };

class GlobalData
{
public:
	unsigned char m_pad[0x11f8];
	float m_rva00371B00Threshold;			///< retail this+0x11f8
};

extern GlobalData *TheWritableGlobalData;		///< retail [0x012ED5C8]
extern const float g_rva00371B00ThresholdScale;	///< retail [0x01075344]
extern const float g_rva00371B00FallbackThreshold;	///< retail [0x010E1F40]

class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
	const Overridable *getFinalOverride() const;

	unsigned char m_pad04[0xd8 - 0x08];
	unsigned int m_statusBits;			///< retail this+0xd8
};

class ProjectileUpdateInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual Bool rva00371B00Query();		///< vtable slot +0xc
};

class Thing
{
public:
	void *m_vtable;
	Overridable *m_template;			///< retail this+4; ThingTemplate IS-A Overridable

	Bool isKindOf(KindOfType t) const;
};

class Object : public Thing
{
public:
	ProjectileUpdateInterface *getProjectileUpdateInterface() const;
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	Int m_frame;					///< retail this+0x3c

	Object *findObjectByID(Int id);
};

extern GameLogic *TheGameLogic;			///< retail [0x012F0898]

class Rva00371B00IdVector
{
public:
	Int *m_begin;
	Int *m_end;
};

class CastleBehavior
{
public:
	Bool checkRepairsPending(void);		///< address-derived name

private:
	void *m_vtable;
	void *m_moduleData;
	Object *m_object;

	unsigned char m_pad0c[0xa0 - 0x0c];
	Int m_leadObjectID;				///< retail this+0xa0
	unsigned char m_pad0a4[0xa5 - 0xa4];
	Bool m_leadFlag;				///< retail this+0xa5
	unsigned char m_pad0a6[0xb8 - 0xa6];
	Rva00371B00IdVector m_firstList;		///< retail this+0xb8 / +0xbc
	unsigned char m_padbc[0xdc - 0xc0];
	Rva00371B00IdVector m_secondList;		///< retail this+0xdc / +0xe0
};

Bool CastleBehavior::checkRepairsPending(void)
{
	GlobalData *data = TheWritableGlobalData;
	GameLogic *logic = TheGameLogic;
	unsigned int frame = (unsigned int)logic->m_frame;

	float thresholdF;
	if (data)
	{
		float scaled = data->m_rva00371B00Threshold;
		thresholdF = scaled * g_rva00371B00ThresholdScale;
	}
	else
		thresholdF = g_rva00371B00FallbackThreshold;
	unsigned int threshold = (unsigned int)(Int)thresholdF;

	if (frame < threshold)
		return false;

	Object *lead = logic->findObjectByID(m_leadObjectID);
	if (!lead)
	{
		m_leadFlag = true;
	}
	else
	{
		m_leadFlag = false;
		if (*(unsigned char *)((char *)lead + 0x344) & 1)
			m_leadFlag = true;
		if (*(unsigned int *)((char *)lead + 0x118) & 4)
			m_leadFlag = true;
		if (*(unsigned int *)((char *)lead + 0x118) & 8)
		{
			Object *chainOwner = TheGameLogic->findObjectByID(
				*(Int *)((char *)lead + 0x7c));
			if (chainOwner && (*(unsigned char *)((char *)chainOwner + 0x344) & 1))
			{
				if (chainOwner->isKindOf(KINDOF_COMMANDCENTER))
					m_leadFlag = true;
			}
		}
		if (*(unsigned int *)((char *)lead + 0x114) & 0x8000000)
			m_leadFlag = true;
	}

	if (!m_leadFlag)
		return false;

	Int *it = m_firstList.m_begin;
	while (it != m_firstList.m_end)
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj)
		{
			Overridable *chain = obj->m_template;
			const Overridable *final = chain;
			if (chain && chain->m_nextOverride)
				final = chain->m_nextOverride->getFinalOverride();
			if (!(final->m_statusBits & 0x200000))
			{
				ProjectileUpdateInterface *pui = obj->getProjectileUpdateInterface();
				if (pui && pui->rva00371B00Query())
					return false;
			}
		}
		++it;
	}

	it = m_secondList.m_begin;
	while (it != m_secondList.m_end)
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj)
		{
			Overridable *chain = obj->m_template;
			const Overridable *final = chain;
			if (chain && chain->m_nextOverride)
				final = chain->m_nextOverride->getFinalOverride();
			if (!(final->m_statusBits & 0x200000))
			{
				ProjectileUpdateInterface *pui = obj->getProjectileUpdateInterface();
				if (pui && pui->rva00371B00Query())
					return false;
			}
		}
		++it;
	}

	return true;
}
