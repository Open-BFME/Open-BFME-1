// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: SiegeDeploySpecialPower scalar-deleting destructor at retail RVA
// 0x00266670 (30 bytes).  Its wrapper calls the matched complete destructor
// at 0x002664F0 through ILT 0x00016153.  The exact constructor at 0x00266240,
// primary/interface vtables, and typed module factories establish the class
// identity independently of the generated placeholder.

class SiegeDeploySpecialPower
{
public:
	virtual ~SiegeDeploySpecialPower();
};

void forceSiegeDeploySpecialPowerDeletingDestructor()
{
	SiegeDeploySpecialPower value;
}
