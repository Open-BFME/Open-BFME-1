// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// RVA-derived Object method at 0x001C7530, 161 bytes. Identity of the method
// is unproven, so it keeps the address token of its existing ABI pin
// (?rva001c7530@Object@@QAE_NXZ). The owner is proven by the body: the same
// pointer it walks is handed to Object::bfmeGetNonnegativePreferredLocomotorHeight
// (0x001BE030 via ILT 0x000047C8), and it reads Object m_template at +0x04 and
// m_ai at +0x204 (the witnessed BFME slot). Starting from this, it follows the
// Object pointer at +0x214 while that object's template has kindof[3] bit
// 0x1000 (the same bit Object_rva001CC660.cpp tests on the same +0x214 object),
// then returns false with no AI, true when the template float at +0x3ec is not
// positive, and otherwise whether AIUpdateInterface::getCurLocomotorSpeed
// (0x0026EC30 via ILT 0x0003DAA5) times that float stays within the preferred
// height. Both template reads are the inline OVERRIDE resolution, which unrolls
// one level of Overridable::getFinalOverride (0x00087A80 via ILT 0x000022BB).
//
// The walk is a do-while whose condition the compiler proves true: that keeps
// retail's aligned top-tested header and unconditional back edge, where a
// while/for loop gets its header test duplicated at the bottom.

typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;

extern const Real BfmeZeroRange;

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad008[0xc8 - 0x8];
	UnsignedInt m_kindof[4];                 // 0x0c8
	unsigned char m_pad0d8[0x3ec - 0xd8];
	Real m_heightFactorAt0x3ec;              // 0x3ec
};

class AIUpdateInterface
{
public:
	Real getCurLocomotorSpeed();
};

class Object
{
public:
	const ThingTemplate *getTemplate() const
	{
		if (!m_template)
			return 0;
		return (const ThingTemplate *)m_template->getFinalOverride();
	}
	AIUpdateInterface *getAI() const { return m_ai; }

	Real bfmeGetNonnegativePreferredLocomotorHeight() const;
	Bool rva001c7530();

private:
	void *m_vtable;
	const ThingTemplate *m_template;         // 0x004
	unsigned char m_pad008[0x204 - 0x8];
	AIUpdateInterface *m_ai;                 // 0x204
	unsigned char m_pad208[0x214 - 0x208];
	Object *m_objectAt0x214;                 // 0x214
};

// ?rva001c7530@Object@@QAE_NXZ
Bool Object::rva001c7530()
{
	Object *obj = this;
	do
	{
		Object *next = obj->m_objectAt0x214;
		if (!next || !(next->getTemplate()->m_kindof[3] & 0x1000))
			break;
		obj = next;
	} while (obj);

	AIUpdateInterface *ai = obj->getAI();
	if (!ai)
		return false;

	Real factor = obj->getTemplate()->m_heightFactorAt0x3ec;
	if (factor <= BfmeZeroRange)
		return true;

	Real height = obj->bfmeGetNonnegativePreferredLocomotorHeight();
	if (ai->getCurLocomotorSpeed() * factor > height)
		return false;
	return true;
}
