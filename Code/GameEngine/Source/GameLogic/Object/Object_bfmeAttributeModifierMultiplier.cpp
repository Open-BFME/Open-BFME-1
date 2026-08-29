// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Object attribute-modifier multiplier query, retail 0x001BFDD0,
// 21 bytes.  The Object wrapper finds the AttributeModifierPoolUpdate module,
// returns false when it is absent, and otherwise tail-forwards the selector and
// output pointer to the pool's multiplicative accumulator.
//
// AttributeModifierPoolUpdate is proven by the finder body's module-name key
// literal and by that class's matched getModuleNameKey implementation.  The
// original finder/query verbs and selector enum spelling are not recoverable
// from retail, so the bfme-prefixed names and Int deliberately describe only
// the semantics that the bytes establish.

typedef int Int;
typedef bool Bool;
typedef float Real;

class AttributeModifierPoolUpdate
{
public:
	Bool bfmeGetAttributeModifierMultiplier(Int which, Real *out);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool bfmeGetAttributeModifierMultiplier(Int which, Real *out) const;

private:
	AttributeModifierPoolUpdate *bfmeFindAttributeModifierPoolUpdate(void) const;
};

// ?bfmeGetAttributeModifierMultiplier@Object@@QBE_NHPAM@Z
Bool Object::bfmeGetAttributeModifierMultiplier(Int which, Real *out) const
{
	AttributeModifierPoolUpdate *pool = bfmeFindAttributeModifierPoolUpdate();
	if (pool == 0)
		return false;
	return pool->bfmeGetAttributeModifierMultiplier(which, out);
}
