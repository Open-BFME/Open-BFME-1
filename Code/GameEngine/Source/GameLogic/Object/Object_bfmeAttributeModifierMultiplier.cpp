// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Object attribute-modifier multiplier query, retail 0x001BFDD0,
// 21 bytes.  The Object wrapper finds the AttributeModifierPoolUpdate module,
// returns false when it is absent, and otherwise tail-forwards the selector and
// output pointer to the pool's multiplicative accumulator.
//
// AttributeModifierPoolUpdate is proven by the finder body's module-name key
// literal and by that class's matched getModuleNameKey implementation.  The
// The selector enum spelling is not recoverable from retail, so Int describes
// only the semantics established by the bytes.

typedef int Int;
typedef bool Bool;
typedef float Real;

class AttributeModifierPoolUpdate
{
public:
	Bool getAttributeModifierMultiplier(Int which, Real *out);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool getAttributeModifierMultiplier(Int which, Real *out) const;

private:
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate(void) const;
};

Bool Object::getAttributeModifierMultiplier(Int which, Real *out) const
{
	AttributeModifierPoolUpdate *pool = findAttributeModifierPoolUpdate();
	if (pool == 0)
		return false;
	return pool->getAttributeModifierMultiplier(which, out);
}
