// cl: /DNDEBUG /MD /EHsc
//
// Address-derived reconstruction of retail RVA 0x00272CD0, 232 bytes.
// The owner is address-derived: this+0x08 is an Object* (same slot the landed
// AIUpdateInterface bodies in Code/GameEngine/Source/GameLogic/AI/AIWaypointPathStates.cpp
// use), but no named caller, vtable slot or string proves a semantic method
// name, so the class keeps the address token.
//
// What the body itself proves:
//   this+0x248  a 40-byte cache compared with ??9ModelConditionFlags@@QBE_NABV0@@Z
//               (ILT 0x00035CA1 -> 0x001C2870)
//   this+0x270  a 12-byte cache compared with ??9?$BitFlags@$0FG@@@QBE_NABV0@@Z
//               (ILT 0x00022C5A -> 0x001C2920); BitFlags<86> == ObjectStatusMaskType
//   Object+0x90 m_status (name_oracle layout witness, confidence 1.00)
//   0x012F0898  TheBfmeGameLogic; +0x3C is the frame counter, the same slot
//               ?_bfme_getFramesBehindPacketRouter@Network@@UAEHXZ reads
//   0x012F060C  g_bfmeOwnerBR, the singleton both change dispatchers hang off
//
// Load-bearing: the two stack temporaries must be DECLARED condition-first,
// status-second. Retail hoists `mov ecx,0xa` above the frame branch and copies
// the 40-byte block before the 12-byte one on both paths; declaring the status
// temporary first reorders those copies and costs 3 bytes.

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ModelConditionFlags.h
class ModelConditionFlags
{
public:
	Bool operator!=(const ModelConditionFlags &other) const;

private:
	UnsignedInt m_bits[10];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <int NUMBITS> class BitFlags
{
public:
	Bool operator!=(const BitFlags &other) const;

private:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<86> ObjectStatusMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	unsigned char m_pad_000[0x90];
	ObjectStatusMaskType m_status;
	unsigned char m_pad_09C[0x110 - 0x9C];
	ModelConditionFlags m_modelConditionFlags110;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_pad_000[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheBfmeGameLogic;

// The two change dispatchers the ledger already holds at 0x002E7410 and
// 0x002E7530. Both are reached through the one singleton at 0x012F060C, so the
// ABI-carrying declarations are stacked rather than cast between.
class BfmeBlockVKQ;
struct BfmeMaskYN;

class Rva002E7410
{
public:
	void dispatch(BfmeBlockVKQ *fresh, BfmeBlockVKQ *cached, Object *object);
};

class BfmeOwnerBR : public Rva002E7410
{
public:
	void bfmeGo7530(BfmeMaskYN *fresh, BfmeMaskYN *cached, Object *object);
};

extern BfmeOwnerBR *g_bfmeOwnerBR;

class Rva00272CD0Updater
{
public:
	void refreshCachedFlags();

private:
	unsigned char m_pad_000[0x08];
	Object *m_object;
	unsigned char m_pad_00C[0x248 - 0x0C];
	ModelConditionFlags m_cachedModelConditionFlags248;
	ObjectStatusMaskType m_cachedStatus270;
};

// ?refreshCachedFlags@Rva00272CD0Updater@@QAEXXZ  retail 0x00272CD0, 232 bytes
void Rva00272CD0Updater::refreshCachedFlags()
{
	UnsignedInt frame = TheBfmeGameLogic->getFrame();
	Object *object = m_object;

	if (frame < 2)
	{
		m_cachedModelConditionFlags248 = object->m_modelConditionFlags110;
		m_cachedStatus270 = object->m_status;
		return;
	}

	ModelConditionFlags conditions = object->m_modelConditionFlags110;
	ObjectStatusMaskType status = object->m_status;

	if (m_cachedModelConditionFlags248 != conditions)
	{
		g_bfmeOwnerBR->dispatch(
			(BfmeBlockVKQ *)&conditions,
			(BfmeBlockVKQ *)&m_cachedModelConditionFlags248,
			object);
		m_cachedModelConditionFlags248 = conditions;
	}

	if (m_cachedStatus270 != status)
	{
		g_bfmeOwnerBR->bfmeGo7530(
			(BfmeMaskYN *)&status,
			(BfmeMaskYN *)&m_cachedStatus270,
			object);
		m_cachedStatus270 = status;
	}
}
