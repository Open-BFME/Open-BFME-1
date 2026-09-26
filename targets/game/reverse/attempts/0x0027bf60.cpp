// ?d_0027bf60@@YAXXZ
// partial score=0.29 date=2026-09-22
// cl: /O2 /Ob1 /DNDEBUG /MD /EHs-c-

// Open-BFME: unnamed AIUpdateInterface-family helper, retail 0x0027BF60, 461
// bytes, served as Code/gen_asm/d_00278950.asm. Reached from ~AnimalAIUpdate's
// vtable slot; prior identity work (re_attempts.log) established that slot is
// ICF-folded with the unrelated common AIUpdateInterface::update body at
// 0x0027E5A0, and that this body does not match Zero Hour's doLocomotor. No
// caller, vtable slot, or ZH source proves a real method name, so this lands
// address-kept.
//
// Shape (from the retail disassembly): the object's own "attack ready" bit
// (flags+0x120 bit 0x80000) gates a Horde-style rate-of-fire recompute. When
// the bit is set, we test the object's own condition mask against a
// lazily-constructed static ModelConditionFlags(0x74,0x75,0x76); if it does
// not match we may also check whether we (or, failing our own range check
// against a per-template range field at +0x3E8, our AI Horde parent) are
// within range of our target (a call through the still-dump helper pinned
// below as rva002774c0), then compare a per-owner "next allowed" frame at
// +0x214 against TheBfmeGameLogic's current frame to return either a
// remaining-cooldown count or a template-derived rate (+0x42C, halved+1), and
// otherwise write a new deadline. When the bit is unset, the function only
// ever touches the flag and notifies -- it returns a large sentinel either way.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

class ThingTemplate
{
public:
	char m_bfmeUnreconstructed_000[0x3E8];
	Real m_bfmeRangeSq;						///< retail this+0x3E8
	char m_bfmeUnreconstructed_3EC[0x42C - 0x3EC];
	Int m_bfmeHalfCountBase;					///< retail this+0x42C
};

class Thing
{
public:
	const ThingTemplate *getTemplate(void) const;			// ILT 0x000084B8
};

class BFMESelectionStatusBits
{
public:
	Bool test(UnsignedInt index) const;				// ILT 0x0003AB20
};

class BfmeOwnerVNI
{
public:
	void bfmeApply1VNI(void);					// ILT 0x0002191D
};

class BfmeBlockVKQ
{
public:
	char bfmeAnyVKQ(const BfmeBlockVKQ &other) const;		// ILT 0x00026F62
private:
	int m_bfmeArr[10];
};

template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType { kInit = 0 };
	BitFlags(BogusInitType, Int, Int, Int);			// ILT 0x00048FDB
private:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

class BfmeObjAS
{
public:
	BfmeObjAS *bfmeParentAS(Int flag);				// ILT 0x0000FAA6

	char m_bfmeUnreconstructed_000[0x04];
	Thing *m_bfmeTemplateOwner;					///< retail this+0x04, aliases Object::m_template
	char m_bfmeUnreconstructed_008[0x110 - 0x08];
	BfmeBlockVKQ m_bfmeConditionFlags;				///< retail this+0x110
	unsigned char m_bfmeByte114;					///< retail this+0x114
	char m_bfmeUnreconstructed_115[0x120 - 0x115];
	UnsignedInt m_bfmeFlags120;					///< retail this+0x120
	char m_bfmeUnreconstructed_124[0x204 - 0x124];
	void *m_bfmeAi;						///< retail this+0x204, opaque AIUpdateInterfaceRva0027BF60Owner*
};

class BfmeGameLogicLike
{
public:
	char m_bfmeUnreconstructed_000[0x3C];
	UnsignedInt m_bfmeFrame;					///< retail this+0x3C
};

extern BfmeGameLogicLike *TheBfmeGameLogic;				// 0x012F0898

class AIUpdateInterfaceRva0027BF60Owner
{
public:
	float rva002774c0(void);					// ABI-only pin, retail 0x002774C0
	Int rva0027bf60(void);						// this body, retail 0x0027BF60

	char m_bfmeUnreconstructed_000[0x08];
	BfmeObjAS *m_bfmeObject;					///< retail this+0x08
	char m_bfmeUnreconstructed_00C[0x214 - 0x0C];
	Int m_bfmeNextAllowedFrame;					///< retail this+0x214
};

// ?rva0027bf60@AIUpdateInterfaceRva0027BF60Owner@@QAEHXZ
Int AIUpdateInterfaceRva0027BF60Owner::rva0027bf60(void)
{
	BfmeObjAS *obj = m_bfmeObject;
	if (!obj)
		return 1;

	static const BitFlags<304> s_bfmeAttackModeMask(BitFlags<304>::kInit, 0x74, 0x75, 0x76);
	const BfmeBlockVKQ &attackModeMask =
		reinterpret_cast<const BfmeBlockVKQ &>(s_bfmeAttackModeMask);

	Int result = 0x3fffffff;
	AIUpdateInterfaceRva0027BF60Owner *owner = this;
	Bool onCooldownPath = false;

	if (!(obj->m_bfmeFlags120 & 0x80000))
		goto bitNotSet;

	if (obj->m_bfmeConditionFlags.bfmeAnyVKQ(attackModeMask))
		goto joinB;

	if (obj->m_bfmeByte114 & 0x20)
	{
		const ThingTemplate *tmpl = reinterpret_cast<const Thing *>(obj)->getTemplate();
		Real range = tmpl->m_bfmeRangeSq;
		Real dist = this->rva002774c0();
		if (dist > range)
			goto joinB;
	}

	{
		BfmeObjAS *parent = obj->bfmeParentAS(0);
		if (!parent)
			goto onCooldownViaThis;
		if (!reinterpret_cast<const BFMESelectionStatusBits *>(parent)->test(0x25))
			goto onCooldownViaThis;

		owner = reinterpret_cast<AIUpdateInterfaceRva0027BF60Owner *>(parent->m_bfmeAi);
		if (!owner)
			goto onCooldownViaThis;

		{
			const ThingTemplate *parentTmpl = reinterpret_cast<const Thing *>(parent)->getTemplate();
			Real parentRange = parentTmpl->m_bfmeRangeSq;
			Real parentDist = owner->rva002774c0();
			owner = this;
			if (parentDist > parentRange)
				goto joinB;
		}
	}
onCooldownViaThis:
	owner = this;
	onCooldownPath = true;

joinB:
	{
		const ThingTemplate *rateTmpl = reinterpret_cast<const Thing *>(obj)->getTemplate();
		Int count = (rateTmpl->m_bfmeHalfCountBase >> 1) + 1;

		if (!onCooldownPath)
			goto notOnCooldown;

		{
			UnsignedInt currentFrame = TheBfmeGameLogic->m_bfmeFrame;
			Int deadline = owner->m_bfmeNextAllowedFrame;
			if ((UnsignedInt)deadline > currentFrame)
			{
				Int remaining = deadline - (Int)currentFrame;
				if (remaining <= count)
					return remaining;
				return count;
			}
		}

		if (!(obj->m_bfmeFlags120 & 0x80000))
			return result;

		obj->m_bfmeFlags120 &= ~0x80000;
		reinterpret_cast<BfmeOwnerVNI *>(obj)->bfmeApply1VNI();
		return result;

	notOnCooldown:
		{
			UnsignedInt currentFrame = TheBfmeGameLogic->m_bfmeFrame;
			const ThingTemplate *rateTmpl2 = reinterpret_cast<const Thing *>(obj)->getTemplate();
			this->m_bfmeNextAllowedFrame = rateTmpl2->m_bfmeHalfCountBase + (Int)currentFrame;
			return count;
		}
	}

bitNotSet:
	if (obj->m_bfmeConditionFlags.bfmeAnyVKQ(attackModeMask))
		return result;

	if (!(obj->m_bfmeFlags120 & 0x80000))
	{
		obj->m_bfmeFlags120 |= 0x80000;
		reinterpret_cast<BfmeOwnerVNI *>(obj)->bfmeApply1VNI();
	}
	return result;
}
