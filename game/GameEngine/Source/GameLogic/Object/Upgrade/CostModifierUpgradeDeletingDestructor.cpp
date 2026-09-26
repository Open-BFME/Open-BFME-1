// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructor for CostModifierUpgrade.
// Its unique primary vtable (0x010CC5AC) is installed by the named
// constructor at 0x002D4570; slot zero routes through ILT 0x00049CD8 to
// this 30-byte wrapper.  Retail teardown evidence includes the class's
// complete destructor at 0x001F8970 and nested/base teardown at 0x002D44E0.

// Retail's slot calls the compiler's complete-destructor ILT at 0x00025293,
// whose TU-local object symbol remains the generated placeholder spelling.
// The recovered typedef preserves the named class identity at the force site.
class Gen_dtor_002d46a0
{
public:
	virtual ~Gen_dtor_002d46a0();

private:
	friend void forceCostModifierUpgradeDeletingDestructor();
};

typedef Gen_dtor_002d46a0 CostModifierUpgrade;

void forceCostModifierUpgradeDeletingDestructor()
{
	CostModifierUpgrade value;
}
