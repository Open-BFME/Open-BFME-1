// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Open-BFME5: VictoryConditions scalar-deleting destructor at retail
// 0x0035F8F0 (30 bytes).  The constructor-installed vtable 0x010E8D90
// and matched complete destructor at 0x0035F880 establish the identity.

class VictoryConditions
{
public:
	virtual ~VictoryConditions();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceVictoryConditionsDeletingDestructor(const VictoryConditions &that)
{
	VictoryConditions value(that);
}
