// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ManTheWallsSpecialPower scalar deleting destructor.  The
// matched constructor at 0x00260600 installs primary vtable 0x010B5E6C;
// slot zero reaches this wrapper through ILT 0x0003E0A9.  Its destructor
// call follows ILT 0x0002147C and the forwarding thunk at 0x00260B50 to
// the matched SpecialPowerModule destructor body at 0x00268F30.

class SpecialPowerModule
{
public:
	virtual ~SpecialPowerModule();
};

class ManTheWallsSpecialPower : public SpecialPowerModule
{
public:
	__declspec(noinline) virtual ~ManTheWallsSpecialPower();
};

ManTheWallsSpecialPower::~ManTheWallsSpecialPower()
{
}
